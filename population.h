#ifndef POPULATION_H
#define POPULATION_H

#include "simulation.h"

population *initialize_population(mpz_t nbFemale, mpz_t nbMale);
void afficher_pop(population *pop, int mode);

#endif // POPULATION_H
