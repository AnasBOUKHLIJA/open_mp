#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>  
#include <string.h>
#include "performance_logger.h"

#define PROGRAMNAME "parallel_loop_fusion_openmp"

int main() {
    
    int *array1 = (int*)malloc(N * sizeof(int));
    int *array2 = (int*)malloc(N * sizeof(int));
    if (array1 == NULL || array2 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    } 
    
    // --------------------------------------------------------------
    // Array of thread counts to test
    // --------------------------------------------------------------
    int maxThreadsSupported = omp_get_max_threads();
    int totalTestCounts = (maxThreadsSupported / 2);
    int threadCounts[totalTestCounts];

    for (int i = 0; i < totalTestCounts; i++) {
        threadCounts[i] = (i + 1) * 2;
    }

    // --------------------------------------------------------------
    // Time variables
    // --------------------------------------------------------------
    double start, end;
    time_t now;
    struct tm *local;
    char startDate[80], endDate[80];

    // --------------------------------------------------------------
    // Tables Initialization
    // --------------------------------------------------------------
    for (int i = 0; i < N; i++) {
        array1[i] = i;
        array2[i] = i;
    }

    // --------------------------------------------------------------
    // Loop Fusion Applied with OpenMP
    // --------------------------------------------------------------
    for (int test = 0; test < totalTestCounts; test++) {

        // Set the number of threads
        // --------------------------------------------------------------
        int threadsCount = threadCounts[test];
        omp_set_num_threads(threadsCount);

        // Initialize thread execution times to zero
        // --------------------------------------------------------------
        double thread_times[threadsCount];
        for (int i = 0; i < threadsCount; i++) {
            thread_times[i] = 0.0;  // Initialize to zero
        }

        // Print the current date and time before starting the computation
        // --------------------------------------------------------------
        start = omp_get_wtime();
        time(&now);
        local = localtime(&now);
        strftime(startDate, sizeof(startDate), "%Y-%m-%d %H:%M:%S", local);
        printf("Start time (Threads: %d): %s\n", threadsCount, startDate);

        #pragma omp parallel
        {
            #pragma omp for schedule(guided)
            for (int i = 0; i < N; i++) {
                double thread_start_time = omp_get_wtime();

                double temp1 = array1[i] * 2;
                double sqrt_value1 = sqrt(temp1);
                double log_value1 = log(sqrt_value1);
                double sin_value1 = sin(log_value1);
                double result1 = cos(sin_value1);
                array1[i] = (int)((result1 * 100) + array1[i] % 100);

                double temp2 = array2[i] + 5;
                double sqrt_value2 = sqrt(temp2);
                double log_value2 = log(sqrt_value2);
                double sin_value2 = sin(log_value2);
                double result2 = cos(sin_value2);
                array2[i] = (int)((result2 * 100) + array2[i] % 100);
                            
                double thread_end_time = omp_get_wtime();

                // Accumulate time
                #pragma omp atomic
                thread_times[omp_get_thread_num()] += thread_end_time - thread_start_time;
            }
        }

        // Format thread execution times as JSON
        // --------------------------------------------------------------
        char thread_times_string[2048] = "{";
        for (int i = 0; i < threadsCount; i++) {
            char temp[50];
            snprintf(temp, sizeof(temp), "\"thread_%d\": %f", i + 1, thread_times[i]);
            strcat(thread_times_string, temp);
            if (i < threadsCount - 1) strcat(thread_times_string, ", ");
        }
        strcat(thread_times_string, "}");  // End the JSON string

        // Print the JSON string (optional)
        printf("Execution times (JSON): %s\n", thread_times_string);

        // Print the current date and time after completing the computation
        // --------------------------------------------------------------
        end = omp_get_wtime();
        time(&now);
        local = localtime(&now);
        strftime(endDate, sizeof(endDate), "%Y-%m-%d %H:%M:%S", local);
        printf("End time (Threads: %d): %s\n", threadsCount, endDate);

        double executionTime = end - start;
        printf("Execution Time (Threads: %d): %f seconds\n", threadsCount, executionTime);


        // Append the execution data and JSON thread times to CSV
        // --------------------------------------------------------------
        appendToCSV(PROGRAMNAME, startDate, endDate, threadsCount ,executionTime, thread_times_string);
    }

    // --------------------------------------------------------------
    // Free the allocated memory
    // --------------------------------------------------------------
    free(array1);
    free(array2);

    return 0;
}