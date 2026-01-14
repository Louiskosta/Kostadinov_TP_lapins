#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdio.h>
#include <stdlib.h>
#include "mt19937ar-cok/mt19937ar-cok.h"
#include <gmp.h>

#define AGE_MAX 16
#define NB_MONTHS 12

extern double prob_litter[10];

typedef struct mois_lapin
{
    mpz_t nb_babies;
    mpz_t nb_male;
    mpz_t femelles_par_accouchements_restants[10];
} mois_lapin;

typedef struct population
{
    mois_lapin lapins_par_age[AGE_MAX + 1][NB_MONTHS];
} population;

void init_prob_litter();
int litter_per_year();
population *simulate_population(mpz_t nbFemale, mpz_t nbMale, int years);
void init_survival_rate();

#endif