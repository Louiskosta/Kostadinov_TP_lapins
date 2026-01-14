#include "simulation.h"
#include "config.h"
#include <math.h>

double prob_litter[] = {0, 0, 0, 1, 1, 2, 2, 2, 1, 1};
double prob_maturity[] = {0, 0, 0, 0, 0, 0.2, 0.4, 0.6, 0.8, 1, 1};
double survival_rate_month_adult[7];
double survival_rate_month_baby;

void init_prob_litter()
{
    float somme = 0;
    for (int i = 3; i <= 9; i++)
    {
        somme += prob_litter[i];
    }
    for (int i = 1; i <= 9; i++)
    {
        prob_litter[i] = prob_litter[i] / somme + prob_litter[i - 1];
    }
}

void init_survival_rate()
{
    for (int i = 0; i < 7; i++)
    {
        double rate = 0.6 - i * 0.1;
        if (rate < 0)
            rate = 0;
        survival_rate_month_adult[i] = pow(rate, 1.0 / 12.0);
    }
    survival_rate_month_baby = pow(0.35, 1.0 / 8.0);
}

double survival_rate_adult(int year)
{
    if (year < 10)
        return survival_rate_month_adult[0];
    int index = year - 10;
    if (index >= 7)
        index = 6;
    return survival_rate_month_adult[index];
}
