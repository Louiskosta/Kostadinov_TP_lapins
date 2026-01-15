# Simulation de Population de Lapins 🐰

Projet de simulation stochastique de croissance de population avec paramètres biologiques réalistes.

## 🚀 Démarrage Rapide

```bash
# Compiler tous les programmes
make

# Voir toutes les commandes disponibles
make help

# Exécuter les programmes
make run-fibo          # Modèle de Fibonacci
make run-exe           # Simulation réaliste
make run-experiments   # Expériences multiples
make run-graphiques    # Générer les graphiques
```

## 📁 Structure du Projet

```
TP_lapins/
├── src/                  # Code source
│   ├── core/             # Modules de simulation
│   ├── programs/         # Programmes exécutables
│   └── external/         # Bibliothèques externes (MT19937)
├── bin/                  # Exécutables compilés
├── build/                # Fichiers objets
├── data/                 # Graphiques et données générés
├── docs/                 # Documentation
│   ├── html/             # Documentation Doxygen
│   └── rapport.tex       # Rapport LaTeX du projet
└── rapport.pdf           # Rapport compilé
```

## 📊 Programmes Disponibles

| Programme | Description | Commande |
|-----------|-------------|----------|
| **exe** | Simulation réaliste (100+100 lapins, 100 ans) | `bin/exe` ou `make run-exe` |
| **fibo** | Modèle de Fibonacci simple | `bin/fibo 20` ou `make run-fibo` |
| **experiments** | Expériences multiples avec statistiques | `make run-experiments` |
| **graphiques** | Génération automatique de graphiques | `make run-graphiques` |

## 🔧 Compilation

### Prérequis
- GCC (compilateur C)
- Bibliothèques : GMP, MPFR
- Gnuplot (pour les graphiques)

```bash
# Installation des dépendances (Ubuntu/Debian)
sudo apt-get install gcc libgmp-dev libmpfr-dev gnuplot
```

### Commandes Make

```bash
make              # Compile tous les programmes
make clean        # Supprime les fichiers compilés
make clean-all    # Supprime aussi les données générées
make help         # Affiche l'aide complète
```

## 📚 Documentation

- **[rapport.pdf](rapport.pdf)** - Rapport complet du projet
- **[docs/rapport.tex](docs/rapport.tex)** - Source LaTeX du rapport
- **[docs/html/index.html](docs/html/index.html)** - Documentation Doxygen du code

### Générer la documentation

```bash
make doc
firefox docs/html/index.html
```

## 🎯 Exemples d'Utilisation

### 1. Simulation Simple

```bash
# Compiler et exécuter
make run-exe

# Ou directement
bin/exe
```

### 2. Modèle de Fibonacci

```bash
# 15 mois (défaut)
make run-fibo

# Durée personnalisée
bin/fibo 30
```

### 3. Générer des Graphiques

```bash
make run-graphiques

# Les graphiques PNG sont dans data/
ls -lh data/*.png
```

Graphiques générés :
- `data/comparaison_populations.png` - Comparaison de 3 conditions initiales
- `data/variabilite_populations.png` - Variabilité stochastique
- `data/boxplot_populations.png` - Distribution des populations finales

## 📈 Paramètres du Modèle

- **Survie** : Taux de survie annuel décroissant avec l'âge (79% à 0-1 an → 72% à 2-3 ans, etc.)
- **Portées** : 0 à 9 portées par an selon une distribution de probabilité
- **Taille de portée** : 3 à 6 bébés uniformément
- **Maturation** : 12 mois pour atteindre l'âge adulte
- **Sexe ratio** : 50% mâles / 50% femelles

## 🔬 Analyses Possibles

Le projet permet d'analyser :
- La croissance exponentielle de la population
- La variabilité stochastique entre réplications
- L'impact des conditions initiales
- La prédictibilité à long terme
- Les distributions de populations finales

## 🐛 Résolution de Problèmes

### Erreur de compilation
```bash
# Vérifier les dépendances
sudo apt-get install gcc libgmp-dev libmpfr-dev

# Nettoyer et recompiler
make clean && make
```

### Gnuplot introuvable
```bash
sudo apt-get install gnuplot
```

### Documentation Doxygen
```bash
sudo apt-get install doxygen
make doc
```

## 📄 Licence

Projet académique - TP Simulation Stochastique

## ✍️ Auteur

Projet de TP - 2025

---

Pour plus de détails, consultez le [rapport.pdf](rapport.pdf) et la documentation Doxygen dans `docs/html/`.
