#ifndef MT19937AR_COK_H
#define MT19937AR_COK_H

#include <gmp.h>
#include <mpfr.h>

void init_genrand(unsigned long s);
unsigned long genrand_int32(void);
long genrand_int31(void);
double genrand_real1(void);
int uniform_int(int a, int b);
void binomial_gaussian(mpz_t result, mpz_t n, double p);
mpz_t *multinomial_gaussian(mpz_t tEchantillon, double probs_cumul[], int nbCategories);

#endif
