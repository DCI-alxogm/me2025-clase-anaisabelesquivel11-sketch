//Ana Isabel Esquivel Castro
//436578
//MN
//Método para optimización 2D
//Usar en especial el método de la malla o Grid
//Para este código se debe tener la función dentro de él, no se la pediré al usuario en este caso

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR 200

char funcion_global[MAX_EXPR]; //declarar la función global
double funcion(double x, double y) {
    return y - x - 2*x*x - 2*x*y - y*y; //ingresamos la función que se va a optimizar
}

void optimizar_2d(int buscar_maximo) { //funcón para otimizar
    double x_min, x_max, y_min, y_max;
    int puntos_x, puntos_y;
    double mejor_x, mejor_y, mejor_valor;
    double paso_x, paso_y;
    int i, j;    
    
    printf("rango de x: "); //pedir al usuario intervalos de x,y y números de puntos a evaluar
    scanf("%lf %lf", &x_min, &x_max);
    printf("rango de y: ");
    scanf("%lf %lf", &y_min, &y_max);
    printf("número de puntos en x: ");
    scanf("%d", &puntos_x);
    printf("número de puntos en y: ");
    scanf("%d", &puntos_y);
    
    if (x_min >= x_max || y_min >= y_max || puntos_x <= 0 || puntos_y <= 0) { //cliclo for para verificar que los datos ingresadps sean números 
        printf("Los datos del rango no son válidos\n");
        return;
    }

    paso_x = (x_max - x_min) / (puntos_x - 1);
    paso_y = (y_max - y_min) / (puntos_y - 1);
  
    mejor_x = x_min;
    mejor_y = y_min;
    mejor_valor = funcion(x_min, y_min);
    printf("x\t\ty\t\tf(x,y)\n");
    for (i = 0; i < puntos_x; i++) {
        double x = x_min + i * paso_x;
        
        for (j = 0; j < puntos_y; j++) {
            double y = y_min + j * paso_y;
            double valor_actual = funcion(x, y);

            printf("%8.4f\t%8.4f\t%10.6f\n", x, y, valor_actual);
            
            if (buscar_maximo) {
                if (valor_actual > mejor_valor) {
                    mejor_valor = valor_actual;
                    mejor_x = x;
                    mejor_y = y;
                }
            } else {
                if (valor_actual < mejor_valor) {
                    mejor_valor = valor_actual;
                    mejor_x = x;
                    mejor_y = y;
                }
            }
        }
    }
  
    printf("Resultado %s\n", buscar_maximo ? "Máximo" : "Mínimo"); // CORRECCIÓN: agregué %s
    printf("Punto optimo:\n");
    printf("x = %12.8f\n", mejor_x);
    printf("y = %12.8f\n", mejor_y);
    printf("f(x,y) = %12.8f\n", mejor_valor);
}

int main() {
    int opcion;

    strcpy(funcion_global, "y - x - 2*x*x - 2*x*y - y*y"); //ingresar la función a trababajar
    
    printf("Funcion actual: f(x,y) = %s\n", funcion_global);
  
    printf("\nSelecciona el número de la opción que buscas\n");
    printf("1. Mínimo\n");
    printf("2. Máximo\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    
    if (opcion == 1) {
        optimizar_2d(0);
    } else if (opcion == 2) {
        optimizar_2d(1);
    } else {
        printf("La opción seleccionada no es válida\n");
        return 1;
    }
     
    return 0;
}