#include "simulation.h"
#include <math.h>

#define GRAND_NB 10000

double prob_litter[] = {0, 0, 0, 1, 1, 2, 2, 2, 1, 1};
double prob_maturity[] = {0, 0, 0, 0, 0, 0.2, 0.4, 0.6, 0.8, 1, 1};
double survival_rate_month_adult[7];
double survival_rate_month_baby;

void init_prob_litter()
{
    float somme = 0;
    for (int i = 3; i <= 9; i++)
    {
        somme += prob_litter[i];
    }
    for (int i = 1; i <= 9; i++)
    {
        prob_litter[i] = prob_litter[i] / somme + prob_litter[i - 1];
    }
}

int litter_per_year()
{
    float r = genrand_real1();
    for (int i = 1; i <= 9; i++)
    {
        if (r <= prob_litter[i])
        {
            return i;
        }
    }
    return 0;
}

population *initialize_population(mpz_t nbFemale, mpz_t nbMale)
{
    population *p = malloc(sizeof(population));
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
    mpz_set(p->lapins_par_age[1][0].nb_male, nbMale);
    unsigned long n_female = mpz_get_ui(nbFemale);
    for (unsigned long i = 0; i < n_female; i++)
    {
        mpz_add_ui(p->lapins_par_age[1][0].femelles_par_accouchements_restants[litter_per_year()], p->lapins_par_age[1][0].femelles_par_accouchements_restants[litter_per_year()], 1);
    }

    return p;
}

void init_survival_rate()
{
    for (int i = 0; i < 7; i++)
    {
        double rate = 0.6 - i * 0.1;
        if (rate < 0)
            rate = 0;
        survival_rate_month_adult[i] = pow(rate, 1.0 / 12.0);
    }
    survival_rate_month_baby = pow(0.35, 1.0 / 8.0);
}

int accouchement()
{
    return uniform_int(3, 6);
}

void reproduction(population *pop, mpz_t new_babies)
{
    mpz_set_ui(new_babies, 0);
    for (int age = 0; age < AGE_MAX; age++)
    {
        for (int month = 0; month < NB_MONTHS; month++)
        {
            mois_lapin *pop_month = &pop->lapins_par_age[age][month];
            for (int acc_rest = 1; acc_rest <= 9; acc_rest++)
            {
                mpz_t females;
                mpz_init(females);
                mpz_set(females, pop_month->femelles_par_accouchements_restants[acc_rest]);
                if (mpz_cmp_ui(females, GRAND_NB) < 0)
                {

                    unsigned long n_females = mpz_get_ui(females);
                    for (unsigned long f = 0; f < n_females; f++)
                    {
                        if (genrand_real1() <= ((float)acc_rest) / (NB_MONTHS - month))
                        {
                            mpz_add_ui(new_babies, new_babies, accouchement());
                            mpz_sub_ui(pop_month->femelles_par_accouchements_restants[acc_rest], pop_month->femelles_par_accouchements_restants[acc_rest], 1);
                            mpz_add_ui(pop_month->femelles_par_accouchements_restants[acc_rest - 1], pop_month->femelles_par_accouchements_restants[acc_rest - 1], 1);
                        }
                    }
                }
                else
                {
                    mpz_t nb_accouchements;
                    mpz_init(nb_accouchements);
                    binomial_gaussian(nb_accouchements, females, ((float)acc_rest) / (NB_MONTHS - month));

                    // Limiter nb_accouchements au nombre de femelles disponibles
                    if (mpz_cmp(nb_accouchements, females) > 0)
                    {
                        mpz_set(nb_accouchements, females);
                    }

                    mpz_t *counts = multinomial_gaussian(nb_accouchements, prob_litter, 10);
                    mpz_sub(pop_month->femelles_par_accouchements_restants[acc_rest], pop_month->femelles_par_accouchements_restants[acc_rest], nb_accouchements);
                    if (mpz_sgn(pop_month->femelles_par_accouchements_restants[acc_rest]) < 0)
                    {
                        gmp_printf("Erreur négatif %Zd\n", pop_month->femelles_par_accouchements_restants[acc_rest]);
                    }
                    mpz_add(pop_month->femelles_par_accouchements_restants[acc_rest - 1], pop_month->femelles_par_accouchements_restants[acc_rest - 1], nb_accouchements);

                    for (int i = 0; i < 10; i++)
                    {
                        mpz_t temp;
                        mpz_init(temp);
                        mpz_mul_ui(temp, counts[i], i);
                        mpz_add(new_babies, new_babies, temp);
                        mpz_clear(temp);
                        mpz_clear(counts[i]);
                    }
                    free(counts);
                    mpz_clear(nb_accouchements);
                }
                mpz_clear(females);
            }
        }
    }
}

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

double survival_rate_adult(int year)
{
    if (year < 10)
        return survival_rate_month_adult[0];
    int index = year - 10;
    if (index >= 7)
        index = 6;
    return survival_rate_month_adult[index];
}

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
                /*if (mpz_cmp_ui(nb_females, 0) < 0){
                    gmp_printf("test %Zd\n", nb_females);
                    for(int i=0; i<10; i++){
                        gmp_printf("%Zd ", pop_month_prev.femelles_par_accouchements_restants[i]);
                    }
                    printf("\n");
                }*/

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

void afficher_pop(population *pop, int mode)
{
    if (mode == 0)
    {
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
        mpz_t somme_babies;
        mpz_t somme_male;
        mpz_t somme_female;
        mpz_init_set_ui(somme_babies, 0);
        mpz_init_set_ui(somme_male, 0);
        mpz_init_set_ui(somme_female, 0);
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

void simulate_month(population *pop)
{
    // afficher_pop(pop, 1);
    mpz_t new_babies;
    mpz_init(new_babies);
    reproduction(pop, new_babies);
    aging(pop);
    mpz_set(pop->lapins_par_age[0][0].nb_babies, new_babies);
    mpz_clear(new_babies);
}

void simulate_year(population *pop)
{
    for (int m = 0; m < NB_MONTHS; m++)
    {
        // printf("----------------------------------------\nMOIS %d\n", m);
        simulate_month(pop);
    }
}

population *simulate_population(mpz_t nbFemale, mpz_t nbMale, int years)
{
    population *pop = initialize_population(nbFemale, nbMale);

    for (int y = 0; y < years; y++)
    {
        simulate_year(pop);

        printf("ANNEE %d : ", y + 1);
        afficher_pop(pop, 1);
        fflush(stdout);
    }
    // afficher_pop(pop, 0);

    return pop;
}