/**
 * @file main.c
 * @brief Point d'entrée du programme de simulation de population de lapins
 *
 * Ce programme simule la croissance d'une population de lapins sur plusieurs années
 * en utilisant la bibliothèque GMP pour gérer les grands nombres.
 */

#include "simulation.h"
#include "population.h"
#include <time.h>

/**
 * @brief Fonction principale du programme
 * @return 0 en cas de succès
 */
int main()
{
    // Initialisation des taux de survie et probabilités
    init_survival_rate();
    init_prob_litter();

    // Initialisation de la population de départ (100 femelles et 100 mâles)
    mpz_t nbFemale, nbMale;
    mpz_init_set_ui(nbFemale, 100);
    mpz_init_set_ui(nbMale, 100);

    // Simulation sur 100 ans
    population *pop = simulate_population(nbFemale, nbMale, 100);

    // Affichage de la population finale
    printf("\n===== POPULATION FINALE (après 100 ans) =====\n");
    afficher_pop(pop, 1);

    // Nettoyage de la mémoire
    mpz_clear(nbFemale);
    mpz_clear(nbMale);
    free(pop);

    return 0;
}