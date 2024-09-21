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
    printf("%s\n", buffer);
    
    // Combinaison du deroulage de boucle et de la fusion de boucles avec OpenMP
    #pragma omp parallel for
    for (int i = 0; i < N; i += 4) {
        // Processing for array1
        if (i < N) {
            double temp = array1[i] * 1.5;         // Scaling
            double sqrt_value = sqrt(temp);       // Square root
            double log_value = log(sqrt_value);   // Natural log
            double sin_value = sin(log_value);    // Sine function
            double result = cos(sin_value);       // Cosine function
            array1[i] = (int)((result * 100) + array1[i] % 100); 
        }
        if (i + 1 < N) {
            double temp = array1[i + 1] * 1.5;         // Scaling
            double sqrt_value = sqrt(temp);       // Square root
            double log_value = log(sqrt_value);   // Natural log
            double sin_value = sin(log_value);    // Sine function
            double result = cos(sin_value);       // Cosine function
            array1[i + 1] = (int)((result * 100) + array1[i + 1] % 100); 
        }
        if (i + 2 < N) {
            double temp = array1[i + 2] * 1.5;         // Scaling
            double sqrt_value = sqrt(temp);       // Square root
            double log_value = log(sqrt_value);   // Natural log
            double sin_value = sin(log_value);    // Sine function
            double result = cos(sin_value);       // Cosine function
            array1[i + 2] = (int)((result * 100) + array1[i + 2] % 100); 
        }
        if (i + 3 < N) {
            double temp = array1[i + 3] * 1.5;         // Scaling
            double sqrt_value = sqrt(temp);       // Square root
            double log_value = log(sqrt_value);   // Natural log
            double sin_value = sin(log_value);    // Sine function
            double result = cos(sin_value);       // Cosine function
            array1[i + 3] = (int)((result * 100) + array1[i + 3] % 100); 
        }
        
        // Processing for array2
        if (i < N) {
            array2[i] = array2[i] + 5;
        }
        if (i + 1 < N) {
            array2[i + 1] = array2[i + 1] + 5;
        }
        if (i + 2 < N) {
            array2[i + 2] = array2[i + 2] + 5;
        }
        if (i + 3 < N) {
            array2[i + 3] = array2[i + 3] + 5;
        }
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