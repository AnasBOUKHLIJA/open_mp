#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <math.h> 
#include "performance_logger.h"

#define N 100000000
#define PROGRAMNAME "combined_optimizations_openmp"

int main() {

    int *array1 = (int*)malloc(N * sizeof(int));
    int *array2 = (int*)malloc(N * sizeof(int));
    if (array1 == NULL || array2 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    } 

    // ------------------------------------------------------------------------------------
    // Array of thread counts to test
    // ------------------------------------------------------------------------------------
    int maxThreadsSupported = omp_get_max_threads();
    int totalTestCounts = (maxThreadsSupported / 2);
    int threadCounts[totalTestCounts];

    for (int i = 0; i < totalTestCounts; i++) {
        threadCounts[i] = (i + 1) * 2;
    }1;

    // ------------------------------------------------------------------------------------
    // Time variables
    // ------------------------------------------------------------------------------------
    double start, end;
    time_t now;
    struct tm *local;
    char startDate[80], endDate[80];

    // ------------------------------------------------------------------------------------
    // Tables Initialization
    // ------------------------------------------------------------------------------------
    for (int i = 0; i < N; i++) {
        array1[i] = i;
        array2[i] = i;
    }

    // ------------------------------------------------------------------------------------
    // Combination of Loop Unrolling and Loop Fusion with OpenMP
    // ------------------------------------------------------------------------------------
    for (int test = 0; test < totalTestCounts; test++) {

        // Set the number of threads
        // ------------------------------------------------------------------------------------
        int threadsCount = threadCounts[test];
        omp_set_num_threads(threadsCount);

        // Print the current date and time before starting the computation
        // ------------------------------------------------------------------------------------
        start = omp_get_wtime();
        time(&now);
        local = localtime(&now);
        strftime(startDate, sizeof(startDate), "%Y-%m-%d %H:%M:%S", local);
        printf("Start time (Threads: %d): %s\n", threadsCount, startDate);


        #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < N; i += 4) {

                // Processing for array1
                // ------------------------------------------------------------------------------------
                if (i < N) {
                    double temp = array1[i] * 1.5;
                    double sqrt_value = sqrt(temp);
                    double log_value = log(sqrt_value);
                    double sin_value = sin(log_value);
                    double result = cos(sin_value);
                    array1[i] = (int)((result * 100) + array1[i] % 100); 
                }
                if (i + 1 < N) {
                    double temp = array1[i + 1] * 1.5;
                    double sqrt_value = sqrt(temp);
                    double log_value = log(sqrt_value);
                    double sin_value = sin(log_value);
                    double result = cos(sin_value);
                    array1[i + 1] = (int)((result * 100) + array1[i + 1] % 100); 
                }
                if (i + 2 < N) {
                    double temp = array1[i + 2] * 1.5;
                    double sqrt_value = sqrt(temp);
                    double log_value = log(sqrt_value);
                    double sin_value = sin(log_value);
                    double result = cos(sin_value);
                    array1[i + 2] = (int)((result * 100) + array1[i + 2] % 100); 
                }
                if (i + 3 < N) {
                    double temp = array1[i + 3] * 1.5;
                    double sqrt_value = sqrt(temp);
                    double log_value = log(sqrt_value);
                    double sin_value = sin(log_value);
                    double result = cos(sin_value);
                    array1[i + 3] = (int)((result * 100) + array1[i + 3] % 100); 
                }
                
                // Processing for array2
                // ------------------------------------------------------------------------------------
                if (i < N) {
                    double temp = array2[i] * 1.5;
                    double sqrt_value = sqrt(temp);
                    double log_value = log(sqrt_value);
                    double sin_value = sin(log_value);
                    double result = cos(sin_value);
                    array2[i] = (int)((result * 100) + array2[i] % 100); 
                }
                if (i + 1 < N) {
                    double temp = array2[i + 1] * 1.5;
                    double sqrt_value = sqrt(temp);
                    double log_value = log(sqrt_value);
                    double sin_value = sin(log_value);
                    double result = cos(sin_value);
                    array2[i + 1] = (int)((result * 100) + array2[i + 1] % 100); 
                }
                if (i + 2 < N) {
                    double temp = array2[i + 2] * 1.5;
                    double sqrt_value = sqrt(temp);
                    double log_value = log(sqrt_value);
                    double sin_value = sin(log_value);
                    double result = cos(sin_value);
                    array2[i + 2] = (int)((result * 100) + array2[i + 2] % 100); 
                }
                if (i + 3 < N) {
                    double temp = array2[i + 3] * 1.5;
                    double sqrt_value = sqrt(temp);
                    double log_value = log(sqrt_value);
                    double sin_value = sin(log_value);
                    double result = cos(sin_value);
                    array2[i + 3] = (int)((result * 100) + array2[i + 3] % 100); 
                }
            }
        }

        // Print the current date and time after completing the computation
        // ------------------------------------------------------------------------------------
        end = omp_get_wtime();
        time(&now);
        local = localtime(&now);
        strftime(endDate, sizeof(endDate), "%Y-%m-%d %H:%M:%S", local);
        printf("End time (Threads: %d): %s\n", threadsCount, endDate);

        double executionTime = end - start;
        printf("Execution Time (Threads: %d): %f seconds\n", threadsCount, executionTime);

        appendToCSV(PROGRAMNAME, threadsCount ,executionTime, startDate, endDate);
    }
    // ------------------------------------------------------------------------------------
    // Free the allocated memory
    // ------------------------------------------------------------------------------------
    free(array1);
    free(array2);

    return 0;
}