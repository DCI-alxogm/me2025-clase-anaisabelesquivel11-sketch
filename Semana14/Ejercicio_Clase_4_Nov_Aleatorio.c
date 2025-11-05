//Ana Isabel Esquivel Castro
//436578
//MN
//Método para optimización 2D - Búsqueda Aleatoria
//Para este código se debe tener la función dentro de él

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> //librería que no había usado xd
#include <string.h> 

#define MAX_EXPR 200

char funcion_global[MAX_EXPR]; //declarar la función global

double funcion(double x, double y) {
    return y - x - 2*x*x - 2*x*y - y*y; //ingresamos la función que se va a optimizar
}

void optimizar_aleatorio(int buscar_maximo) { //función para optimizar por método aleatorio
    double x_min, x_max, y_min, y_max;
    int iteraciones;
    double mejor_x, mejor_y, mejor_valor;
    int i, iteracion_mejor = 0;

    srand(time(NULL));//se mete una semilla de números aleatorios
    
    printf("rango de x: "); //pedir al usuario intervalos de x,y y número de iteraciones
    scanf("%lf %lf", &x_min, &x_max);
    printf("rango de y: ");
    scanf("%lf %lf", &y_min, &y_max);
    printf("número de iteraciones: ");
    scanf("%d", &iteraciones);
    
    if (x_min >= x_max || y_min >= y_max || iteraciones <= 0) {//verificar que los datos ingresados sean válidos
        printf("Los datos del rango no son válidos\n");
        return;
    }

    mejor_x = x_min + (double)rand() / RAND_MAX * (x_max - x_min);//inicializar con el primer punto aleatorio
    mejor_y = y_min + (double)rand() / RAND_MAX * (y_max - y_min);
    mejor_valor = funcion(mejor_x, mejor_y);
    iteracion_mejor = 1;
    
    printf("iteración\tx\t\ty\t\tf(x,y)\t\tMejor Valor\n");
    printf("%d\t\t%8.4f\t%8.4f\t%10.6f\t%10.6f\n", 1, mejor_x, mejor_y, mejor_valor, mejor_valor);
    
    for (i = 2; i <= iteraciones; i++) {

        double x_actual = x_min + (double)rand() / RAND_MAX * (x_max - x_min);//generar punto aleatorio
        double y_actual = y_min + (double)rand() / RAND_MAX * (y_max - y_min);
        double valor_actual = funcion(x_actual, y_actual);
        
        if (i % (iteraciones / 10) == 0 || i == iteraciones) { 
            if ((buscar_maximo && valor_actual > mejor_valor) || (!buscar_maximo && valor_actual < mejor_valor)) {
                printf(" *\n");//indicador de nuevo mejor valor
            } else {
                printf("\n");
            }
        }

        if (buscar_maximo) { //actualizar el mejor valor :)
            if (valor_actual > mejor_valor) {
                mejor_valor = valor_actual;
                mejor_x = x_actual;
                mejor_y = y_actual;
                iteracion_mejor = i;
            }
        } else {
            if (valor_actual < mejor_valor) {
                mejor_valor = valor_actual;
                mejor_x = x_actual;
                mejor_y = y_actual;
                iteracion_mejor = i;
            }
        }
    }
    printf("Resultado %s encontrado en la iteración %d\n", buscar_maximo ? "Máximo" : "Mínimo", iteracion_mejor);
    printf("Punto óptimo:\n");
    printf("x = %12.8f\n", mejor_x);
    printf("y = %12.8f\n", mejor_y);
    printf("f(x,y) = %12.8f\n", mejor_valor);

}

int main() {
    int opcion;

    strcpy(funcion_global, "y - x - 2*x*x - 2*x*y - y*y"); //ingresar la función a trabajar
    printf("Funcion actual: f(x,y) = %s\n", funcion_global);
  
    printf("\nSelecciona el número de la opción que buscas\n");
    printf("1. Mínimo\n");
    printf("2. Máximo\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    
    if (opcion == 1) {
        optimizar_aleatorio(0); // Buscar mínimo
    } else if (opcion == 2) {
        optimizar_aleatorio(1); // Buscar máximo
    } else {
        printf("La opción seleccionada no es válida\n");
        return 1;
    }
     
    return 0;
}