#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {

    int n = 1000000000;
    int chunk_size = n / 32;

    // ----- Version Séquentielle -----
    unsigned int seed_seq = time(NULL);
    double start_time_seq = omp_get_wtime();
    int global_count_seq = 0;

    for (int i = 0; i < n; i++) {
        double x = (double)rand_r(&seed_seq) / RAND_MAX; 
        double y = (double)rand_r(&seed_seq) / RAND_MAX; 

        if (x * x + y * y <= 1) {
            global_count_seq++;
        }
    }

    double end_time_seq = omp_get_wtime();
    double pi_seq = (double)global_count_seq / n * 4;
    printf("Version séquentielle: Estimation de Pi = %f, Temps d'exécution = %f secondes\n", pi_seq, end_time_seq - start_time_seq);

    // ----- Version Parallèle -----
    for (int num_threads = 2; num_threads <= 8; num_threads += 2) {
        int global_count = 0;
        double start_time, end_time;

        omp_set_num_threads(num_threads);

        start_time = omp_get_wtime();

        #pragma omp parallel
        {
            int local_count = 0;
            unsigned int seed = time(NULL) ^ omp_get_thread_num();

            #pragma omp for schedule(dynamic, chunk_size)
            for (int i = 0; i < n; i++) {
                double x = (double)rand_r(&seed) / RAND_MAX;
                double y = (double)rand_r(&seed) / RAND_MAX;

                if (x * x + y * y <= 1) {
                    local_count++;
                }
            }

            #pragma omp atomic
            global_count += local_count;
        }

        end_time = omp_get_wtime();

        double pi = (double)global_count / n * 4;

        // Calcul du speedup et de l'efficacité
        double speedup = (end_time_seq - start_time_seq) / (end_time - start_time);
        double efficiency = speedup / num_threads;

        printf("Threads : %d, Estimation de Pi = %f, Temps d'exécution = %f secondes, Speedup = %f, Efficacité = %f\n", 
               num_threads, pi, end_time - start_time, speedup, efficiency);
    }

    return 0;
}
