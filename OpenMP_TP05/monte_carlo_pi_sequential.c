#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    // Nombre d'échantillons à générer
    int n     = 1000000000;
    int count = 0;

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Boucle pour générer des points aléatoires
    for (int i = 0; i < n; i++) {
        // Générer des coordonnées aléatoires dans le carré [0, 1] x [0, 1]
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        // Vérifier si le point est à l'intérieur du cercle de rayon 1
        if (x * x + y * y <= 1) {
            // Point à l'intérieur du cercle
            count++;  
        }
    }

    // Estimer la valeur de pi
    double pi = (double)count / n * 4;

    printf("Estimation de Pi = %f\n", pi);
    return 0;
}
