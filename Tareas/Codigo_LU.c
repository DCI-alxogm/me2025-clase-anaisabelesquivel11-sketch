//Ana Isabel Esquivel Castro
//436578
//Métodos Numéricos 
//Realizar un código para factorización LU para la matriz mostrada en claase. 
//Para este ejercicio me basé en los códigos de Gauss y Gauss Joedan, en cuanto 
//al error empleado y la tolerancia que usé en los otros dos códigos
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DIM 10 // tolerancia
#define TOL 1e-10 //error maximo permitido

int main() { //pedimos al usuario el tamaño de la matriz A y sus respectivos valores para cada posición
    int n, i, j, k;
    double A[MAX_DIM][MAX_DIM], L[MAX_DIM][MAX_DIM], U[MAX_DIM][MAX_DIM];
    double b[MAX_DIM], y[MAX_DIM], x[MAX_DIM];
    
    printf("Dimension de la matriz (3 para 3x3): ");
    scanf("%d", &n);
    
    printf("Matriz A (%dx%d):\n", n, n);
    for(i = 0; i < n; i++) {
        printf("Fila %d: ", i+1);
        for(j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
    printf("Vector b: "); //pedimos al usuario ingresar valores para el vector b
     
    for(i = 0; i < n; i++) {
        scanf("%lf", &b[i]);
    }
    
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i == j)
                L[i][j] = 1.0;  // sabemos que la diagonal  de L es 1
            else
                L[i][j] = 0.0;
            U[i][j] = 0.0;
        }
    }
    
    
    for(i = 0; i < n; i++) { //usando el método de doolittle, hacemos la factorización de LU
        // Calcular U
        for(j = i; j < n; j++) {
            U[i][j] = A[i][j];
            for(k = 0; k < i; k++) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
        
        
        for(j = i + 1; j < n; j++) { //calculamos L
            L[j][i] = A[j][i];
            for(k = 0; k < i; k++) {
                L[j][i] -= L[j][k] * U[k][i];
            }
            L[j][i] /= U[i][i];
        }
    }
    
    for(i = 0; i < n; i++) { //resolvemos Ly=b con sustitución haciana adelante.
        y[i] = b[i];
        for(j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
        y[i] /= L[i][i];
    }
  
    for(i = n-1; i >= 0; i--) { //resolvemos Ux para y con la sustitucion hacia atrás
        x[i] = y[i];
        for(j = i+1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }

    printf("\nMatriz L:\n"); //resultados
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%8.3f ", L[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMatriz U:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%8.3f ", U[i][j]);
        }
        printf("\n");
    }
    
    printf("\nSolucion:\n");
    for(i = 0; i < n; i++) {
        printf("x%d = %f\n", i+1, x[i]);
    }
    
    return 0;
}