/**
 * @file config.h
 * @brief Fichier d'en-tête pour la configuration des paramètres de simulation
 *
 * Ce fichier déclare les fonctions d'initialisation et de calcul des paramètres
 * biologiques de la simulation (probabilités de portée, taux de survie).
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief Initialise le tableau des probabilités de portées par an
 *
 * Transforme les poids en probabilités cumulatives pour permettre
 * un tirage aléatoire du nombre de portées.
 */
void init_prob_litter();

/**
 * @brief Initialise les taux de survie mensuels pour adultes et bébés
 *
 * Calcule les taux de survie mensuels à partir des taux annuels en utilisant
 * une formule de racine 12ème pour les adultes et 8ème pour les bébés.
 */
void init_survival_rate();

/**
 * @brief Calcule le taux de survie mensuel d'un adulte selon son âge
 * @param year Âge du lapin en années
 * @return Taux de survie mensuel (probabilité entre 0 et 1)
 */
double survival_rate_adult(int year);

#endif // CONFIG_H
