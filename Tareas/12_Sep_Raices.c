//Ana Isabel Esquivel Castro
//436578
//Ejercicio de clase 2 Semana 6 (ACTUALIZACIÓN)
//Encontrar las reíces de la función f(x) =sen(10x)-cos(3x) 
//en el rango de x=3 a x=5 
//con un error relativomáximo entre iteraciones de Ermax= 0.0001
//Determinar si la relación Ea= (DeltaX)sub1/2^n
  
#include <stdio.h>
#include <math.h>

// Definición de la función f(x) = sin(10x) - cos(3x)
float f(float c) {
    return sin(10*c) - cos(3*c);
}

int main() {
    float Err_max = 0.0001f;   // Error máximo permitido
    float a0 = 3, b0 = 5;      // Intervalo inicial dado
    float a = a0, b = b0;      // Copias para ir actualizando
    float k, fk, Err, Eapr, kold;
    int n = 0;                 // contador de iteraciones
    float Ea_teorico;          // error teórico

    printf("Iter \t Raiz \t\t f(k) \t\t Eaprox \t E_r \t\t Ea_teorico\n");

    kold = a;   // inicializamos kold

    do {
        k = (a + b) / 2.0f;  // Punto medio
        fk = f(k);
        n++;  // aumentar número de iteraciones

        // Método de bisección
        if (f(k) * f(a) < 0) {
            b = k;
        } else {
            a = k;
        }

        Eapr = fabs(k - kold);     // error aproximado
        Err  = fabs(Eapr / k);     // error relativo
        Ea_teorico = (b0 - a0) / pow(2, n);   // error teórico
        kold = k;

        printf("%d \t %f \t %f \t %f \t %f \t %f\n", n, k, fk, Eapr, Err, Ea_teorico);

    } while (Err > Err_max);

    printf("\nLa raíz aproximada es: %f\n", k);
    printf("f(c_raiz) = %f\n", f(k));

    return 0;
}
