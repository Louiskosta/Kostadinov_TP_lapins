/**
 * @file simulation.c
 * @brief Implémentation du moteur de simulation
 *
 * Ce fichier contient les fonctions principales qui orchestrent la simulation
 * de la population de lapins sur plusieurs années.
 */

#include "simulation.h"
#include "population.h"
#include "reproduction.h"
#include "aging.h"

/**
 * @brief Simule un mois de vie de la population
 *
 * Cette fonction effectue les étapes suivantes:
 * 1. Calcule les naissances du mois (reproduction)
 * 2. Fait vieillir tous les lapins d'un mois
 * 3. Ajoute les nouveaux-nés à la population
 *
 * @param pop Pointeur vers la population à simuler
 */
void simulate_month(population *pop)
{
    mpz_t new_babies;
    mpz_init(new_babies);

    // Étape 1: Reproduction - calcul des naissances
    reproduction(pop, new_babies);

    // Étape 2: Vieillissement - survie et maturation
    aging(pop);

    // Étape 3: Ajout des nouveaux-nés
    mpz_set(pop->lapins_par_age[0][0].nb_babies, new_babies);

    mpz_clear(new_babies);
}

/**
 * @brief Simule une année complète de vie de la population
 *
 * Exécute la simulation pour les 12 mois de l'année.
 *
 * @param pop Pointeur vers la population à simuler
 */
void simulate_year(population *pop)
{
    for (int m = 0; m < NB_MONTHS; m++)
    {
        simulate_month(pop);
    }
}

/**
 * @brief Lance la simulation complète sur plusieurs années
 *
 * Initialise la population de départ et simule son évolution
 * sur le nombre d'années spécifié. Affiche les statistiques
 * à la fin de chaque année.
 *
 * @param nbFemale Nombre initial de femelles
 * @param nbMale Nombre initial de mâles
 * @param years Nombre d'années à simuler
 * @return Pointeur vers la population finale
 */
population *simulate_population(mpz_t nbFemale, mpz_t nbMale, int years)
{
    // Initialisation de la population de départ
    population *pop = initialize_population(nbFemale, nbMale);

    // Simulation année par année
    for (int y = 0; y < years; y++)
    {
        simulate_year(pop);

        // Affichage des statistiques annuelles
        printf("ANNEE %d : ", y + 1);
        afficher_pop(pop, 1);
        fflush(stdout);
    }

    return pop;
}
