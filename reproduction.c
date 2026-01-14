#include "reproduction.h"
#include "mt19937ar-cok/mt19937ar-cok.h"
#include "gmp.h"

#define GRAND_NB 10000

extern double prob_litter[];

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
