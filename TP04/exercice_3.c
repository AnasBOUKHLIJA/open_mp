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

    // Calcul le maximum des éléments
    // --------------------------------------------
    int max_sequential = table[0];
    double max_start_sequentialt, max_end_sequential;
    max_start_sequentialt = omp_get_wtime();
    for (int i = 0; i < size; i++) {
        if (table[i] > max_sequential) {
            max_sequential = table[i];
        }
    }
    max_end_sequential = omp_get_wtime();
    printf("Le Max avec une boucle séquentialle est %d\n", max_sequential);
    double max_execution_time_sequential = max_end_sequential - max_start_sequentialt;
    printf("Le Temps d'Exécution Séquentialle: %f seconds\n", max_execution_time_sequential);


    // Calcul le minimum des éléments
    // --------------------------------------------
    int min_sequential = table[0];
    double min_start_sequentialt, min_end_sequential;
    min_start_sequentialt = omp_get_wtime();
    for (int i = 0; i < size; i++) {
        if (table[i] < min_sequential) {
            min_sequential = table[i];
        }
    }
    min_end_sequential = omp_get_wtime();
    printf("Le Min avec une boucle séquentialle est %d\n", min_sequential);
    double min_execution_time_sequential = min_end_sequential - min_start_sequentialt;
    printf("Le Temps d'Exécution Séquentialle: %f seconds\n", min_execution_time_sequential);


    // Version parallele de calcul le maximum des éléments
    // --------------------------------------------
    int max_parallel = table[0];
    double max_start_parallel, max_end_parallel;
    max_start_parallel = omp_get_wtime();
    int max_num_threads = 0;

    #pragma omp parallel
    {
        max_num_threads = omp_get_num_threads();
        #pragma omp for reduction(max: max_parallel)
        for (int i = 0; i < size; i++) {
            if (table[i] > max_parallel) {
                max_parallel = table[i];
            }
        }
    } 

    max_end_parallel = omp_get_wtime();
    printf("Le Max avec une boucle Parallele est %d\n", max_parallel);
    double max_execution_time_parallel = max_end_parallel - max_start_parallel;
    printf("Le Temps d'Exécution Parallele: %f seconds\n", max_execution_time_parallel);

    // Version parallele de calcul le minimum des éléments
    // --------------------------------------------
    int min_parallel = table[0];
    double min_start_parallel, min_end_parallel;
    min_start_parallel = omp_get_wtime();
    int min_num_threads = 0;

    #pragma omp parallel
    {
        min_num_threads = omp_get_num_threads();
        #pragma omp for reduction(min: min_parallel)
        for (int i = 0; i < size; i++) {
            if (table[i] < min_parallel) {
                min_parallel = table[i];
            }
        }
    } 
    min_end_parallel = omp_get_wtime();
    printf("Le Min avec une boucle Parallele est %d\n", min_parallel);
    double min_execution_time_parallel = min_end_parallel - min_start_parallel;
    printf("Le Temps d'Exécution Parallele: %f seconds\n", min_execution_time_parallel);

    // Comparaison des temps d'exécution pour le Max
    //  -------------------------------------------
    double max_speed_up = max_execution_time_sequential / max_execution_time_parallel;
    printf("L'acceleration cas de Max avec %d threads est: %f\n", max_num_threads, max_speed_up);
    printf("L'efficacite cas de Max avec %d threads est: %f\n", max_num_threads, max_speed_up / max_num_threads);

    // Comparaison des temps d'exécution pour le Min
    //  -------------------------------------------
    double min_speed_up = min_execution_time_sequential / min_execution_time_parallel;
    printf("L'acceleration cas de Min avec %d threads est: %f\n", min_num_threads, min_speed_up);
    printf("L'efficacite cas de Min avec %d threads est: %f\n", min_num_threads, min_speed_up / min_num_threads);

    // Libération de la mémoire
    free(table);
    return 0;
}