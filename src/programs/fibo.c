/**
 * @file fibo.c
 * @brief Simulation du problème classique de Fibonacci (Leonardo de Pise)
 *
 * Modèle simple de croissance de lapins :
 * - Un couple de jeunes lapins devient adulte en 1 mois
 * - Un couple adulte produit 1 nouveau couple de jeunes chaque mois
 * - Les lapins ne meurent jamais
 *
 * Référence : https://r-knott.surrey.ac.uk/Fibonacci/fibnat.html
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Simule l'évolution de la population de lapins selon le modèle de Fibonacci
 *
 * @param months Nombre de mois à simuler
 */
void fibonacci_rabbits(int months)
{
    long long young = 1; // Couples de jeunes lapins (nouveau-nés)
    long long adult = 0; // Couples de lapins adultes
    long long total;

    printf("\n===== SIMULATION DE FIBONACCI - POPULATION DE LAPINS =====\n\n");
    printf("Règles :\n");
    printf("- Un couple de jeunes devient adulte en 1 mois\n");
    printf("- Un couple adulte produit 1 nouveau couple de jeunes par mois\n");
    printf("- Les lapins ne meurent pas\n\n");
    printf("%-10s %-15s %-15s %-15s\n", "Mois", "Jeunes", "Adultes", "Total");
    printf("------------------------------------------------------------\n");

    for (int month = 0; month <= months; month++)
    {
        total = young + adult;
        printf("%-10d %-15lld %-15lld %-15lld\n", month, young, adult, total);

        // Simulation du mois suivant
        long long new_young = adult;         // Les adultes produisent de nouveaux jeunes
        long long new_adult = adult + young; // Les jeunes deviennent adultes + les adultes restent

        young = new_young;
        adult = new_adult;
    }

    printf("\n");
}

/**
 * @brief Affiche la suite de Fibonacci classique pour comparaison
 *
 * @param n Nombre de termes à afficher
 */
void fibonacci_sequence(int n)
{
    printf("\n===== SUITE DE FIBONACCI CLASSIQUE =====\n\n");
    printf("F(0) = 1\n");
    printf("F(1) = 1\n");

    long long fib_prev2 = 1; // F(n-2)
    long long fib_prev1 = 1; // F(n-1)
    long long fib_current;

    for (int i = 2; i <= n; i++)
    {
        fib_current = fib_prev1 + fib_prev2;
        printf("F(%d) = %lld\n", i, fib_current);

        fib_prev2 = fib_prev1;
        fib_prev1 = fib_current;
    }

    printf("\n");
}

/**
 * @brief Point d'entrée du programme
 */
int main(int argc, char *argv[])
{
    int months = 12; // Par défaut, simuler 12 mois

    // Permettre de spécifier le nombre de mois en argument
    if (argc > 1)
    {
        months = atoi(argv[1]);
        if (months < 0 || months > 50)
        {
            printf("Erreur : le nombre de mois doit être entre 0 et 50\n");
            return 1;
        }
    }

    // Simulation de la population de lapins
    fibonacci_rabbits(months);

    // Affichage de la suite de Fibonacci pour vérification
    fibonacci_sequence(months);

    printf("Note : Le total de lapins au mois n correspond à F(n+1)\n");
    printf("       (décalage d'un rang car on commence avec 1 couple au mois 0)\n\n");

    return 0;
}
