# Guide d'Utilisation de la Documentation Doxygen

## 📖 Accès à la Documentation

### Ouvrir la documentation

```bash
# Option 1 : Avec xdg-open (Linux)
xdg-open docs/html/index.html

# Option 2 : Avec un navigateur spécifique
google-chrome docs/html/index.html
firefox docs/html/index.html

# Option 3 : Ouvrir manuellement
# Naviguer vers : TP_lapins/docs/html/index.html dans votre explorateur de fichiers
```

## 🗂️ Navigation dans la Documentation

### Page d'accueil (index.html)

La page d'accueil contient :
- Description du projet
- Liens vers les différentes sections

### Menu de navigation principal

1. **📁 Fichiers** (Files)
   - Liste tous les fichiers `.c` et `.h`
   - Cliquez sur un fichier pour voir ses fonctions
   - Exemple : `simulation.c` → voir toutes les fonctions de simulation

2. **🏗️ Structures de données** (Data Structures / Classes)
   - `mois_lapin` - Structure représentant la population d'un mois
   - `population` - Structure globale de la population
   - Voir les membres de chaque structure

3. **📋 Index des fichiers** (File List)
   - Accès rapide à tous les modules
   - Modules core : aging, config, population, reproduction, simulation
   - Programmes : experiments, fibo, graphiques, main

4. **🔍 Index des fonctions** (File Members / Globals)
   - Liste alphabétique de **toutes les fonctions**
   - Cliquez sur "All" pour voir la liste complète
   - Exemple : `simulate_population()`, `aging()`, `reproduction()`

## 📚 Modules Documentés

### Modules Core (src/core/)

| Module | Fichier | Description |
|--------|---------|-------------|
| **Simulation** | `simulation.c/h` | Moteur principal de simulation |
| **Config** | `config.c/h` | Paramètres biologiques |
| **Population** | `population.c/h` | Gestion de la population |
| **Aging** | `aging.c/h` | Vieillissement et mortalité |
| **Reproduction** | `reproduction.c/h` | Reproduction et naissances |

### Programmes (src/programs/)

| Programme | Fichier | Description |
|-----------|---------|-------------|
| **Main** | `main.c` | Simulation simple |
| **Fibo** | `fibo.c` | Modèle de Fibonacci |
| **Experiments** | `experiments.c` | Expériences multiples |
| **Graphiques** | `graphiques.c` | Génération de graphiques |

## 🔎 Comment Trouver une Fonction

### Méthode 1 : Par le menu "Files"

1. Cliquez sur **Files** dans le menu
2. Cliquez sur le fichier (ex: `simulation.c`)
3. Descendez jusqu'à "Functions"
4. Toutes les fonctions du fichier sont listées

### Méthode 2 : Par l'index des fonctions

1. Cliquez sur **Files** → **File Members**
2. Sélectionnez **All** pour voir toutes les fonctions
3. Ou choisissez une lettre (a, b, c...) pour filtrer
4. Cliquez sur le nom de la fonction pour voir sa documentation

### Méthode 3 : Recherche

1. Utilisez la barre de recherche en haut à droite
2. Tapez le nom de la fonction (ex: "simulate")
3. Sélectionnez dans les résultats

## 📖 Exemple de Navigation

Pour trouver la fonction `simulate_population()` :

**Chemin 1** :
```
Files → simulation.c → Functions → simulate_population()
```

**Chemin 2** :
```
Files → File Members → All → s → simulate_population()
```

**Chemin 3** :
```
Barre de recherche → "simulate_population"
```

## 💡 Informations Disponibles pour Chaque Fonction

Quand vous cliquez sur une fonction, vous voyez :

- **Signature complète** : type de retour, nom, paramètres
- **Description** : à quoi sert la fonction
- **Paramètres** : description de chaque paramètre
- **Valeur de retour** : ce que retourne la fonction
- **Détails** : explications supplémentaires
- **Code source** : lien vers le code

## 🔄 Régénérer la Documentation

Si vous modifiez le code et voulez mettre à jour la documentation :

```bash
# Méthode 1 : Via make
make doc

# Méthode 2 : Directement avec doxygen
doxygen Doxyfile
```

La documentation sera régénérée dans `docs/html/`

## 🎯 Exemples Pratiques

### Voir toutes les fonctions de simulation

1. Files → `simulation.c` → Scroll vers "Functions"
2. Vous verrez :
   - `simulate_month()`
   - `simulate_year()`
   - `simulate_population()`

### Comprendre la structure population

1. Data Structures → `population`
2. Vous verrez le membre : `lapins_par_age[17][12]`

### Chercher les fonctions de configuration

1. Files → `config.c`
2. Fonctions disponibles :
   - `init_prob_litter()`
   - `init_survival_rate()`
   - `survival_rate_adult()`

## 🐛 Problèmes Courants

### "Aucune fonction visible"

**Solution** : Régénérez la documentation
```bash
make doc
```

### "Documentation vide"

**Vérification** :
```bash
# Vérifier que les fichiers existent
ls src/core/*.c src/programs/*.c

# Régénérer
doxygen Doxyfile
```

### "Certaines fonctions manquent"

Les fonctions `static` peuvent ne pas apparaître. Dans le Doxyfile :
```
EXTRACT_STATIC = YES
```

## 📊 Structure de la Documentation

```
docs/html/
├── index.html              # Page d'accueil
├── files.html              # Liste des fichiers
├── globals.html            # Index des fonctions
├── annotated.html          # Structures
├── simulation_8c.html      # Doc de simulation.c
├── population_8c.html      # Doc de population.c
└── ...                     # Autres modules
```

## ✅ Checklist de Vérification

- [ ] `docs/html/index.html` existe
- [ ] Tous les modules apparaissent dans Files
- [ ] Les fonctions sont visibles dans File Members
- [ ] Les structures sont dans Data Structures
- [ ] La recherche fonctionne

---

**Note** : La documentation est générée en français grâce à `OUTPUT_LANGUAGE = French` dans le Doxyfile.
