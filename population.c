#include "population.h"
#include "reproduction.h"

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
