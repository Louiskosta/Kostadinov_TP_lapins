/**
 * @file config.c
 * @brief Implémentation de la configuration des paramètres de simulation
 *
 * Ce fichier contient les paramètres biologiques de la simulation et les fonctions
 * pour initialiser les probabilités et taux de survie.
 */

#include "simulation.h"
#include "config.h"
#include <math.h>

// Poids initiaux pour le nombre de portées par an (indices 0 à 9)
double prob_litter[] = {0, 0, 0, 1, 1, 2, 2, 2, 1, 1};

// Probabilités de maturité des bébés par mois d'âge (0 à 10 mois)
double prob_maturity[] = {0, 0, 0, 0, 0, 0.2, 0.4, 0.6, 0.8, 1, 1};

// Taux de survie mensuels des adultes selon leur âge (7 tranches d'âge)
double survival_rate_month_adult[7];

// Taux de survie mensuel des bébés
double survival_rate_month_baby;

/**
 * @brief Initialise le tableau des probabilités de portées par an
 *
 * Transforme les poids initiaux en probabilités cumulatives.
 * Par exemple, si les poids sont [0,0,0,1,1,2,2,2,1,1], la somme est 10
 * et on obtient des probabilités cumulatives pour tirer aléatoirement.
 */
void init_prob_litter()
{
    float somme = 0;
    // Calcul de la somme des poids (indices 3 à 9 correspondent aux portées possibles)
    for (int i = 3; i <= 9; i++)
    {
        somme += prob_litter[i];
    }
    // Conversion en probabilités cumulatives
    for (int i = 1; i <= 9; i++)
    {
        prob_litter[i] = prob_litter[i] / somme + prob_litter[i - 1];
    }
}

/**
 * @brief Initialise les taux de survie mensuels
 *
 * Calcule les taux de survie mensuels à partir des taux annuels:
 * - Adultes: 7 tranches d'âge avec des taux décroissants (60%, 50%, ..., 0%)
 * - Bébés: taux de survie global de 35% sur 8 mois
 */
void init_survival_rate()
{
    // Calcul des taux de survie mensuels pour les adultes selon leur âge
    for (int i = 0; i < 7; i++)
    {
        double rate = 0.6 - i * 0.1; // Taux annuel: 60% -> 50% -> ... -> 0%
        if (rate < 0)
            rate = 0;
        // Conversion en taux mensuel (racine 12ème du taux annuel)
        survival_rate_month_adult[i] = pow(rate, 1.0 / 12.0);
    }
    // Taux de survie mensuel des bébés (35% de survie sur 8 mois)
    survival_rate_month_baby = pow(0.35, 1.0 / 8.0);
}

/**
 * @brief Retourne le taux de survie mensuel d'un adulte selon son âge
 *
 * @param year Âge du lapin en années
 * @return Taux de survie mensuel (probabilité entre 0 et 1)
 *
 * Les lapins de moins de 10 ans ont le meilleur taux de survie.
 * Au-delà, le taux diminue progressivement jusqu'à 0 après 16 ans.
 */
double survival_rate_adult(int year)
{
    if (year < 10)
        return survival_rate_month_adult[0]; // Jeunes adultes (meilleur taux)
    int index = year - 10;
    if (index >= 7)
        index = 6; // Adultes très âgés (taux minimum)
    return survival_rate_month_adult[index];
}
