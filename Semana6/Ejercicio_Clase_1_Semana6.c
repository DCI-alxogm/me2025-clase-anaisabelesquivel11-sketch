//Ana Isabel Esquivel Castro
//436578
//Ejercicio de clase 1 Semana 6 (ACTUALIZACIÓN)
   
  
#include <stdio.h>
#include <math.h>

// Definición de la función f(c)
float f(float c) {
    return (9.81 * 68.1) / c * (1 - exp(-(c / 68.1) * 10)) - 40;
}

int main() {
    float Err_max = 0.01;
    float a = 4, b = 20, k, Err, kold;

    kold = a;

    do {
        k = (a + b) / 2;  // punto medio
        Err = fabsf((k - kold) / k);

        if (f(k) * f(a) < 0) {
            b = k;
        } else {
            a = k;
        }

        kold = k;
    } while (Err > Err_max);

    printf("La raíz aproximada es: %f\n", k);
    printf("f(c_raiz) = %f\n", f(k));

    return 0;
}

