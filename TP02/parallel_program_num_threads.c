#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500

int main() {
    int matriceA[N][N], matriceB[N][N], matriceResultat[N][N] = {0};
    double start, end;
    int num_threads[] = {1, 2, 4, 8};  // Nombre de threads à tester

    // Initialisation des matrices
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriceA[i][j] = rand() % 10;
            matriceB[i][j] = rand() % 10;
        }
    }

    for (int t = 0; t < 4; t++) {
        omp_set_num_threads(num_threads[t]);

        // Mesure du temps de multiplication parallèle
        start = omp_get_wtime();

        #pragma omp parallel for collapse(2)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matriceResultat[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    matriceResultat[i][j] += matriceA[i][k] * matriceB[k][j];
                }
            }
        }

        end = omp_get_wtime();
        printf("Temps d'exécution avec %d threads : %f secondes\n", num_threads[t], end - start);
    }

    return 0;
}
