#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ROWS_A 500
#define COLS_A 500
#define COLS_B 500

int main() {
    int matriceA[ROWS_A][COLS_A], matriceB[COLS_A][COLS_B], matriceResultat[ROWS_A][COLS_B];
    double start, end;

    // Initialisation des matrices
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_A; j++) {
            matriceA[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < COLS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            matriceB[i][j] = rand() % 10;
        }
    }

    // Initialiser matriceResultat à zéro
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            matriceResultat[i][j] = 0;
        }
    }

    // Mesure du temps d'exécution pour la multiplication
    start = omp_get_wtime();

    // Multiplication des matrices
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
                for (int k = 0; k < COLS_A; k++) {
                matriceResultat[i][j] += matriceA[i][k] * matriceB[k][j];
            }
        }
    }

    end = omp_get_wtime();
    printf("Temps d'exécution pour la multiplication de matrices non carrées : %f secondes\n", end - start);

    return 0;
}
