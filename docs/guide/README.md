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
./exe              # Une simulation simple
./experiments      # Expérimentations multiples avec statistiques
./graphiques       # Génère les graphiques d'analyse
```

## 3. Programme de Génération de Graphiques (graphiques)

Programme qui génère automatiquement des graphiques d'analyse avec gnuplot.

### Fonctionnalités
- **Comparaison des conditions initiales** : compare l'évolution pour 10×10, 50×50 et 100×100 lapins
- **Variabilité stochastique** : montre la variabilité entre plusieurs réplications
- **Distribution des populations finales** : boxplot montrant la distribution après N années

### Graphiques générés
- `comparaison_populations.png` : évolution de la population selon les conditions initiales
- `variabilite_populations.png` : variabilité entre réplications (100×100 lapins)
- `boxplot_populations.png` : distribution des populations finales

### Fichiers de données
- `comparaison_data.dat` : données pour le graphique de comparaison
- `variabilite_data.dat` : données de variabilité
- `boxplot_data.dat` : données pour le boxplot
- `plot_*.gp` : scripts gnuplot correspondants

### Exécution
```bash
./graphiques
```

Les graphiques PNG sont générés dans le répertoire courant.

## 4. Programme d'Expérimentations (experiments)

Lance plusieurs simulations avec différentes conditions initiales pour analyser la variabilité stochastique. Calcule les statistiques (moyenne, écart-type, min, max).

### Exécution
```bash
./experiments
```

Ce programme lance automatiquement plusieurs séries d'expériences et affiche les résultats statistiques.

## Structure du projet

```
.
├── fibo.c              # Simulation simple de Fibonacci
├── main.c              # Point d'entrée de la simulation réaliste
├── experiments.c       # Programme d'expérimentations multiples
├── simulation.c/h      # Moteur de simulation
├── config.c/h          # Configuration des paramètres
├── population.c/h      # Gestion de la population
├── aging.c/h           # Vieillissement et maturation
├── reproduction.c/h    # Logique de reproduction
├── mt19937ar-cok/      # Générateur de nombres aléatoires
├── makefile            # Fichier de compilation
├── Doxyfile            # Configuration Doxygen
├── RAPPORT.md          # Template de rapport
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
