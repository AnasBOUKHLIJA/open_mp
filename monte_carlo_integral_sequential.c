#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction à intégrer
double f(double x) {
    return x * x;  // f(x) = x^2
}

int main() {
    int n, i;
    double x, sum = 0.0, integral;

    // Nombre d'échantillons à générer
    n = 1000000;

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Boucle pour générer des points aléatoires
    for (i = 0; i < n; i++) {
        // Générer un point aléatoire dans l'intervalle [0, 1]
        x = (double)rand() / RAND_MAX;

        // Ajouter la valeur de la fonction f(x) à la somme
        sum += f(x);
    }

    // Estimer l'intégrale
    integral = sum / n;  // La moyenne de f(x) sur l'intervalle [0, 1]

    printf("Estimation de l'intégrale de f(x) = x^2 sur [0, 1] = %f\n", integral);
    return 0;
}
