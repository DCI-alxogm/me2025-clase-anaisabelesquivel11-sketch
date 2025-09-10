//Ana Isabel Esquivel Castro
//436578
//Ejercicio de clase 2 Semana 6 (ACTUALIZACIÓN)
//Encontrar las reíces de la función f(x) =sen(10x)-cos(3x) 
//en el rango de x=3 a x=5 
//con un error relativomáximo entre iteraciones de Ermax= 0.0001
//Determinar si la relación Ea= (DeltaX)sub1/2^n
  
#include <stdio.h>
#include <math.h>

// Definición de la función
float f(float c) {
    return sen(10*x)-cos(3*x);   // <-- aquí pones la función que quieras
}

int main() {
    float Err_max = 0.001;
    float a = 4, b = 20, k, fk, Err, Eapr, kold = INFINITY;

    printf("Raiz \t f(k) \t Eaprox \t E_r \n");

    kold = a;

    do {
        k = (a + b) / 2;  // punto medio, primera estimación de la raíz 
        fk = f(k);

        if (f(k) * f(a) < 0) {
            b = k;
        } else {
            a = k;
        }

        Eapr = k - kold; 
        Err = fabs(Eapr / k);
        kold = k;

        printf( "%f \t %f \t %f \t %f \n", k, fk, Eapr, Err);

    } while (Err > Err_max);

    printf("\n La raíz aproximada es: %f\n", k);
    printf("f(c_raiz) = %f\n", f(k));
printf ()
    return 0;
}
