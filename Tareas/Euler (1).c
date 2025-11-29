//Ana Isabel Esquivel Castro
//436578
//MN
//Tarea EDO
//Este es el primer código con el método de euler 

#include <stdio.h>
#include <stdlib.h>
void derivs(double t, double x, double y, double *dx, double *dy){
    *dx = x + y;// Esta es la primera ecuación
    *dy = -x + y;//y esta la segunda ecuación del sistema
}

int main(){
    double t = 0.0, h = 0.1;//inicio el tiempo y el paso
    double x = 1.0, y = 0.0;//valores iniciales que me dieron
    double dx_dt, dy_dt;//aquí guardaré las derivadas
    
    for(int i = 0; i < 10; i++){//Voy a hacer 10 iteraciones
        derivs(t, x, y, &dx_dt, &dy_dt);//lamo a la función para calcular
        
        x = x + h * dx_dt;//actualizo x con Euler
        y = y + h * dy_dt;//actualizo y igual
        t = t + h;
        
        printf("t=%.2f  x=%.4f  y=%.4f\n", t, x, y);//modtrar resultados
    }
    
    return 0;//término el programa
}