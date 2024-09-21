#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <math.h> 

#define N 1000000000

int main() {
    int *array = (int*)malloc(N * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    } 

    // Time variables
    time_t now;
    struct tm *local;
    char buffer[80];

    // Initialisation du tableau
    for (int i = 0; i < N; i++) {
        array[i] = i;
    }

    // Print the current date and time before starting the computation
    time(&now);
    local = localtime(&now);
    strftime(buffer, sizeof(buffer), "Start time: %Y-%m-%d %H:%M:%S", local);
    printf("%s\n", buffer);

    // Déroulage de boucle applique avec OpenMP
    #pragma omp parallel for
    for (int i = 0; i < N; i += 4) {
        if (i < N) {
            double temp = array[i] * 1.5;         // Scaling
            double sqrt_value = sqrt(temp);       // Square root
            double log_value = log(sqrt_value);   // Natural log
            double sin_value = sin(log_value);    // Sine function
            double result = cos(sin_value);       // Cosine function
            array[i] = (int)((result * 100) + array[i] % 100); 
        }
        if (i + 1 < N) {
            double temp = array[i + 1] * 1.5;         // Scaling
            double sqrt_value = sqrt(temp);       // Square root
            double log_value = log(sqrt_value);   // Natural log
            double sin_value = sin(log_value);    // Sine function
            double result = cos(sin_value);       // Cosine function
            array[i + 1] = (int)((result * 100) + array[i + 1] % 100); 
        }
        if (i + 2 < N) {
            double temp = array[i + 2] * 1.5;         // Scaling
            double sqrt_value = sqrt(temp);       // Square root
            double log_value = log(sqrt_value);   // Natural log
            double sin_value = sin(log_value);    // Sine function
            double result = cos(sin_value);       // Cosine function
            array[i + 2] = (int)((result * 100) + array[i + 2] % 100); 
        }
        if (i + 3 < N) {
            double temp = array[i + 3] * 1.5;         // Scaling
            double sqrt_value = sqrt(temp);       // Square root
            double log_value = log(sqrt_value);   // Natural log
            double sin_value = sin(log_value);    // Sine function
            double result = cos(sin_value);       // Cosine function
            array[i + 3] = (int)((result * 100) + array[i + 3] % 100); 
        }
    }

    // Print the current date and time after completing the computation
    time(&now);
    local = localtime(&now);
    strftime(buffer, sizeof(buffer), "End time: %Y-%m-%d %H:%M:%S", local);
    printf("%s\n", buffer);

    // Free the allocated memory
    free(array);

    return 0;
}