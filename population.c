/**
 * @file population.c
 * @brief Implémentation de la gestion de la population
 *
 * Ce fichier contient les fonctions pour initialiser et afficher
 * les données de la population de lapins.
 */

#include "population.h"
#include "reproduction.h"

/**
 * @brief Initialise une nouvelle population de lapins
 *
 * Alloue la mémoire pour la structure population et initialise tous
 * les compteurs GMP à zéro. Place la population initiale de femelles
 * et mâles dans la tranche d'âge de 1 an.
 *
 * @param nbFemale Nombre initial de femelles
 * @param nbMale Nombre initial de mâles
 * @return Pointeur vers la structure population allouée
 */
population *initialize_population(mpz_t nbFemale, mpz_t nbMale)
{
    population *p = malloc(sizeof(population));

    // Initialisation de tous les compteurs GMP pour chaque âge et mois
    for (int age = 0; age < AGE_MAX; age++)
    {
        for (int month = 0; month < NB_MONTHS; month++)
        {
            mpz_init(p->lapins_par_age[age][month].nb_babies);
            mpz_init(p->lapins_par_age[age][month].nb_male);
            for (int i = 0; i < 10; i++)
            {
                mpz_init(p->lapins_par_age[age][month].femelles_par_accouchements_restants[i]);
            }
        }
    }

    // Placement de la population initiale à l'âge de 1 an
    mpz_set(p->lapins_par_age[1][0].nb_male, nbMale);
    unsigned long n_female = mpz_get_ui(nbFemale);

    // Répartition aléatoire des femelles selon leur nombre de portées prévues
    for (unsigned long i = 0; i < n_female; i++)
    {
        mpz_add_ui(p->lapins_par_age[1][0].femelles_par_accouchements_restants[litter_per_year()], p->lapins_par_age[1][0].femelles_par_accouchements_restants[litter_per_year()], 1);
    }

    return p;
}

/**
 * @brief Affiche les statistiques de la population
 *
 * @param pop Pointeur vers la population à afficher
 * @param mode Mode d'affichage:
 *             - 0: Affichage détaillé par âge et mois
 *             - 1: Affichage résumé (total bébés, mâles, femelles)
 */
void afficher_pop(population *pop, int mode)
{
    if (mode == 0)
    {
        // Mode détaillé: affichage par âge et mois
        printf("--------------------------------\n");
        for (int year = 0; year < AGE_MAX + 1; year++)
        {
            printf("AGE = %d\n", year);
            for (int month = 0; month < 12; month++)
            {
                mois_lapin pop_month = pop->lapins_par_age[year][month];
                gmp_printf("MONTH %d : babies = %Zd, male = %Zd, females = [", month, pop_month.nb_babies, pop_month.nb_male);
                for (int i = 0; i < 10; i++)
                {
                    gmp_printf("%Zd, ", pop_month.femelles_par_accouchements_restants[i]);
                }
                printf("]\n");
            }
        }
    }
    else
    {
        // Mode résumé: calcul et affichage des totaux
        mpz_t somme_babies;
        mpz_t somme_male;
        mpz_t somme_female;
        mpz_init_set_ui(somme_babies, 0);
        mpz_init_set_ui(somme_male, 0);
        mpz_init_set_ui(somme_female, 0);

        // Somme sur tous les âges et mois
        for (int year = 0; year < AGE_MAX; year++)
        {
            for (int month = 0; month < 12; month++)
            {
                mois_lapin pop_month = pop->lapins_par_age[year][month];
                mpz_add(somme_babies, somme_babies, pop_month.nb_babies);
                mpz_add(somme_male, somme_male, pop_month.nb_male);
                for (int i = 0; i < 10; i++)
                {
                    mpz_add(somme_female, somme_female, pop_month.femelles_par_accouchements_restants[i]);
                }
            }
        }
        gmp_printf("babies = %Zd, male = %Zd, females = %Zd\n", somme_babies, somme_male, somme_female);
    }
}
