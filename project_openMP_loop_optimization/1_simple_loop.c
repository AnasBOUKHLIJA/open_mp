#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h> 
#include <omp.h>
#include "performance_logger.h"

#define N 100000000
#define PROGRAMNAME "simple_loop"

int main() {
    
    int *array1 = (int*)malloc(N * sizeof(int));
    int *array2 = (int*)malloc(N * sizeof(int));
    if (array1 == NULL || array2 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    } 

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
    // Print the current date and time before starting the computation
    // ------------------------------------------------------------------------------------
    start = omp_get_wtime();
    time(&now);
    local = localtime(&now);
    strftime(startDate, sizeof(startDate), "%Y-%m-%d %H:%M:%S", local);
    printf("Start time: %s\n", startDate);

    // ------------------------------------------------------------------------------------
    // Simple Loops
    // ------------------------------------------------------------------------------------
    for (int i = 0; i < N; i++) {
        double temp = array1[i] * 1.5;
        double sqrt_value = sqrt(temp);
        double log_value = log(sqrt_value);
        double sin_value = sin(log_value);
        double result = cos(sin_value);

        array1[i] = (int)((result * 100) + array1[i] % 100);
    }

    for (int i = 0; i < N; i++) {
        double temp = array2[i] * 1.5;
        double sqrt_value = sqrt(temp);
        double log_value = log(sqrt_value);
        double sin_value = sin(log_value);
        double result = cos(sin_value);

        array2[i] = (int)((result * 100) + array2[i] % 100);
    }

    // ------------------------------------------------------------------------------------
    // Print the current date and time after completing the computation
    // ------------------------------------------------------------------------------------
    end = omp_get_wtime();
    time(&now);
    local = localtime(&now);
    strftime(endDate, sizeof(endDate), "%Y-%m-%d %H:%M:%S", local);
    printf("End time: %s\n", endDate);

    double executionTime = end - start;
    printf("Execution Time: %f seconds\n", end - start);

    appendToCSV(PROGRAMNAME, omp_get_num_threads() ,executionTime, startDate, endDate);

    // ------------------------------------------------------------------------------------
    // Free the allocated memory
    // ------------------------------------------------------------------------------------
    free(array1);
    free(array2);

    return 0;
}
