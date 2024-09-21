#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>

#define WIDTH 1600
#define HEIGHT 1600
#define MAX_ITER 1000

int mandelbrot(double complex c) {
    double complex z = 0 + 0*I;
    int iter;
    for (iter = 0; iter < MAX_ITER; iter++) {
        if (cabs(z) > 2.0) break;
        z = z*z + c;
    }
    return iter;
}

void generate_mandelbrot(unsigned char image[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double complex c = (x - WIDTH/2.0)*4.0/WIDTH + (y -HEIGHT/2.0)*4.0/HEIGHT*I;
            int value = mandelbrot(c);
            image[y][x] = (value == MAX_ITER) ? 0 : (255 * value / MAX_ITER);
        }
    }
}

int main() {
    double start, end;
    unsigned char image[HEIGHT][WIDTH];

    start = omp_get_wtime();

    generate_mandelbrot(image);

    end = omp_get_wtime();

    printf("Temps d'exécution : %f secondes\n", end - start);    
    
    FILE *fp = fopen("/home/anas/Desktop/mandelbrot.pgm", "wb");

    fprintf(fp, "P5\n%d %d\n255\n", WIDTH, HEIGHT);
    fwrite(image, 1, WIDTH*HEIGHT, fp);
    fclose(fp);
    printf("Image générée : mandelbrot.pgm\n");
    return 0;
}