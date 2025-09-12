//436578
//Ejercicio de clase 3, Semana 6
//ANÀLISIS COMPARATIVO DE MÈTODO DE BISECCIÒN Y FALSA POSICIÒN PARA DIFERENTES FUNCIONES DADAS
//Mètodo de falsa posición, funciòn 2

#include <stdio.h>
#include <math.h>

// Definimos la función
float f(float c) {
    return pow(c, 10) - 1;
}

int main() {
    float Err_max = 0.0001;  
    float a0 = 4, b0 = 20; 
    float a = a0, b = b0;      
    float k, fk, Err, Eapr, kold;
    int n = 0;                 
    float Ea_teorico;          

    printf("Iter \t Raiz \t\t f(k) \t\t Eaprox \t E_r \t\t Ea_teorico\n");
//Incluì Iter para no estar contanto linea por linea al comparar
    kold = a;

    do {
        k = (f(b) * a - f(a) * b) / (f(b) - f(a));
        fk = f(k);
        n++;  

        if (f(k) * f(a) < 0) {
            b = k;
        } else {
            a = k;
        }

        Eapr = fabs(k - kold);     
        Err  = fabs(Eapr / k);     
        Ea_teorico = (b0 - a0) / pow(2, n);   

        printf("%d \t %f \t %f \t %f \t %f \t %f\n", n, k, fk, Eapr, Err, Ea_teorico);

    } while (Err > Err_max);

    printf("\nLa raíz aproximada es: %f\n", k);
    printf("f(c_raiz) = %f\n", f(k));
/////////// :)
    return 0;
}
