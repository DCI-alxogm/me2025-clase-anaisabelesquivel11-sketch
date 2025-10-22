//Ana Isabel Esquivel Castro
//436578
//Métodos Numéricos
//Tarea Método de Gauss
//Hacer un método que corra para cualquier matriz (en este caso de 3x3)
//Debe incluir: 
//->Leer la dimensión de la matriz de línea de comandos
//->Leer los coeficientes de A y B de la línea de comandos
//->Evaluar la necesidad de cambiar las filas por columnas y realizarlo (pivoteo)
//->Evaluar que el sistema esté bien condicionado, es decir, que no sea sensible a cambios de cifras siginificativas
//->Imprimir el resultado de la matriz



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DIM 10 //se emplea para definir el tamaño másximo de la matriz que usaremos
#define TOL 1e-10 // es la tolerancia para evitar los errores numéricos

int main() {
    int n, i, j, k; //declaramos variables
    double A[MAX_DIM][MAX_DIM], b[MAX_DIM], x[MAX_DIM]; //A es la matriz de coeficientes, b es el vector de términos independientes y x es el vector solución, n es la dimensión de la matriz
    double factor, temp, max_val;
    
    printf("Dimension de la matriz: ");
    scanf("%d", &n);//n es la dimensión de la matriz
    
    printf("Matriz A (%dx%d): \n", n, n); //en esta parte del cilco se lee la matriz A por la fila desde la entrada del usuario
    for(i = 0; i < n; i++) {
        printf("Fila %d: ", i+1);
        for(j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
    
    printf("Vector b: ");
    for(i = 0; i < n; i++) {
        scanf("%lf", &b[i]);
    }
    
    
    printf("\nSistema original:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) printf("%8.3f ", A[i][j]);
        printf("| %8.3f\n", b[i]);
    }
    
    
    for(i = 0; i < n; i++) { //aplicamos el pivoteo para evitar la división entre cero 

        int max_row = i;
        for(j = i+1; j < n; j++) {
            if(fabs(A[j][i]) > fabs(A[max_row][i])) max_row = j;
        }
        
        if(max_row != i) { //en esta paerte realizamos el intercambio de filas con la que se tiene el pivote más grande
            for(j = 0; j < n; j++) {
                temp = A[i][j];
                A[i][j] = A[max_row][j];
                A[max_row][j] = temp;
            }
            temp = b[i];
            b[i] = b[max_row];
            b[max_row] = temp;
            printf("Pivoteo: intercambiadas filas %d y %d\n", i+1, max_row+1);
        }
        
                        //normalización para escalar los valores de la fila para que estén en un rango similar y así quitar números muy grandes de los cálculos
        max_val = 0.0;
        for(j = 0; j < n; j++) {
            if(fabs(A[i][j]) > max_val) max_val = fabs(A[i][j]);
        }
        if(max_val > TOL) {
            for(j = 0; j < n; j++) A[i][j] /= max_val;
            b[i] /= max_val;
        }
        
     
        for(j = i+1; j < n; j++) { //eliminación gaussiana para crear los ceros debajo del elemento diagonal
          
            factor = A[j][i] / A[i][i]; //decide cuántas veces restar la fila pivote y 
            for(k = i; k < n; k++) { //simplifica la misma operación al vector b para poder mantener la equivalencia
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }
  
    int bien_condicionado = 1; //se verifics el condicionamiento para ver si es sensible a cambios de cifras significativas
    for(i = 0; i < n; i++) {
        if(fabs(A[i][i]) < TOL) {
            printf("ADVERTENCIA: Sistema mal condicionado\n");
            bien_condicionado = 0;
            break;
        }
    }
    if(bien_condicionado) printf("Sistema bien condicionado\n");
    
    for(i = n-1; i >= 0; i--) { // a partir de los resultados encontrados para las variables, se sustituyen los resultados hacia atrás.
        x[i] = b[i];
        for(j = i+1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    

    printf("\nSolucion:\n"); //se muestran los resultados de la matriz
    for(i = 0; i < n; i++) {
        printf("x%d = %f\n", i+1, x[i]);
    }
    
    return 0;
}