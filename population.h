/**
 * @file population.h
 * @brief Fichier d'en-tête pour la gestion de la population
 *
 * Ce fichier déclare les fonctions pour initialiser et afficher
 * les données de la population de lapins.
 */

#ifndef POPULATION_H
#define POPULATION_H

#include "simulation.h"

/**
 * @brief Initialise une nouvelle population de lapins
 * @param nbFemale Nombre initial de femelles
 * @param nbMale Nombre initial de mâles
 * @return Pointeur vers la structure population allouée
 */
population *initialize_population(mpz_t nbFemale, mpz_t nbMale);

/**
 * @brief Affiche les statistiques de la population
 * @param pop Pointeur vers la population à afficher
 * @param mode Mode d'affichage (0: détaillé, 1: résumé)
 */
void afficher_pop(population *pop, int mode);

#endif // POPULATION_H
