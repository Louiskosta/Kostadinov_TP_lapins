# Structure du Projet

```
TP_lapins/
│
├── 📄 README.md                    # Guide de démarrage rapide
├── 📄 RESUME.md                    # Résumé complet du projet
├── 📄 .gitignore                   # Fichiers ignorés par Git
├── 📄 .editorconfig                # Configuration de l'éditeur
├── 📄 makefile                     # Automatisation de la compilation
├── 📄 Doxyfile                     # Configuration Doxygen
│
├── 📁 src/                         # CODE SOURCE
│   │
│   ├── 📁 core/                    # Modules principaux (10 fichiers)
│   │   ├── simulation.c/h          # Moteur de simulation principal
│   │   ├── config.c/h              # Paramètres biologiques
│   │   ├── population.c/h          # Gestion de la population
│   │   ├── aging.c/h               # Vieillissement et mortalité
│   │   └── reproduction.c/h        # Reproduction et naissances
│   │
│   ├── 📁 programs/                # Programmes principaux (4 fichiers)
│   │   ├── main.c                  # → bin/exe (simulation simple)
│   │   ├── fibo.c                  # → bin/fibo (Fibonacci)
│   │   ├── experiments.c           # → bin/experiments
│   │   └── graphiques.c            # → bin/graphiques
│   │
│   └── 📁 external/                # Bibliothèques externes
│       └── mt19937ar-cok/          # Générateur aléatoire Mersenne Twister
│           ├── mt19937ar-cok.c
│           ├── mt19937ar-cok.h
│           └── readme-mt.txt
│
├── 📁 build/                       # Fichiers objets (.o)
│   ├── aging.o
│   ├── config.o
│   ├── population.o
│   ├── reproduction.o
│   ├── simulation.o
│   ├── mt19937ar-cok.o
│   ├── main.o
│   ├── fibo.o
│   ├── experiments.o
│   └── graphiques.o
│
├── 📁 bin/                         # Exécutables compilés
│   ├── exe                         # Simulation réaliste (100+100 lapins, 100 ans)
│   ├── fibo                        # Modèle de Fibonacci
│   ├── experiments                 # Expériences multiples avec stats
│   └── graphiques                  # Génération de graphiques
│
├── 📁 data/                        # Données et graphiques générés
│   ├── comparaison_data.dat
│   ├── variabilite_data.dat
│   ├── boxplot_data.dat
│   ├── plot_comparaison.gp
│   ├── plot_variabilite.gp
│   ├── plot_boxplot.gp
│   ├── comparaison_populations.png
│   ├── variabilite_populations.png
│   └── boxplot_populations.png
│
└── 📁 docs/                        # Documentation
    ├── 📁 html/                    # Documentation Doxygen
    │   └── index.html              # (généré par `make doc`)
    │
    └── 📁 guide/                   # Guides utilisateur
        ├── README.md               # Guide d'utilisation complet
        ├── GUIDE_GRAPHIQUES.md     # Interprétation des graphiques
        ├── RAPPORT.md              # Template de rapport de TP
        └── TODO.md                 # Liste des tâches

```

## 📊 Flux de Données

```
src/core/*.c ──┐
               ├─→ build/*.o ──→ bin/exe ──→ (exécution)
src/programs/*.c┘

bin/graphiques ──→ data/*.dat ──→ gnuplot ──→ data/*.png
```

## 🔧 Processus de Compilation

```
makefile
   │
   ├─→ compile src/core/*.c     → build/*.o
   ├─→ compile src/programs/*.c → build/*.o
   ├─→ compile src/external/*.c → build/*.o
   │
   └─→ link build/*.o → bin/{exe,fibo,experiments,graphiques}
```

## 📈 Flux d'Utilisation Typique

```
1. make                    # Compiler tout
2. make run-exe            # Test rapide
3. make run-graphiques     # Générer les graphiques
4. firefox data/*.png      # Visualiser les résultats
5. make doc               # Générer la documentation
```

## 🗂️ Organisation par Type

### Code Source C
- **10 fichiers** dans `src/core/` (5 modules × 2 fichiers .c/.h)
- **4 fichiers** dans `src/programs/` (4 programmes)
- **2 fichiers** dans `src/external/mt19937ar-cok/`

### Documentation
- **4 fichiers Markdown** dans `docs/guide/`
- **1 fichier HTML** principal dans `docs/html/` (+ nombreux fichiers générés)
- **2 fichiers Markdown** à la racine (README, RESUME)

### Configuration
- **1 makefile** principal
- **1 Doxyfile** pour la documentation
- **1 .gitignore**
- **1 .editorconfig**

## 📏 Statistiques du Projet

- **Lignes de code C** : ~2500 lignes (core + programs)
- **Modules principaux** : 5 (simulation, config, population, aging, reproduction)
- **Programmes** : 4 (exe, fibo, experiments, graphiques)
- **Graphiques générés** : 3 PNG
- **Fichiers de données** : 3 .dat + 3 .gp

## 🎯 Avantages de cette Structure

✅ **Séparation claire** : src/, bin/, build/, data/, docs/
✅ **Modularité** : core/programs/external bien séparés
✅ **Pas de pollution** : tous les .o dans build/
✅ **Lisibilité** : structure intuitive et standard
✅ **Maintenabilité** : facile d'ajouter de nouveaux modules
✅ **Professionnalisme** : suit les conventions de projets C
