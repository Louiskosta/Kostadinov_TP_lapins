/**
 * @file simulation.h
 * @brief Fichier d'en-tête principal pour la simulation de population de lapins
 *
 * Ce fichier contient les définitions de structures et les déclarations de fonctions
 * nécessaires pour la simulation de croissance d'une population de lapins.
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdio.h>
#include <stdlib.h>
#include "mt19937ar-cok/mt19937ar-cok.h"
#include <gmp.h>

#define AGE_MAX 16   // Âge maximum des lapins en années
#define NB_MONTHS 12 // Nombre de mois dans une année

// Tableau de probabilités pour le nombre de portées par an
extern double prob_litter[10];

/**
 * @struct mois_lapin
 * @brief Représente la population de lapins pour un mois et un âge donnés
 */
typedef struct mois_lapin
{
    mpz_t nb_babies;                               // Nombre de bébés (non-matures)
    mpz_t nb_male;                                 // Nombre de mâles adultes
    mpz_t femelles_par_accouchements_restants[10]; // Femelles groupées par nombre d'accouchements restants
} mois_lapin;

/**
 * @struct population
 * @brief Représente l'ensemble de la population de lapins
 */
typedef struct population
{
    mois_lapin lapins_par_age[AGE_MAX + 1][NB_MONTHS]; // Population organisée par âge et mois
} population;

// Déclarations de fonctions
void init_prob_litter();
int litter_per_year();
population *simulate_population(mpz_t nbFemale, mpz_t nbMale, int years);
void init_survival_rate();

#endif