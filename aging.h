/**
 * @file aging.h
 * @brief Fichier d'en-tête pour la gestion du vieillissement
 *
 * Ce fichier déclare les fonctions liées au vieillissement de la population
 * (survie, maturation des bébés, passage au mois suivant).
 */

#ifndef AGING_H
#define AGING_H

#include "simulation.h"

/**
 * @brief Simule le vieillissement de toute la population d'un mois
 *
 * Cette fonction gère:
 * - Le vieillissement des mâles et femelles adultes
 * - La maturation des bébés
 * - La mortalité selon l'âge
 *
 * @param pop Pointeur vers la population à faire vieillir
 */
void aging(population *pop);

#endif // AGING_H
