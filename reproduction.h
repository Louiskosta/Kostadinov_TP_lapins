/**
 * @file reproduction.h
 * @brief Fichier d'en-tête pour la gestion de la reproduction
 *
 * Ce fichier déclare les fonctions liées à la reproduction des lapins
 * (nombre de portées, taille des portées, processus de reproduction).
 */

#ifndef REPRODUCTION_H
#define REPRODUCTION_H

#include "simulation.h"

/**
 * @brief Tire aléatoirement le nombre de portées d'une femelle pour l'année
 * @return Nombre de portées (entre 0 et 9)
 */
int litter_per_year();

/**
 * @brief Tire aléatoirement la taille d'une portée
 * @return Nombre de bébés dans la portée (entre 3 et 6)
 */
int accouchement();

/**
 * @brief Simule la reproduction de toute la population pour un mois
 * @param pop Pointeur vers la population
 * @param new_babies Variable où stocker le nombre total de nouveaux bébés
 */
void reproduction(population *pop, mpz_t new_babies);

#endif // REPRODUCTION_H
