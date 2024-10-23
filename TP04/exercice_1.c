#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define size 100000000

int main() {
    
    // Initialisation du tableau d'entiers
    // --------------------------------------------
    int *table = (int *) malloc(size * sizeof(int));
    srand(time(NULL));
    if (table == NULL) {
        printf("Erreur lors de la location de la memoire!\n");
        return 1;
    }
    for (int i = 0; i < size ; i++){
        table[i] = i + 1;
    }

    // Implémentation de la boucle séquentielle pour calculer la somme
    // --------------------------------------------
    // int sum_sequential = 0;
    // for (int i = 0; i < size; i++) {
    //     sum_sequential += table[i];
    // }
    // printf("La somme avec une boucle séquentialle est %d\n", sum_sequential);

    // Implémentation de la boucle parallèle avec OpenMP
    // --------------------------------------------
    // int sum_parallel = 0;
    // #pragma omp parallel for
    // for (int i = 0; i < size; i++) {
    //     sum_parallel += table[i];
    // }
    // printf("La somme avec une boucle parallèle est %d\n", sum_parallel);

    // Utilisation de la clause reduction(+: sum) pour la gestion de la somme
    // // --------------------------------------------
    // int sum_parallel = 0;
    // #pragma omp parallel for reduction(+:sum_parallel)
    // for (int i = 0; i < size; i++) {
    //     sum_parallel += table[i];
    // }
    // printf("La somme avec une boucle parallèle est %d\n", sum_parallel);



    // Mesure du temps d'exécution de la version séquentielle avec omp_get_wtime()
    // --------------------------------------------
    int sum_sequential = 0;
    double start_sequentialt, end_sequential;
    start_sequentialt = omp_get_wtime();
    for (int i = 0; i < size; i++) {
        sum_sequential += table[i];
    }
    end_sequential = omp_get_wtime();
    printf("La somme avec une boucle séquentialle est %d\n", sum_sequential);
    double execution_time_sequential = end_sequential - start_sequentialt;
    printf("Le Temps d'Exécution Séquentialle: %f seconds\n", execution_time_sequential);

    // Mesure du temps d'exécution de la version parallèle avec OpenMP et omp_get_wtime()
    // --------------------------------------------
    int sum_parallel = 0;
    double start_parallel, end_parallel;
    start_parallel = omp_get_wtime();
    int num_threads = 0;

    #pragma omp parallel 
    {
        num_threads = omp_get_num_threads();
        #pragma omp for reduction(+:sum_parallel)
        for (int i = 0; i < size; i++) {
            sum_parallel += table[i];
        }
    }
    end_parallel = omp_get_wtime();
    printf("La somme avec une boucle parallele est %d\n", sum_parallel);
    double execution_time_parallel = end_parallel - start_parallel;
    printf("Le Temps d'Exécution parallele (%d threads): %f seconds\n", num_threads, execution_time_parallel);

    // Comparaison des temps d'exécution
    //  -------------------------------------------
    double speed_up = execution_time_sequential / execution_time_parallel;
    printf("L'acceleration avec %d threads est: %f\n", num_threads, speed_up);
    printf("L'efficacite avec %d threads est: %f\n\n", num_threads, speed_up / num_threads);

    // Libération de la mémoire
    free(table);
    return 0;
}