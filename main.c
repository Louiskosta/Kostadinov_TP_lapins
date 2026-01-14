#include "simulation.h"
#include <time.h>
int main()
{
    init_survival_rate();
    init_prob_litter();
    mpz_t nbFemale, nbMale;
    mpz_init_set_ui(nbFemale, 10);
    mpz_init_set_ui(nbMale, 10);
    population *pop = simulate_population(nbFemale, nbMale, 1000);
    mpz_clear(nbFemale);
    mpz_clear(nbMale);
    free(pop);

    return 0;
}