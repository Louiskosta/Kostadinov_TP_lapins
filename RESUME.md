# Résumé du Projet - Simulation de Population de Lapins

## 🎯 Objectif
Simuler la croissance d'une population de lapins avec des paramètres biologiques réalistes et analyser la variabilité stochastique.

## � Structure du Projet

```
TP_lapins/
├── src/                      # Code source
│   ├── core/                 # Modules principaux de simulation
│   │   ├── simulation.c/h    # Moteur de simulation
│   │   ├── config.c/h        # Paramètres biologiques
│   │   ├── population.c/h    # Gestion de la population
│   │   ├── aging.c/h         # Vieillissement et mortalité
│   │   └── reproduction.c/h  # Reproduction et naissances
│   ├── programs/             # Programmes exécutables
│   │   ├── main.c            # Simulation simple
│   │   ├── fibo.c            # Modèle de Fibonacci
│   │   ├── experiments.c     # Expériences multiples
│   │   └── graphiques.c      # Génération de graphiques
│   └── external/             # Bibliothèques externes
│       └── mt19937ar-cok/    # Générateur aléatoire Mersenne Twister
├── build/                    # Fichiers objets (.o)
├── bin/                      # Exécutables compilés
│   ├── exe                   # Simulation réaliste
│   ├── fibo                  # Fibonacci
│   ├── experiments           # Expériences
│   └── graphiques            # Graphiques
├── data/                     # Données et graphiques générés
│   ├── *.dat                 # Fichiers de données
│   ├── *.gp                  # Scripts gnuplot
│   └── *.png                 # Graphiques PNG
├── docs/                     # Documentation
│   ├── html/                 # Documentation Doxygen
│   └── guide/                # Guides et rapports
│       ├── README.md         # Guide complet
│       ├── GUIDE_GRAPHIQUES.md  # Interprétation des graphiques
│       ├── RAPPORT.md        # Template de rapport
│       └── TODO.md           # Liste des tâches
├── makefile                  # Automatisation de la compilation
├── Doxyfile                  # Configuration Doxygen
├── .gitignore               # Fichiers à ignorer par Git
└── RESUME.md                # Ce fichier
```

## 🔧 Compilation

```bash
# Compiler tous les programmes
make

# Compiler un programme spécifique
make bin/exe
make bin/fibo
make bin/experiments
make bin/graphiques

# Nettoyer les fichiers compilés
make clean

# Nettoyer tout (y compris les données)
make clean-all
```

## 🚀 Utilisation Rapide

```bash
# 1. Simulation simple de Fibonacci
make run-fibo

# 2. Simulation réaliste (100+100 lapins, 100 ans)
make run-exe

# 3. Expériences multiples avec statistiques
make run-experiments

# 4. Générer les graphiques d'analyse
make run-graphiques
```

## 📊 Programmes Disponibles

## 📊 Programmes Disponibles

| Exécutable | Localisation | Description | Usage |
|------------|-------------|-------------|-------|
| `exe` | `bin/exe` | Simulation réaliste simple | `make run-exe` ou `bin/exe` |
| `fibo` | `bin/fibo` | Modèle de Fibonacci | `make run-fibo` ou `bin/fibo 20` |
| `experiments` | `bin/experiments` | Expériences multiples + stats | `make run-experiments` |
| `graphiques` | `bin/graphiques` | Génération de graphiques | `make run-graphiques` |

## 📊 Graphiques Générés

Après avoir exécuté `./graphiques`, vous obtenez :

1. **data/comparaison_populations.png**
   - Évolution pour 3 conditions initiales (10×10, 50×50, 100×100)
   - Montre la croissance exponentielle
   
2. **data/variabilite_populations.png**
   - 8 réplications indépendantes (100×100 lapins)
   - Illustre la variabilité stochastique
   
3. **data/boxplot_populations.png**
   - Distribution des populations finales
   - Basé sur 15 réplications par condition

Tous les fichiers de données (`.dat`) et scripts gnuplot (`.gp`) sont également dans `data/`.

## 📈 Paramètres Biologiques

- **Survie annuelle** :
  - 0-1 an : 79%
  - 1-2 ans : 77%
  - 2-3 ans : 72%
  - etc. (décroit avec l'âge)

- **Portées par an** : 0 à 9 (distribution de probabilité)
- **Taille de portée** : 3 à 6 bébés
- **Maturation** : 12 mois
- **Sexe ratio** : 50/50

## 🔬 Analyses Possibles

### 1. Taux de Croissance
```
Ajustement exponentiel : N(t) = N₀ × e^(rt)
Calculer r à partir des données
```

### 2. Variabilité
```
Coefficient de variation : CV = σ / μ
Évolution du CV avec le temps
```

### 3. Prédictibilité
```
Intervalle de confiance à 95%
Largeur de l'IC en fonction du temps
```

### 4. Impact des Conditions Initiales
```
Temps pour atteindre 1 million de lapins
Différence relative entre conditions
```

## 📝 Structure des Données

```c
typedef struct mois_lapin {
    mpz_t nb_babies;                      // Bébés non-matures
    mpz_t nb_male;                        // Mâles adultes
    mpz_t femelles_par_accouchements[10]; // Femelles par nb portées
} mois_lapin;

typedef struct population {
    mois_lapin lapins_par_age[17][12];    // [âge][mois]
} population;
```

## 🧮 Bibliothèques Utilisées

- **GMP** : Arithmétique de précision arbitraire (grandes populations)
- **MPFR** : Calculs en virgule flottante de précision arbitraire
- **mt19937ar** : Générateur de nombres pseudo-aléatoires de haute qualité

### Pour le Rapport

1. Inclure les 3 graphiques PNG depuis `data/`
2. Analyser :
   - Taux de croissance observé
   - Variabilité stochastique
   - Impact des conditions initiales
   - Limites du modèle
3. Répondre aux questions théoriques
4. Discuter de la prédictibilité à long terme

Voir `docs/guide/GUIDE_GRAPHIQUES.md` pour les détails d'interprétation.

## 🔍 Vérifications

```bash
# Vérifier que tout compile
make clean && make

# Afficher l'aide
make help

# Tester chaque programme
make run-fibo
make run-exe | head -20
make run-experiments | tail -30
make run-graphiques

# Vérifier les graphiques générés
ls -lh data/*.png

# Générer la documentation
make doc
firefox docs/html/index.html
```

## 📌 Avantages de la Nouvelle Structure

✅ **Séparation claire** : code source, binaires, données
✅ **Modularité** : core/programs/external bien séparés
✅ **Propreté** : build/ contient tous les .o
✅ **Organisation** : documentation centralisée dans docs/
✅ **Maintenabilité** : facile de trouver et modifier les fichiers
✅ **Professionnalisme** : structure standard de projet C

## 📌 Points Clés

✅ Modèle stochastique réaliste
✅ Gestion de grandes populations (milliards)
✅ Visualisations automatiques
✅ Code modulaire et documenté
✅ Analyses statistiques intégrées

## 🎓 Concepts Illustrés

- Croissance exponentielle
- Variabilité stochastique
- Processus de Markov
- Modélisation démographique
- Analyses Monte Carlo
- Visualisation scientifique

## 🆘 Problèmes Courants

**Erreur "undefined reference to mpz_..."**
```bash
sudo apt-get install libgmp-dev libmpfr-dev
```

**Erreur "gnuplot: command not found"**
```bash
sudo apt-get install gnuplot
```

**Crash mémoire**
- Réduire le nombre d'années
- Réduire le nombre de réplications
- Vérifier la libération de la mémoire

## 📧 Fichiers Importants

```
TP_lapins/
├── makefile             # Automatisation (make help pour voir les commandes)
├── Doxyfile             # Configuration de la documentation
├── .gitignore           # Fichiers ignorés par Git
├── RESUME.md            # Ce fichier
├── src/                 # Code source
│   ├── core/            # 5 modules principaux
│   ├── programs/        # 4 programmes
│   └── external/        # mt19937ar-cok
├── bin/                 # 4 exécutables
├── build/               # Fichiers .o (temporaires)
├── data/                # Graphiques et données générées
└── docs/                # Documentation complète
    ├── html/            # Doxygen
    └── guide/           # 4 fichiers markdown
```

---

**Projet** : TP Simulation Stochastique  
**Structure mise à jour** : 2025-01-14  
**Langage** : C17  
**Outils** : GCC, GMP, MPFR, Gnuplot, Doxygen
