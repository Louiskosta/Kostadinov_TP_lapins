# Guide des Graphiques

Ce document explique les différents graphiques générés par le programme `graphiques`.

## 1. Comparaison des Conditions Initiales

**Fichier** : `comparaison_populations.png`

Ce graphique montre l'évolution de la population totale au fil du temps pour trois conditions initiales différentes :
- 10×10 lapins (10 mâles + 10 femelles)
- 50×50 lapins
- 100×100 lapins

### Interprétation
- On observe une **croissance exponentielle** pour toutes les conditions
- Les trois courbes ont une forme similaire (parallèles en échelle log)
- La condition initiale détermine simplement le "décalage" vertical de la courbe
- Plus on part avec de lapins, plus la croissance absolue est importante

### Questions d'analyse
1. Le taux de croissance dépend-il de la condition initiale ?
2. Combien de temps faut-il pour atteindre 1 million de lapins dans chaque cas ?
3. Quelle est la différence relative entre les trois courbes à t=15 ans ?

## 2. Variabilité Stochastique

**Fichier** : `variabilite_populations.png`

Ce graphique montre 8 réplications indépendantes de la simulation avec les mêmes conditions initiales (100×100 lapins).

### Interprétation
- Chaque courbe représente une simulation avec une graine aléatoire différente
- On observe une **dispersion** croissante avec le temps
- Les trajectoires divergent progressivement malgré le même point de départ
- La variabilité est due aux processus stochastiques :
  - Nombre de portées par femelle (tiré au hasard)
  - Taille de chaque portée (3-6 bébés)
  - Survie individuelle
  - Sexe des nouveaux-nés

### Questions d'analyse
1. La variabilité relative augmente-t-elle ou diminue-t-elle avec le temps ?
2. Peut-on prédire précisément la population à t=12 ans ?
3. Quelle est l'étendue (max - min) à t=12 ans ?
4. Les trajectoires se croisent-elles ? Pourquoi ?

### Calculs utiles
```
Coefficient de variation (CV) = écart-type / moyenne
```
Un CV élevé indique une forte variabilité relative.

## 3. Distribution des Populations Finales

**Fichier** : `boxplot_populations.png`

Ce graphique montre la distribution des populations finales après 12 ans pour les trois conditions initiales, basée sur 15 réplications chacune.

### Éléments du boxplot
- **Médiane** (ligne centrale) : valeur centrale
- **Quartiles** (boîte) : 50% des valeurs sont dans la boîte
  - Q1 (25e percentile) : bord inférieur de la boîte
  - Q3 (75e percentile) : bord supérieur de la boîte
- **Moustaches** : minimum et maximum (hors outliers)
- **Outliers** : points exceptionnels

### Interprétation
1. **Forme de la distribution** : la boîte est-elle symétrique ou asymétrique ?
2. **Dispersion** : quelle condition a la plus grande variabilité absolue ?
3. **Comparaison** : les distributions se chevauchent-elles ?

### Questions d'analyse
1. La médiane est-elle proche de la moyenne attendue ?
2. Y a-t-il des valeurs aberrantes (outliers) ?
3. L'étendue interquartile (IQR = Q3 - Q1) est-elle proportionnelle à la médiane ?
4. Peut-on considérer que la distribution est approximativement normale ?

## Données Brutes

Les fichiers `.dat` contiennent les données numériques utilisées pour les graphiques :

- `comparaison_data.dat` : 
  ```
  # Annees Pop_10x10 Pop_50x50 Pop_100x100
  0 21 118 225
  1 231 1083 1862
  ...
  ```

- `variabilite_data.dat` :
  ```
  # Annees Rep1 Rep2 Rep3 Rep4 Rep5 Rep6 Rep7 Rep8
  0 225 225 225 225 225 225 225 225
  1 1893 1740 1878 1937 1900 1802 1916 1943
  ...
  ```

- `boxplot_data.dat` :
  ```
  # Condition PopulationFinale
  1 21110843
  1 20887456
  ...
  ```

## Scripts Gnuplot

Les fichiers `.gp` sont les scripts gnuplot utilisés pour générer les PNG.
Vous pouvez les modifier pour personnaliser :
- Taille de l'image : `set terminal png size 1200,800`
- Titre : `set title 'Mon titre'`
- Couleurs : `linecolor rgb 'red'`
- Type de courbe : `with lines`, `with linespoints`, `with points`

Pour régénérer un graphique après modification :
```bash
gnuplot plot_comparaison.gp
```

## Analyses Statistiques Recommandées

Pour chaque graphique, calculez :

1. **Taux de croissance moyen**
   - Ajustement exponentiel : N(t) = N₀ × e^(rt)
   - Calcul de r (taux intrinsèque de croissance)

2. **Coefficient de variation**
   - CV(t) = σ(t) / μ(t)
   - Évolution du CV avec le temps

3. **Intervalle de confiance**
   - IC à 95% pour la population finale
   - Basé sur les réplications

4. **Test d'hypothèse**
   - Les trois conditions donnent-elles des taux de croissance statistiquement différents ?
   - Test ANOVA ou test non-paramétrique (Kruskal-Wallis)

## Rapport

Dans votre rapport, incluez :

1. **Figures** : les trois graphiques PNG
2. **Légendes** : description détaillée de chaque figure
3. **Analyse** : réponses aux questions ci-dessus
4. **Discussion** : 
   - Importance de la variabilité stochastique
   - Limites du modèle
   - Prédictibilité à long terme
   - Impact des paramètres biologiques

## Commandes Utiles

```bash
# Générer tous les graphiques
./graphiques

# Nettoyer les fichiers générés
make clean  # ou rm *.png *.dat *.gp

# Regénérer un graphique spécifique
gnuplot plot_comparaison.gp
gnuplot plot_variabilite.gp
gnuplot plot_boxplot.gp

# Convertir PNG en PDF (pour le rapport)
convert comparaison_populations.png comparaison_populations.pdf
```
