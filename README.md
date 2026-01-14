# Simulation de Population de Lapins

Ce projet contient deux programmes de simulation de croissance de populations de lapins.

## 1. Simulation de Fibonacci (fibo.c)

Programme simple illustrant le problème classique de Leonardo de Pise (Fibonacci).

### Modèle
- Un couple de jeunes lapins devient adulte en 1 mois
- Un couple adulte produit 1 nouveau couple de jeunes chaque mois
- Les lapins ne meurent jamais

### Compilation et exécution
```bash
gcc -Wall -Wextra -std=c17 fibo.c -o fibo
./fibo [nombre_de_mois]
```

Par défaut, simule 12 mois. Exemple :
```bash
./fibo 20    # Simule 20 mois
```

## 2. Simulation Réaliste (exe)

Programme de simulation complexe avec paramètres biologiques réalistes :
- Mortalité selon l'âge
- Nombre de portées variable
- Taille des portées aléatoire
- Maturation progressive des bébés
- Gestion de très grandes populations avec GMP

### Dépendances
- GMP (GNU Multiple Precision)
- MPFR (Multiple Precision Floating-Point)

### Compilation
```bash
make
```

### Exécution
```bash
./exe
```

## Structure du projet

```
.
├── fibo.c              # Simulation simple de Fibonacci
├── main.c              # Point d'entrée de la simulation réaliste
├── simulation.c/h      # Moteur de simulation
├── config.c/h          # Configuration des paramètres
├── population.c/h      # Gestion de la population
├── aging.c/h           # Vieillissement et maturation
├── reproduction.c/h    # Logique de reproduction
├── mt19937ar-cok/      # Générateur de nombres aléatoires
├── makefile            # Fichier de compilation
├── Doxyfile            # Configuration Doxygen
└── docs/               # Documentation générée
```

## Documentation

Pour générer la documentation HTML avec Doxygen :
```bash
doxygen Doxyfile
```

La documentation sera disponible dans `docs/html/index.html`.

## Références

- [Fibonacci et les lapins](https://r-knott.surrey.ac.uk/Fibonacci/fibnat.html)
- Modèle de croissance exponentielle de populations
