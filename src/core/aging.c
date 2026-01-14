/**
 * @file aging.c
 * @brief Implémentation de la logique de vieillissement
 *
 * Ce fichier contient les fonctions qui gèrent le vieillissement de la population:
 * - Vieillissement des mâles (survie selon l'âge)
 * - Vieillissement des femelles (survie et attribution des portées)
 * - Maturation des bébés (devenir adulte mâle ou femelle)
 * - Passage au mois suivant pour toute la population
 */

#include "aging.h"
#include "config.h"
#include "reproduction.h"
#include "mt19937ar-cok.h"
#include "gmp.h"

#define GRAND_NB 10000 // Seuil pour utiliser l'approximation gaussienne

extern double prob_maturity[];
extern double survival_rate_month_baby;

/**
 * @brief Retourne l'état de la population au mois précédent
 *
 * @param pop Pointeur vers la population
 * @param year Âge en années
 * @param month Mois (0-11)
 * @return Structure mois_lapin du mois précédent
 */
mois_lapin prev_month(population *pop, int year, int month)
{
    if (!month)
    {
        year--;
        month = 11;
    }
    else
    {
        month--;
    }
    return pop->lapins_par_age[year][month];
}

/**
 * @brief Simule le vieillissement et la survie des mâles adultes
 *
 * Pour chaque mâle du mois précédent, tire aléatoirement s'il survit
 * selon le taux de survie de son âge. Deux méthodes sont utilisées:
 * - Simulation individuelle pour les petites populations
 * - Approximation binomiale gaussienne pour les grandes populations
 *
 * @param pop_month Pointeur vers le mois de destination
 * @param pop_month_prev Mois source (mois précédent)
 * @param age Âge en années
 */
void male_aging(mois_lapin *pop_month, mois_lapin pop_month_prev, int age)
{
    mpz_set_ui(pop_month->nb_male, 0);
    mpz_t nb_male;
    mpz_init(nb_male);
    mpz_set(nb_male, pop_month_prev.nb_male);
    if (mpz_cmp_ui(nb_male, GRAND_NB) < 0)
    {
        unsigned long n_male = mpz_get_ui(nb_male);
        for (unsigned long i = 0; i < n_male; i++)
        {
            if (genrand_real1() < survival_rate_adult(age))
                mpz_add_ui(pop_month->nb_male, pop_month->nb_male, 1);
        }
    }
    else
    {

        binomial_gaussian(pop_month->nb_male, nb_male, survival_rate_adult(age));
    }
    mpz_clear(nb_male);
}

/**
 * @brief Simule le vieillissement et la survie des femelles adultes
 *
 * Gère la survie des femelles et leur attribution de nouvelles portées.
 * Traitement spécial au début de l'année (month == 0) où les femelles
 * reçoivent un nouveau nombre de portées pour l'année.
 *
 * @param pop_month Pointeur vers le mois de destination
 * @param pop_month_prev Mois source (mois précédent)
 * @param age Âge en années
 * @param month Mois actuel (0-11)
 */
void female_aging(mois_lapin *pop_month, mois_lapin pop_month_prev, int age, int month)
{
    for (int i = 0; i < 10; i++)
    {
        mpz_set_ui(pop_month->femelles_par_accouchements_restants[i], 0);
    }

    if (month == 0)
    {
        mpz_t nb_female;
        mpz_init(nb_female);
        mpz_set(nb_female, pop_month_prev.femelles_par_accouchements_restants[0]);
        if (mpz_cmp_ui(nb_female, GRAND_NB) < 0)
        {

            unsigned long n_female_ul = mpz_get_ui(nb_female);
            for (unsigned long i = 0; i < n_female_ul; i++)
            {
                if (genrand_real1() < survival_rate_adult(age))
                {
                    mpz_add_ui(pop_month->femelles_par_accouchements_restants[litter_per_year()], pop_month->femelles_par_accouchements_restants[litter_per_year()], 1);
                }
            }
        }
        else
        {
            mpz_t nb_female;
            mpz_init(nb_female);
            binomial_gaussian(nb_female, pop_month_prev.femelles_par_accouchements_restants[0], survival_rate_adult(age));
            mpz_t *counts = multinomial_gaussian(nb_female, prob_litter, 10);
            for (int i = 0; i < 10; i++)
            {
                mpz_set(pop_month->femelles_par_accouchements_restants[i], counts[i]);
            }
            free(counts);
        }
    }
    else
    {
        for (int acc_rest = 0; acc_rest < 10; acc_rest++)
        {
            mpz_t nb_females;
            mpz_init(nb_females);
            mpz_set(nb_females, pop_month_prev.femelles_par_accouchements_restants[acc_rest]);

            if (mpz_cmp_ui(nb_females, GRAND_NB) < 0)
            {
                unsigned long n_females_ul = mpz_get_ui(nb_females);
                for (unsigned long i = 0; i < n_females_ul; i++)
                {
                    if (genrand_real1() < survival_rate_adult(age))
                        mpz_add_ui(pop_month->femelles_par_accouchements_restants[acc_rest], pop_month->femelles_par_accouchements_restants[acc_rest], 1);
                }
            }
            else
            {
                binomial_gaussian(pop_month->femelles_par_accouchements_restants[acc_rest], nb_females, survival_rate_adult(age));
            }
            mpz_clear(nb_females);
        }
    }
}

/**
 * @brief Simule le vieillissement et la maturation des bébés
 *
 * Les bébés peuvent:
 * 1. Mourir (selon survival_rate_month_baby)
 * 2. Devenir matures (selon prob_maturity[month])
 *    - Devenir mâle (50% de chance)
 *    - Devenir femelle (50% de chance) avec attribution du nombre de portées
 * 3. Rester bébé un mois de plus
 *
 * @param pop_month Pointeur vers le mois de destination
 * @param pop_month_prev Mois source (mois précédent)
 * @param month Mois d'âge du bébé (0-10)
 */
void babies_aging(mois_lapin *pop_month, mois_lapin pop_month_prev, int month)
{
    mpz_set_ui(pop_month->nb_babies, 0);
    mpz_t n_babies;
    mpz_init(n_babies);
    mpz_set(n_babies, pop_month_prev.nb_babies);
    if (mpz_cmp_ui(n_babies, GRAND_NB) < 0)
    {

        unsigned long n_babies_ul = mpz_get_ui(n_babies);
        for (unsigned long i = 0; i < n_babies_ul; i++)
        {
            if (genrand_real1() < survival_rate_month_baby)
            {

                if (genrand_real1() < prob_maturity[month])
                {
                    if (genrand_real1() < 0.5)
                    {
                        mpz_add_ui(pop_month->nb_male, pop_month->nb_male, 1);
                    }
                    else
                    {
                        int nb_litter = litter_per_year();
                        if (nb_litter < month)
                            mpz_add_ui(pop_month->femelles_par_accouchements_restants[0], pop_month->femelles_par_accouchements_restants[0], 1);
                        else
                            mpz_add_ui(pop_month->femelles_par_accouchements_restants[nb_litter - month], pop_month->femelles_par_accouchements_restants[nb_litter - month], 1);
                    }
                }
                else
                {
                    mpz_add_ui(pop_month->nb_babies, pop_month->nb_babies, 1);
                }
            }
        }
    }
    else
    {
        mpz_t n_babies_survived;
        mpz_init(n_babies_survived);
        binomial_gaussian(n_babies_survived, n_babies, survival_rate_month_baby); // survie
        mpz_t n_mature;
        mpz_init(n_mature);
        binomial_gaussian(n_mature, n_babies_survived, prob_maturity[month]); // maturité
        mpz_t n_male;
        mpz_init(n_male);
        binomial_gaussian(n_male, n_mature, 0.5);
        mpz_set(pop_month->nb_male, n_male);
        mpz_t n_female;
        mpz_init(n_female);
        mpz_sub(n_female, n_mature, n_male);
        mpz_t *counts = multinomial_gaussian(n_female, prob_litter, 10);
        mpz_set_ui(pop_month->femelles_par_accouchements_restants[0], 0);
        for (int i = 0; i <= month; i++)
        {
            mpz_add(pop_month->femelles_par_accouchements_restants[0], pop_month->femelles_par_accouchements_restants[0], counts[i]);
        }
        for (int i = month + 1; i < 10; i++)
        {
            mpz_add(pop_month->femelles_par_accouchements_restants[i - month], pop_month->femelles_par_accouchements_restants[i - month], counts[i]);
        }
        free(counts);

        mpz_sub(pop_month->nb_babies, n_babies_survived, n_mature);
        mpz_clear(n_babies_survived);
        mpz_clear(n_mature);
        mpz_clear(n_male);
        mpz_clear(n_female);
    }
    mpz_clear(n_babies);
}

/**
 * @brief Fait vieillir toute la population d'un mois
 *
 * Parcourt la population en sens inverse (des plus vieux aux plus jeunes)
 * pour éviter d'écraser les données. Pour chaque âge et mois:
 * 1. Applique le vieillissement des mâles
 * 2. Applique le vieillissement des femelles
 * 3. Applique la maturation des bébés (uniquement pour l'âge 0)
 *
 * @param pop Pointeur vers la population à faire vieillir
 */
void aging(population *pop)
{
    mois_lapin pop_month;
    mois_lapin pop_month_prev = pop->lapins_par_age[AGE_MAX - 1][NB_MONTHS - 1];
    for (int age = AGE_MAX - 1; age >= 0; age--)
    {
        for (int month = NB_MONTHS - 1; month >= 0; month--)
        {
            pop_month = pop_month_prev;
            if (!(age || month)) // on traite les lapins agés de 0 mois après
                break;

            pop_month_prev = prev_month(pop, age, month);

            male_aging(&pop_month, pop_month_prev, age);
            female_aging(&pop_month, pop_month_prev, age, month);
            if ((age == 0) && (month <= 10))
                babies_aging(&pop_month, pop_month_prev, month);
            pop->lapins_par_age[age][month] = pop_month;
        }
    }
}
