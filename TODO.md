# TODO - Ce qu'il reste à faire pour le TP

## ✅ Code Complété

Tout le code de simulation est fonctionnel :
- ✅ Simulation Fibonacci simple (`fibo.c`)
- ✅ Simulation réaliste avec tous les paramètres biologiques (`exe`)
- ✅ Programme d'expérimentations multiples (`experiments`)
- ✅ Documentation du code (commentaires Doxygen)
- ✅ Makefile pour compilation
- ✅ README avec instructions

## 📊 Expérimentations à Réaliser

### 1. Lancer les expérimentations
```bash
make
./experiments > resultats.txt
```

Cela va lancer automatiquement :
- Expérience 1 : Conditions faibles (10+10 lapins, 10 ans, 5 runs)
- Expérience 2 : Conditions moyennes (50+50 lapins, 10 ans, 5 runs)
- Expérience 3 : Conditions fortes (100+100 lapins, 10 ans, 5 runs)
- Expérience 4 : Longue durée (100+100 lapins, 20 ans, 3 runs)

**ATTENTION:** Cela peut prendre du temps (15-30 minutes selon votre PC)

### 2. Variantes à tester manuellement

#### Test d'extinction (conditions très faibles)
```bash
# Modifier experiments.c ligne ~120 pour ajouter:
run_experiment_series(5, 5, 10, 10);  // 5+5 lapins, voir si extinction
```

#### Test longue durée extrême
```bash
# Modifier experiments.c pour tester 25 ans
run_experiment_series(100, 100, 25, 2);
```

## 📝 Rapport à Rédiger

Le template est dans `RAPPORT.md`. Il faut compléter :

### Sections à remplir :

1. **Introduction (§1)** : Contexte et objectifs
   - ✅ Déjà écrite en partie

2. **Modèle (§2)** : Justifier vos choix
   - ✅ Paramètres biologiques décrits
   - ⚠️ Ajouter : Pourquoi simulation mensuelle et pas annuelle ?
   - ⚠️ Ajouter : Justification des seuils choisis

3. **Résultats (§3)** : ⚠️ **À COMPLÉTER**
   - Copier les résultats de `./experiments`
   - Remplir les tableaux
   - Créer des graphiques (optionnel mais recommandé)

4. **Analyse Variabilité (§4)** : ⚠️ **À COMPLÉTER**
   - Calculer les CV (coefficient de variation)
   - Analyser le risque d'extinction
   - Discuter l'importance de faire plusieurs runs

5. **Performances (§5)** : ⚠️ **À COMPLÉTER**
   - Mesurer le temps avec `time ./exe`
   - Mesurer avec `time ./experiments`
   - Discuter les limites (mémoire, temps)

6. **Conclusion (§7)** : ⚠️ **À COMPLÉTER**
   - Synthèse des résultats
   - Comparaison avec modèle de Fibonacci
   - Apprentissages

### Graphiques Recommandés

Si vous avez le temps, créer avec Excel/Python/R :

1. **Courbe d'évolution** : Population en fonction du temps
2. **Boxplot** : Distribution des populations finales
3. **Histogramme** : Répartition des résultats

## 🎯 Checklist Finale

Avant de rendre :

### Code
- [ ] `make clean && make` compile sans erreur ni warning
- [ ] `./fibo` fonctionne
- [ ] `./exe` fonctionne et affiche des résultats
- [ ] `./experiments` fonctionne (même si long)
- [ ] Code commenté et lisible
- [ ] Documentation Doxygen générée (`doxygen Doxyfile`)

### Expérimentations
- [ ] Expérimentations lancées et résultats sauvegardés
- [ ] Au moins 3 configurations testées
- [ ] Variabilité stochastique analysée

### Rapport
- [ ] RAPPORT.md complété avec vos résultats
- [ ] Tableaux remplis
- [ ] Analyses et conclusions rédigées
- [ ] Références bibliographiques
- [ ] Graphiques (optionnel)

### Livraison
- [ ] Code source (tous les .c et .h)
- [ ] Makefile
- [ ] README.md
- [ ] RAPPORT.md (ou RAPPORT.pdf)
- [ ] Résultats des expérimentations (resultats.txt)
- [ ] Documentation HTML (optionnel)

## ⏱️ Estimation du Temps Restant

- Lancer expérimentations : **30 min - 1h** (temps machine)
- Analyser résultats : **30 min**
- Rédiger rapport : **2-3 heures**
- Relecture et finalisation : **30 min**

**Total : 4-5 heures**

## 💡 Conseils

1. **Lancez les expérimentations en premier** pendant que vous rédigez autre chose
2. **Utilisez `time`** pour mesurer les performances
3. **Faites des captures d'écran** des résultats intéressants
4. **Sauvegardez régulièrement** votre travail
5. **Testez la compilation** sur une machine propre si possible

## 🆘 En cas de problème

### Programme trop lent
- Réduire le nombre d'années (10 au lieu de 20)
- Réduire le nombre de runs (3 au lieu de 5)
- Utiliser moins de lapins initiaux

### Segmentation fault
- Vérifier les limites de mémoire
- Réduire la durée de simulation
- Vérifier les allocations/désallocations

### Résultats incohérents
- Vérifier l'initialisation du générateur aléatoire
- S'assurer que les paramètres sont corrects
- Faire plus de runs pour moyenner

---

**Bon courage ! La partie difficile (le code) est faite, il reste "juste" à faire tourner et analyser. 🚀**
