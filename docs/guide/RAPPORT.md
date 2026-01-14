# Rapport de Simulation - Population de Lapins
## Modélisation et Expérimentations

**Auteur:** [Votre Nom]  
**Date:** [Date]

---

## 1. Introduction

Ce rapport présente une simulation stochastique de croissance d'une population de lapins, en utilisant une approche "individual-based modeling". Contrairement au modèle simpliste de Fibonacci, cette simulation intègre des paramètres biologiques réalistes : mortalité selon l'âge, reproduction variable, et maturation progressive.

---

## 2. Modèle Mathématique et Choix de Modélisation

### 2.1 Paramètres Biologiques

#### Reproduction
- **Nombre de portées par an:** 3 à 9 portées
  - Distribution pondérée : plus de chances d'avoir 5, 6 ou 7 portées
  - Implémentation : tableau de poids `[0,0,0,1,1,2,2,2,1,1]` converti en probabilités cumulatives
  
- **Taille des portées:** 3 à 6 bébés par portée
  - Distribution uniforme
  
- **Sexe des nouveaux-nés:** 50% mâles, 50% femelles

#### Maturation
- **Maturité sexuelle:** Entre 5 et 8 mois
  - Probabilités progressives par mois d'âge
  - À 10 mois, tous les lapins sont matures

#### Mortalité
- **Bébés (0-8 mois):** Taux de survie global de 35% sur 8 mois
  - Taux mensuel : (0.35)^(1/8) ≈ 0.885
  
- **Adultes jeunes (<10 ans):** Taux de survie annuel de 60%
  - Taux mensuel : (0.60)^(1/12) ≈ 0.957
  
- **Adultes âgés (≥10 ans):** Déclin progressif
  - -10% par an jusqu'à 0% à 15 ans
  - Exemple : 11 ans → 50%, 12 ans → 40%, ..., 15 ans → 0%

### 2.2 Choix d'Implémentation

#### Pas de temps
**Choix:** Simulation mensuelle (pas annuelle)  
**Justification:** Plus de précision pour la reproduction et la maturation

#### Gestion des grandes populations
**Problème:** Avec une croissance exponentielle, on peut atteindre des milliards de lapins  
**Solution adoptée:**
- Utilisation de la bibliothèque GMP (GNU Multiple Precision) pour gérer les très grands nombres
- Pour les populations > 10000, utilisation d'approximations gaussiennes au lieu de simulations individuelles
- Compromis entre précision et performance

#### Structure de données
Organisation par âge et mois : `population[age][month]`
- Facilite le vieillissement (décalage d'indices)
- Permet un calcul efficace des statistiques

---

## 3. Résultats des Expérimentations

### 3.1 Comparaison Fibonacci vs Modèle Réaliste

#### Programme Fibonacci (10 mois)
```
Mois 0:  1 couple
Mois 5:  8 couples
Mois 10: 89 couples
```

#### Simulation Réaliste (10 ans, 100+100 lapins initiaux)

**Résultats** (à compléter avec vos données) :
```
[Insérer ici les résultats de ./experiments]
```

**Observations:**
- [ ] La croissance est-elle plus lente que Fibonacci ? Pourquoi ?
- [ ] Quelle est la variabilité entre les runs ?
- [ ] Y a-t-il des risques d'extinction avec peu de lapins initiaux ?

### 3.2 Impact des Conditions Initiales

#### Expérience A : 10 femelles + 10 mâles

| Run | Population finale | Observations |
|-----|------------------|--------------|
| 1   |                  |              |
| 2   |                  |              |
| 3   |                  |              |
| 4   |                  |              |
| 5   |                  |              |

**Statistiques:**
- Moyenne : 
- Écart-type : 
- Min : 
- Max : 

#### Expérience B : 100 femelles + 100 mâles

| Run | Population finale | Observations |
|-----|------------------|--------------|
| 1   |                  |              |
| 2   |                  |              |
| 3   |                  |              |
| 4   |                  |              |
| 5   |                  |              |

**Statistiques:**
- Moyenne : 
- Écart-type : 
- Min : 
- Max : 

### 3.3 Simulation Longue Durée (20 ans)

**Conditions:** 100 femelles + 100 mâles initiaux

| Année | Population moyenne | Écart-type |
|-------|-------------------|------------|
| 5     |                   |            |
| 10    |                   |            |
| 15    |                   |            |
| 20    |                   |            |

**Graphique** (si possible, créer un graphique avec les données)

---

## 4. Analyse de la Variabilité Stochastique

### 4.1 Coefficient de Variation

Le coefficient de variation (CV = écart-type / moyenne) mesure la variabilité relative :

- **Faible population initiale:** CV = ____%
- **Moyenne population initiale:** CV = ____%
- **Forte population initiale:** CV = ____%

**Conclusion:** [À compléter]

### 4.2 Risque d'Extinction

Avec peu de lapins initiaux, il existe un risque d'extinction dû à :
1. Forte mortalité des bébés (65% de mortalité)
2. Variabilité stochastique élevée
3. Déséquilibre possible mâles/femelles par chance

**Observations:** [À compléter]

---

## 5. Performances et Optimisations

### 5.1 Temps d'Exécution

| Configuration | Temps CPU | Mémoire |
|--------------|-----------|---------|
| 10 ans, 100 lapins | | |
| 20 ans, 100 lapins | | |
| 10 ans, 1000 lapins | | |

### 5.2 Optimisations Implémentées

1. **GMP pour grands nombres:** Évite les overflows
2. **Approximation gaussienne:** Pour populations > 10000
3. **Structure de données efficace:** Tableau indexé par âge/mois

### 5.3 Limites

- Au-delà de 25-30 ans, le temps de calcul devient prohibitif
- La mémoire peut être limitante pour des populations énormes
- [Autres limites observées]

---

## 6. Extensions Possibles (hors scope du TP)

1. **Ressources limitées:** Introduire une capacité de charge maximale
2. **Prédateurs:** Mortalité supplémentaire proportionnelle à la population
3. **Pandémies:** Événements stochastiques de mortalité massive
4. **Parallélisation:** Exécuter plusieurs runs en parallèle
5. **Visualisation:** Graphiques temps réel de l'évolution

---

## 7. Conclusion

### 7.1 Résumé des Résultats

[À compléter avec vos observations principales]

### 7.2 Comparaison avec la Littérature

[Comparer vos résultats avec des données réelles sur les lapins]

### 7.3 Apprentissages

1. Importance de la modélisation stochastique
2. Nécessité de multiples exécutions pour des résultats fiables
3. Compromis entre réalisme et performance
4. [Autres apprentissages]

---

## Annexes

### A. Code Source

Structure du projet :
```
├── fibo.c              # Simulation simple Fibonacci
├── main.c              # Simulation réaliste simple run
├── experiments.c       # Expérimentations multiples
├── simulation.c/h      # Moteur de simulation
├── config.c/h          # Paramètres biologiques
├── population.c/h      # Gestion population
├── aging.c/h           # Vieillissement
├── reproduction.c/h    # Reproduction
└── makefile
```

### B. Instructions d'Utilisation

```bash
# Compilation
make

# Fibonacci simple
./fibo 12

# Une simulation réaliste
./exe

# Expérimentations multiples
./experiments

# Documentation
doxygen Doxyfile
firefox docs/html/index.html
```

### C. Références

1. https://r-knott.surrey.ac.uk/Fibonacci/fibnat.html
2. [Autres références sur la biologie des lapins]
3. Documentation GMP : https://gmplib.org/

---

**Note:** Ce template doit être complété avec vos résultats expérimentaux réels.
