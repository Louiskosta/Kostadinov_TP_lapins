#include "simulation.h"
#include "population.h"
#include "reproduction.h"
#include "aging.h"

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
