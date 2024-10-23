#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    int n = 1000000000;
    int chunk_size = n / 32;

    srand(time(NULL));

    for (int num_threads = 2; num_threads <= 8; num_threads+=2) {
        int global_count = 0;
        double start_time, end_time;

        // Set the number of threads
        omp_set_num_threads(num_threads);

        start_time = omp_get_wtime(); // Start timing

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

        printf("Threads : %d, Estimation de Pi = %f, Temps d'exécution = %f secondes\n", num_threads, pi, end_time - start_time);
    }

    return 0;
}
