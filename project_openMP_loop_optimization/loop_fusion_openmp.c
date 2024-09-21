#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <math.h> 

#define N 1000000000

int main() {
    int *array1 = (int*)malloc(N * sizeof(int));
    int *array2 = (int*)malloc(N * sizeof(int));
    if (array1 == NULL || array2 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    } 
    
    // Time variables
    time_t now;
    struct tm *local;
    char buffer[80];

    // Initialisation des tableaux
    for (int i = 0; i < N; i++) {
        array1[i] = i;
        array2[i] = i;
    }

    // Print the current date and time before starting the computation
    time(&now);
    local = localtime(&now);
    strftime(buffer, sizeof(buffer), "Start time: %Y-%m-%d %H:%M:%S", local);
    printf("%s\n", buffer);;

    // Fusion de boucles appliquee avec OpenMP
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        double temp1 = array1[i] * 2;         // Scaling
        double sqrt_value1 = sqrt(temp1);       // Square root
        double log_value1 = log(sqrt_value1);   // Natural log
        double sin_value1 = sin(log_value1);    // Sine function
        double result1 = cos(sin_value1);       // Cosine function
        array1[i] = (int)((result1 * 100) + array1[i] % 100);

        double temp2 = array2[i] + 5;         // Scaling
        double sqrt_value2 = sqrt(temp2);       // Square root
        double log_value2 = log(sqrt_value2);   // Natural log
        double sin_value2 = sin(log_value2);    // Sine function
        double result2 = cos(sin_value2);       // Cosine function
        array2[i] = (int)((result2 * 100) + array2[i] % 100);
    }

    // Print the current date and time after completing the computation
    time(&now);
    local = localtime(&now);
    strftime(buffer, sizeof(buffer), "End time: %Y-%m-%d %H:%M:%S", local);
    printf("%s\n", buffer);
    // Free the allocated memory
    free(array1);
    free(array2);

    return 0;
}