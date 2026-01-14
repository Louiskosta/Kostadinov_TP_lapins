/**
 * @file graphiques.c
 * @brief Programme de génération de graphiques pour analyser la simulation
 *
 * Ce programme génère des fichiers de données et des graphiques avec gnuplot
 * pour analyser la variabilité stochastique et comparer différentes conditions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <mpfr.h>
#include "simulation.h"
#include "config.h"
#include "population.h"
#include "mt19937ar-cok.h"

/**
 * @brief Calcule la population totale
 */
unsigned long calculer_total(population *pop)
{
    mpz_t total;
    mpz_init(total);

    for (int age = 0; age <= AGE_MAX; age++)
    {
        for (int mois = 0; mois < NB_MONTHS; mois++)
        {
            mpz_add(total, total, pop->lapins_par_age[age][mois].nb_male);
            mpz_add(total, total, pop->lapins_par_age[age][mois].nb_babies);
            for (int acc = 0; acc < 10; acc++)
            {
                mpz_add(total, total, pop->lapins_par_age[age][mois].femelles_par_accouchements_restants[acc]);
            }
        }
    }

    unsigned long result = mpz_get_ui(total);
    mpz_clear(total);
    return result;
}

/**
 * @brief Libère une population
 */
void liberer_population(population *pop)
{
    for (int age = 0; age <= AGE_MAX; age++)
    {
        for (int mois = 0; mois < NB_MONTHS; mois++)
        {
            mpz_clear(pop->lapins_par_age[age][mois].nb_male);
            mpz_clear(pop->lapins_par_age[age][mois].nb_babies);
            for (int acc = 0; acc < 10; acc++)
            {
                mpz_clear(pop->lapins_par_age[age][mois].femelles_par_accouchements_restants[acc]);
            }
        }
    }
    free(pop);
}

/**
 * @brief Effectue une simulation et retourne la population finale
 */
unsigned long simuler_finale(int males, int females, int annees, unsigned long seed)
{
    init_genrand(seed);

    mpz_t m, f;
    mpz_inits(m, f, NULL);
    mpz_set_ui(m, males);
    mpz_set_ui(f, females);

    population *pop = simulate_population(f, m, annees);
    unsigned long total = calculer_total(pop);

    liberer_population(pop);
    mpz_clears(m, f, NULL);

    return total;
}

/**
 * @brief Génère un graphique boxplot
 */
void graphique_boxplot()
{
    printf("\n=== Génération du boxplot ===\n");

    int nb_rep = 15; // Réduit pour éviter problèmes mémoire
    int annees = 12; // Réduit pour accélérer
    int conditions[][2] = {{10, 10}, {50, 50}, {100, 100}};
    const char *labels[] = {"10x10", "50x50", "100x100"};

    FILE *f = fopen("boxplot_data.dat", "w");
    if (!f)
        return;

    fprintf(f, "# Condition PopFinal\n");

    for (int cond = 0; cond < 3; cond++)
    {
        printf("  Condition %s : ", labels[cond]);
        for (int rep = 0; rep < nb_rep; rep++)
        {
            if (rep % 10 == 0)
                printf(".");
            fflush(stdout);

            unsigned long pop = simuler_finale(
                conditions[cond][0], conditions[cond][1],
                annees, 10000 + cond * 1000 + rep);
            fprintf(f, "%d %lu\n", cond + 1, pop);
        }
        printf(" OK\n");
    }

    fclose(f);

    // Script gnuplot
    FILE *gp = fopen("plot_boxplot.gp", "w");
    if (!gp)
        return;

    fprintf(gp, "set terminal png size 1200,800 font 'Arial,14'\n");
    fprintf(gp, "set output 'boxplot_populations.png'\n");
    fprintf(gp, "set title 'Distribution des populations finales (20 ans, 30 réplications)'\n");
    fprintf(gp, "set ylabel 'Population finale'\n");
    fprintf(gp, "set xlabel 'Condition initiale'\n");
    fprintf(gp, "set xtics ('10×10' 1, '50×50' 2, '100×100' 3)\n");
    fprintf(gp, "set grid y\n");
    fprintf(gp, "set style fill solid 0.3\n");
    fprintf(gp, "set boxwidth 0.4\n");
    fprintf(gp, "plot 'boxplot_data.dat' using 1:2 with boxplot notitle\n");

    fclose(gp);

    if (system("gnuplot plot_boxplot.gp") == 0)
    {
        printf("✓ Graphique généré : boxplot_populations.png\n");
    }
}

/**
 * @brief Génère un graphique de comparaison simple
 */
void graphique_comparaison_simple()
{
    printf("\n=== Génération graphique de comparaison ===\n");

    int conditions[][2] = {{10, 10}, {50, 50}, {100, 100}};
    const char *labels[] = {"10x10", "50x50", "100x100"};
    int annees_max = 15;

    FILE *f = fopen("comparaison_data.dat", "w");
    if (!f)
        return;

    fprintf(f, "# Annees Pop_10x10 Pop_50x50 Pop_100x100\n");

    for (int annee = 0; annee <= annees_max; annee++)
    {
        fprintf(f, "%d", annee);

        for (int cond = 0; cond < 3; cond++)
        {
            if (annee == 0)
            {
                printf("  Condition %s : simulation...", labels[cond]);
                fflush(stdout);
            }

            unsigned long pop = simuler_finale(
                conditions[cond][0], conditions[cond][1],
                annee, 5000 + cond);
            fprintf(f, " %lu", pop);
        }
        fprintf(f, "\n");

        if (annee == 0)
            printf(" OK\n");
    }

    fclose(f);

    // Script gnuplot
    FILE *gp = fopen("plot_comparaison.gp", "w");
    if (!gp)
        return;

    fprintf(gp, "set terminal png size 1200,800 font 'Arial,14'\n");
    fprintf(gp, "set output 'comparaison_populations.png'\n");
    fprintf(gp, "set title 'Évolution selon les conditions initiales'\n");
    fprintf(gp, "set xlabel 'Années'\n");
    fprintf(gp, "set ylabel 'Population totale'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set key top left\n");
    fprintf(gp, "plot 'comparaison_data.dat' u 1:2 w lp lw 2 title '10×10', \\\n");
    fprintf(gp, "     'comparaison_data.dat' u 1:3 w lp lw 2 title '50×50', \\\n");
    fprintf(gp, "     'comparaison_data.dat' u 1:4 w lp lw 2 title '100×100'\n");

    fclose(gp);

    if (system("gnuplot plot_comparaison.gp") == 0)
    {
        printf("✓ Graphique généré : comparaison_populations.png\n");
    }
}

/**
 * @brief Génère un graphique de variabilité
 */
void graphique_variabilite()
{
    printf("\n=== Génération graphique de variabilité ===\n");

    int nb_rep = 8;      // Réduit de 10 à 8
    int annees_max = 12; // Réduit de 15 à 12

    FILE *f = fopen("variabilite_data.dat", "w");
    if (!f)
        return;

    fprintf(f, "# Annees");
    for (int rep = 0; rep < nb_rep; rep++)
    {
        fprintf(f, " Rep%d", rep + 1);
    }
    fprintf(f, "\n");

    for (int annee = 0; annee <= annees_max; annee++)
    {
        fprintf(f, "%d", annee);

        if (annee % 5 == 0)
        {
            printf("  Année %d...", annee);
            fflush(stdout);
        }

        for (int rep = 0; rep < nb_rep; rep++)
        {
            unsigned long pop = simuler_finale(100, 100, annee, 7000 + rep * 100);
            fprintf(f, " %lu", pop);
        }
        fprintf(f, "\n");

        if (annee % 5 == 0)
            printf(" OK\n");
    }

    fclose(f);

    // Script gnuplot
    FILE *gp = fopen("plot_variabilite.gp", "w");
    if (!gp)
        return;

    fprintf(gp, "set terminal png size 1200,800 font 'Arial,14'\n");
    fprintf(gp, "set output 'variabilite_populations.png'\n");
    fprintf(gp, "set title 'Variabilité stochastique (100×100, 10 réplications)'\n");
    fprintf(gp, "set xlabel 'Années'\n");
    fprintf(gp, "set ylabel 'Population totale'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set key outside\n");
    fprintf(gp, "plot ");

    for (int rep = 0; rep < nb_rep; rep++)
    {
        fprintf(gp, "'variabilite_data.dat' u 1:%d w l lw 1.5 title 'Rep %d'",
                rep + 2, rep + 1);
        if (rep < nb_rep - 1)
            fprintf(gp, ", \\\n     ");
    }
    fprintf(gp, "\n");

    fclose(gp);

    if (system("gnuplot plot_variabilite.gp") == 0)
    {
        printf("✓ Graphique généré : variabilite_populations.png\n");
    }
}

/**
 * @brief Programme principal
 */
int main()
{
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║  Génération de graphiques - Simulation Lapins ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");

    // Initialiser les paramètres
    init_prob_litter();
    init_survival_rate();

    // Générer les graphiques
    graphique_comparaison_simple();
    graphique_variabilite();
    graphique_boxplot();

    printf("\n=== Tous les graphiques générés ! ===\n");
    printf("\nFichiers PNG créés :\n");
    printf("  • comparaison_populations.png - Comparaison 3 conditions\n");
    printf("  • variabilite_populations.png - Variabilité stochastique\n");
    printf("  • boxplot_populations.png     - Distribution finale\n");
    printf("\nFichiers de données (.dat) et scripts gnuplot (.gp) disponibles.\n");

    return 0;
}
