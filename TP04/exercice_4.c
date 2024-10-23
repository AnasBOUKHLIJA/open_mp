#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define INITIAL_SIZE 100000000
#define SIZE_INCREMENT 100000000
#define NUM_TESTS 10

int main() {
    for (int test = 0; test < NUM_TESTS; test++) {
        int size = INITIAL_SIZE + test * SIZE_INCREMENT;
        
        // Initialisation du tableau d'entiers
        // --------------------------------------------
        int *table = (int *) malloc(size * sizeof(int));
        srand(time(NULL));
        if (table == NULL) {
            printf("Erreur lors de la location de la memoire!\n");
            return 1;
        }
        for (int i = 0; i < size; i++) {
            table[i] = i + 1;
        }

        // Mesure du temps d'exécution de la version séquentielle
        // --------------------------------------------
        double product_sequential = 1;
        double start_sequentialt, end_sequential;
        start_sequentialt = omp_get_wtime();
        for (int i = 0; i < size; i++) {
            product_sequential *= table[i];
        }
        end_sequential = omp_get_wtime();
        printf("Taille du tableau: %d, Le produit avec une boucle séquentielle est %f\n", size, product_sequential);
        double execution_time_sequential = end_sequential - start_sequentialt;
        printf("Le Temps d'Exécution Séquentielle: %f seconds\n", execution_time_sequential);

        // Mesure du temps d'exécution de la version parallèle avec OpenMP
        // --------------------------------------------
        double product_parallel = 1;
        double start_parallel, end_parallel;
        start_parallel = omp_get_wtime();
        int num_threads = 0;

        #pragma omp parallel 
        {
            num_threads = omp_get_num_threads();
            #pragma omp for reduction(*:product_parallel)
            for (int i = 0; i < size; i++) {
                product_parallel *= table[i];
            }
        }
        end_parallel = omp_get_wtime();
        printf("Taille du tableau: %d, Le produit avec une boucle parallèle est %f\n", size, product_parallel);
        double execution_time_parallel = end_parallel - start_parallel;
        printf("Le Temps d'Exécution parallèle (%d threads): %f seconds\n", num_threads, execution_time_parallel);

        // Comparaison des temps d'exécution
        //  -------------------------------------------
        double speed_up = execution_time_sequential / execution_time_parallel;
        printf("L'acceleration %d threads est: %f\n", num_threads, speed_up);
        printf("L'efficacite %d threads est: %f\n\n", num_threads, speed_up / num_threads);

        // Libération de la mémoire
        free(table);
    }

    return 0;
}
