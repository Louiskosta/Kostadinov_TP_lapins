#ifndef REPRODUCTION_H
#define REPRODUCTION_H

#include "simulation.h"

int litter_per_year();
int accouchement();
void reproduction(population *pop, mpz_t new_babies);

#endif // REPRODUCTION_H
