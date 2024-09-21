# OpenMP Projects - TP02 & TP03

## Description
Ce dépôt contient les fichiers relatifs aux travaux pratiques (TP) sur l'optimisation avec OpenMP. Vous trouverez des codes sources pour les TP02 et TP03, ainsi que des scripts pour compiler et exécuter les programmes. De plus, des résultats d'exécution et des documents PDF expliquant les optimisations sont inclus.

## Structure du Répertoire

### TP02 - Parallélisation de Boucles en OpenMP
- **OpenMP_TP02.pdf** : Rapport du TP02.
- **OpenMP_TP02.zip** : Archive contenant tous les fichiers du TP02.
- **TP02/compile_and_run.sh** : Script shell pour compiler et exécuter les programmes.
- **TP02/sequential_program.c** : Programme séquentiel sans parallélisation.
- **TP02/parallel_program.c** : Programme parallèle basique.
- **TP02/parallel_program_num_threads.c** : Programme avec gestion du nombre de threads.
- **TP02/parallel_program_loop_order.c** : Optimisation de l'ordre des boucles.
- **TP02/parallel_program_loop_interne.c** : Parallélisation de la boucle interne.
- **TP02/parallel_program_demission_M_N.c** : Gestion de la distribution M*N pour la parallélisation.
- **TP02/results/** : Résultats des exécutions des différents programmes parallèles et séquentiels.

### TP03 - Optimisation du Mandelbrot avec OpenMP
- **OpenMP_TP03.pdf** : Rapport du TP03.
- **OpenMP_TP03.zip** : Archive contenant tous les fichiers du TP03.
- **TP03/compile_and_run.sh** : Script shell pour compiler et exécuter les programmes.
- **TP03/mandelbrot_sequential.c** : Programme séquentiel pour générer le fractal de Mandelbrot.
- **TP03/mandelbrot_parallel.c** : Programme parallèle pour Mandelbrot avec OpenMP.
- **TP03/mandelbrot_parallel_number_threads.c** : Mandelbrot avec gestion du nombre de threads.
- **TP03/mandelbrot_parallel_task_loop.c** : Mandelbrot utilisant `taskloop` pour la parallélisation.
- **TP03/results/** : Résultats des différentes versions des programmes Mandelbrot.

### Projet d'Optimisation de Boucles avec OpenMP
- **project_openMP_loop_optimization.zip** : Archive contenant tous les fichiers du projet.
- **project_openMP_loop_optimization/compile_and_run.sh** : Script pour compiler et exécuter les programmes.
- **project_openMP_loop_optimization/simple_loop_no_openmp_no_optimization.c** : Boucle simple sans optimisation ni OpenMP.
- **project_openMP_loop_optimization/simple_loop_no_optimization.c** : Boucle simple avec OpenMP mais sans optimisation.
- **project_openMP_loop_optimization/loop_unrolling_openmp.c** : Boucle avec unrolling et OpenMP.
- **project_openMP_loop_optimization/loop_fusion_openmp.c** : Boucle avec fusion de boucles et OpenMP.
- **project_openMP_loop_optimization/combined_optimizations_openmp.c** : Optimisations combinées avec OpenMP.

## Instructions

1. **Compilation et exécution** :
   - Chaque répertoire (TP02, TP03, project_openMP_loop_optimization) contient un script `compile_and_run.sh` pour compiler et exécuter les programmes.
   - Exécutez les scripts avec la commande suivante :
     ```bash
     ./compile_and_run.sh
     ```
   
2. **Résultats** :
   - Les résultats des différentes exécutions sont disponibles dans les dossiers `results` respectifs pour TP02 et TP03.

## Exécution des Programmes
- Les programmes peuvent être exécutés sur une machine avec OpenMP installé. Les résultats varient en fonction du nombre de cœurs de votre machine.

