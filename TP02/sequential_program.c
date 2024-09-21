#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 500

int main() {

    int matriceA[N][N], matriceB[N][N], matriceResultat[N][N] = {0};
    double start, end;

    // Initialisation des matrices
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriceA[i][j] = rand() % 10;
            matriceB[i][j] = rand() % 10;
        }
    }

    // Mesure du temps de multiplication séquentielle
    start = omp_get_wtime();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriceResultat[i][j] = 0;
            for (int k = 0; k < N; k++) {
                matriceResultat[i][j] += matriceA[i][k] * matriceB[k][j];
            }
        }
    }

    end = omp_get_wtime();
    printf("Temps d'exécution séquentiel : %f secondes\n", end - start);

    return 0;
}
