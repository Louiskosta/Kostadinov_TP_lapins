/*
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mt19937ar-cok.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti = N + 1;     /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0] = s & 0xffffffffUL;
    for (mti = 1; mti < N; mti++)
    {
        mt[mti] =
            (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i = 1;
    j = 0;
    k = (N > key_length ? N : key_length);
    for (; k; k--)
    {
        mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1664525UL)) + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL;                                                             /* for WORDSIZE > 32 machines */
        i++;
        j++;
        if (i >= N)
        {
            mt[0] = mt[N - 1];
            i = 1;
        }
        if (j >= key_length)
            j = 0;
    }
    for (k = N - 1; k; k--)
    {
        mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1566083941UL)) - i; /* non linear */
        mt[i] &= 0xffffffffUL;                                                  /* for WORDSIZE > 32 machines */
        i++;
        if (i >= N)
        {
            mt[0] = mt[N - 1];
            i = 1;
        }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2] = {0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N)
    { /* generate N words at one time */
        int kk;

        if (mti == N + 1)         /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk = 0; kk < N - M; kk++)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (; kk < N - 1; kk++)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32() >> 1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32() * (1.0 / 4294967295.0);
    /* divided by 2^32-1 */
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32() * (1.0 / 4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5) * (1.0 / 4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void)
{
    unsigned long a = genrand_int32() >> 5, b = genrand_int32() >> 6;
    return (a * 67108864.0 + b) * (1.0 / 9007199254740992.0);
}

int uniform_int(int a, int b)
{
    return a + (int)(genrand_real1() * (b - a + 1));
}

double normal_centree_reduite()
{

    double u1 = genrand_real1();
    double u2 = genrand_real1();

    return sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}

void normal(mpfr_t result, mpfr_t mean, mpfr_t sd)
{
    mpfr_init_set(result, sd, MPFR_RNDN);
    mpfr_mul_d(result, result, normal_centree_reduite(), MPFR_RNDN);
    mpfr_add(result, result, mean, MPFR_RNDN);
}

void binomial_gaussian(mpz_t result, mpz_t n, double p)
{
    mpfr_t mean;
    mpfr_init(mean);
    mpfr_set_z(mean, n, MPFR_RNDN);
    mpfr_mul_d(mean, mean, p, MPFR_RNDN);

    // sd = sqrt(n * p * (1.0 - p))
    mpfr_t sd;
    mpfr_init(sd);
    mpfr_set_z(sd, n, MPFR_RNDN);
    mpfr_mul_d(sd, sd, p, MPFR_RNDN);
    mpfr_mul_d(sd, sd, 1.0 - p, MPFR_RNDN);
    mpfr_sqrt(sd, sd, MPFR_RNDN);

    // tirage gaussien
    mpfr_t x;
    mpfr_init(x);
    normal(x, mean, sd);

    // bornes (une gaussienne peut sortir de [0,n])
    mpfr_t zero, n_mpfr;
    mpfr_init_set_ui(zero, 0, MPFR_RNDN);
    mpfr_init_set_z(n_mpfr, n, MPFR_RNDN);

    if (mpfr_cmp(x, zero) < 0)
        mpfr_set(x, zero, MPFR_RNDN);
    if (mpfr_cmp(x, n_mpfr) > 0)
        mpfr_set(x, n_mpfr, MPFR_RNDN);

    mpfr_add_d(x, x, 0.5, MPFR_RNDN); // pour arrondi
    mpfr_get_z(result, x, MPFR_RNDN);

    // Libération mémoire
    mpfr_clear(mean);
    mpfr_clear(sd);
    mpfr_clear(x);
    mpfr_clear(zero);
    mpfr_clear(n_mpfr);
}

mpz_t *multinomial_gaussian(mpz_t tEchantillon, double probs_cumul[], int nbCategories)
{
    mpz_t *counts = malloc(sizeof(mpz_t) * nbCategories);
    mpz_t total;
    mpz_init_set_ui(total, 0);

    // Première catégorie
    double p0 = probs_cumul[0];

    mpfr_t mean, variance, sd, p_val, one_minus_p, temp;
    mpfr_init(mean);
    mpfr_init(variance);
    mpfr_init(sd);
    mpfr_init(p_val);
    mpfr_init(one_minus_p);
    mpfr_init(temp);

    // mean = tEchantillon * p0
    mpfr_set_z(mean, tEchantillon, MPFR_RNDN);
    mpfr_mul_d(mean, mean, p0, MPFR_RNDN);

    // variance = tEchantillon * p0 * (1.0 - p0)
    mpfr_set_d(p_val, p0, MPFR_RNDN);
    mpfr_set_ui(one_minus_p, 1, MPFR_RNDN);
    mpfr_sub(one_minus_p, one_minus_p, p_val, MPFR_RNDN);
    mpfr_set_z(variance, tEchantillon, MPFR_RNDN);
    mpfr_mul(variance, variance, p_val, MPFR_RNDN);
    mpfr_mul(variance, variance, one_minus_p, MPFR_RNDN);
    mpfr_sqrt(sd, variance, MPFR_RNDN);

    // Tirage gaussien
    mpfr_t x;
    mpfr_init(x);
    normal(x, mean, sd);

    // Bornes
    mpfr_t zero, t_mpfr;
    mpfr_init_set_ui(zero, 0, MPFR_RNDN);
    mpfr_init_set_z(t_mpfr, tEchantillon, MPFR_RNDN);

    if (mpfr_cmp(x, zero) < 0)
        mpfr_set(x, zero, MPFR_RNDN);
    if (mpfr_cmp(x, t_mpfr) > 0)
        mpfr_set(x, t_mpfr, MPFR_RNDN);

    mpfr_add_d(x, x, 0.5, MPFR_RNDN);
    mpz_init(counts[0]);
    mpfr_get_z(counts[0], x, MPFR_RNDN);
    // S'assurer que counts[0] >= 0
    if (mpz_sgn(counts[0]) < 0)
        mpz_set_ui(counts[0], 0);
    mpz_add(total, total, counts[0]);

    // Autres catégories
    for (int i = 1; i < nbCategories; i++)
    {
        double p = probs_cumul[i] - probs_cumul[i - 1];

        // mean = tEchantillon * p
        mpfr_set_z(mean, tEchantillon, MPFR_RNDN);
        mpfr_mul_d(mean, mean, p, MPFR_RNDN);

        // variance = tEchantillon * p * (1.0 - p)
        mpfr_set_d(p_val, p, MPFR_RNDN);
        mpfr_set_ui(one_minus_p, 1, MPFR_RNDN);
        mpfr_sub(one_minus_p, one_minus_p, p_val, MPFR_RNDN);
        mpfr_set_z(variance, tEchantillon, MPFR_RNDN);
        mpfr_mul(variance, variance, p_val, MPFR_RNDN);
        mpfr_mul(variance, variance, one_minus_p, MPFR_RNDN);
        mpfr_sqrt(sd, variance, MPFR_RNDN);

        // Tirage gaussien
        normal(x, mean, sd);

        if (mpfr_cmp(x, zero) < 0)
            mpfr_set(x, zero, MPFR_RNDN);

        mpfr_add_d(x, x, 0.5, MPFR_RNDN);
        mpz_init(counts[i]);
        mpfr_get_z(counts[i], x, MPFR_RNDN);
        // S'assurer que counts[i] >= 0
        if (mpz_sgn(counts[i]) < 0)
            mpz_set_ui(counts[i], 0);
        mpz_add(total, total, counts[i]);
    }

    // Correction pour que la somme = tEchantillon
    if (mpz_cmp_ui(total, 0) > 0)
    {
        mpfr_t factor;
        mpfr_init(factor);
        mpfr_set_z(factor, tEchantillon, MPFR_RNDN);
        mpfr_set_z(temp, total, MPFR_RNDN);
        mpfr_div(factor, factor, temp, MPFR_RNDN);

        mpz_set_ui(total, 0);
        for (int i = 0; i < nbCategories; i++)
        {
            mpfr_set_z(temp, counts[i], MPFR_RNDN);
            mpfr_mul(temp, temp, factor, MPFR_RNDN);
            mpfr_add_d(temp, temp, 0.5, MPFR_RNDN);
            mpfr_get_z(counts[i], temp, MPFR_RNDN);
            // S'assurer que counts[i] >= 0 après rescaling
            if (mpz_sgn(counts[i]) < 0)
                mpz_set_ui(counts[i], 0);
            mpz_add(total, total, counts[i]);
        }

        // Ajustement final si nécessaire
        mpz_t diff;
        mpz_init(diff);
        mpz_sub(diff, tEchantillon, total);
        if (mpz_cmp_ui(diff, 0) != 0 && nbCategories > 0)
        {
            mpz_add(counts[0], counts[0], diff);
            // S'assurer que counts[0] reste >= 0 après ajustement
            if (mpz_sgn(counts[0]) < 0)
                mpz_set_ui(counts[0], 0);
        }
        mpz_clear(diff);
        mpfr_clear(factor);
    }

    // Libération mémoire
    mpfr_clear(mean);
    mpfr_clear(variance);
    mpfr_clear(sd);
    mpfr_clear(p_val);
    mpfr_clear(one_minus_p);
    mpfr_clear(temp);
    mpfr_clear(x);
    mpfr_clear(zero);
    mpfr_clear(t_mpfr);
    mpz_clear(total);

    return counts;
}