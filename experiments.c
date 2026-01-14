/**
 * @file experiments.c
 * @brief Programme d'expérimentations multiples pour analyser la variabilité stochastique
 *
 * Lance plusieurs simulations avec différentes conditions initiales et collecte
 * les statistiques (moyenne, écart-type, min, max) pour analyser la variabilité.
 */

#include "simulation.h"
#include <time.h>
#include <math.h>

/**
 * @brief Structure pour stocker les résultats d'une simulation
 */
typedef struct
{
    unsigned long final_babies;
    unsigned long final_males;
    unsigned long final_females;
    unsigned long total_population;
} SimulationResult;

/**
 * @brief Calcule les statistiques sur un ensemble de résultats
 */
void compute_statistics(SimulationResult *results, int num_experiments,
                        double *mean, double *std_dev, unsigned long *min, unsigned long *max)
{
    *mean = 0;
    *min = results[0].total_population;
    *max = results[0].total_population;

    // Calcul de la moyenne
    for (int i = 0; i < num_experiments; i++)
    {
        *mean += results[i].total_population;
        if (results[i].total_population < *min)
            *min = results[i].total_population;
        if (results[i].total_population > *max)
            *max = results[i].total_population;
    }
    *mean /= num_experiments;

    // Calcul de l'écart-type
    double variance = 0;
    for (int i = 0; i < num_experiments; i++)
    {
        double diff = results[i].total_population - *mean;
        variance += diff * diff;
    }
    variance /= num_experiments;
    *std_dev = sqrt(variance);
}

/**
 * @brief Lance une série d'expériences avec les mêmes paramètres
 */
void run_experiment_series(int num_females, int num_males, int years, int num_experiments)
{
    printf("\n==============================================================\n");
    printf("SÉRIE D'EXPÉRIENCES : %d femelles, %d mâles, %d ans\n", num_females, num_males, years);
    printf("Nombre d'expériences : %d\n", num_experiments);
    printf("==============================================================\n\n");

    SimulationResult *results = malloc(num_experiments * sizeof(SimulationResult));

    // Lancer les expériences
    for (int exp = 0; exp < num_experiments; exp++)
    {
        printf("Expérience %d/%d...\n", exp + 1, num_experiments);

        mpz_t nbFemale, nbMale;
        mpz_init_set_ui(nbFemale, num_females);
        mpz_init_set_ui(nbMale, num_males);

        population *pop = simulate_population(nbFemale, nbMale, years);

        // Collecter les résultats finaux
        mpz_t total_babies, total_males, total_females;
        mpz_init_set_ui(total_babies, 0);
        mpz_init_set_ui(total_males, 0);
        mpz_init_set_ui(total_females, 0);

        for (int age = 0; age < AGE_MAX; age++)
        {
            for (int month = 0; month < NB_MONTHS; month++)
            {
                mpz_add(total_babies, total_babies, pop->lapins_par_age[age][month].nb_babies);
                mpz_add(total_males, total_males, pop->lapins_par_age[age][month].nb_male);
                for (int i = 0; i < 10; i++)
                {
                    mpz_add(total_females, total_females,
                            pop->lapins_par_age[age][month].femelles_par_accouchements_restants[i]);
                }
            }
        }

        results[exp].final_babies = mpz_get_ui(total_babies);
        results[exp].final_males = mpz_get_ui(total_males);
        results[exp].final_females = mpz_get_ui(total_females);
        results[exp].total_population = results[exp].final_babies +
                                        results[exp].final_males +
                                        results[exp].final_females;

        mpz_clear(total_babies);
        mpz_clear(total_males);
        mpz_clear(total_females);
        mpz_clear(nbFemale);
        mpz_clear(nbMale);
        free(pop);
    }

    // Calcul des statistiques
    double mean, std_dev;
    unsigned long min, max;
    compute_statistics(results, num_experiments, &mean, &std_dev, &min, &max);

    // Affichage des résultats
    printf("\n----- RÉSULTATS STATISTIQUES -----\n");
    printf("Population moyenne :    %.0f lapins\n", mean);
    printf("Écart-type :           %.0f lapins\n", std_dev);
    printf("Coefficient de variation : %.2f%%\n", (std_dev / mean) * 100);
    printf("Population minimale :  %lu lapins\n", min);
    printf("Population maximale :  %lu lapins\n", max);
    printf("\nDétail des expériences :\n");
    for (int i = 0; i < num_experiments; i++)
    {
        printf("Exp %2d: %10lu lapins (bébés: %7lu, mâles: %7lu, femelles: %7lu)\n",
               i + 1, results[i].total_population,
               results[i].final_babies, results[i].final_males, results[i].final_females);
    }

    free(results);
}

int main()
{
    // Initialisation
    init_survival_rate();
    init_prob_litter();

    printf("\n╔══════════════════════════════════════════════════════════════╗\n");
    printf("║  EXPÉRIMENTATIONS - SIMULATION POPULATION DE LAPINS         ║\n");
    printf("║  Analyse de la variabilité stochastique                     ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");

    // Expérience 1 : Impact des conditions initiales faibles (risque d'extinction)
    printf("\n\n### EXPÉRIENCE 1 : Conditions initiales faibles ###\n");
    run_experiment_series(10, 10, 10, 5);

    // Expérience 2 : Conditions initiales moyennes
    printf("\n\n### EXPÉRIENCE 2 : Conditions initiales moyennes ###\n");
    run_experiment_series(50, 50, 10, 5);

    // Expérience 3 : Conditions initiales fortes
    printf("\n\n### EXPÉRIENCE 3 : Conditions initiales fortes ###\n");
    run_experiment_series(100, 100, 10, 5);

    // Expérience 4 : Simulation longue durée
    printf("\n\n### EXPÉRIENCE 4 : Simulation sur 20 ans ###\n");
    run_experiment_series(100, 100, 20, 3);

    printf("\n\n═══════════════════════════════════════════════════════════════\n");
    printf("CONCLUSION :\n");
    printf("Les résultats montrent une forte variabilité stochastique.\n");
    printf("Plusieurs exécutions sont nécessaires pour obtenir des résultats\n");
    printf("statistiquement significatifs.\n");
    printf("═══════════════════════════════════════════════════════════════\n\n");

    return 0;
}
