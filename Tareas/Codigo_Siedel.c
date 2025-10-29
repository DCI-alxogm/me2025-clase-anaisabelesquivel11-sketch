//Ana Isabel Esquivel   Castro
//436578
//Métodos Numéricos
//Tarea : Código de Gauss Siedel

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_DIM 10 //drfinimos las variables para  la tolerancia, el número máximo de interaciones y la dimensión de la matriz
#define MAX_ITER 100
#define TOL 1e-6

double calcularDeterminante(double A[MAX_DIM][MAX_DIM], int n) { //calculamos el determinante
    double det = 1.0;
    double temp[MAX_DIM][MAX_DIM];
    int i, j, k;
    
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            temp[i][j] = A[i][j];
        }
    }  
    for(i = 0; i < n; i++) {
        if(fabs(temp[i][i]) < 1e-12) return 0;
        det *= temp[i][i];
        for(k = i + 1; k < n; k++) {
            double factor = temp[k][i] / temp[i][i];
            for(j = i; j < n; j++) {
                temp[k][j] -= factor * temp[i][j];
            }
        }
    }
    return det;
}

void aplicarPivoteo(double A[MAX_DIM][MAX_DIM], double b[MAX_DIM], int n) {
    int i, j, k;
    for(i = 0; i < n; i++) {
        int max_row = i;
        for(k = i + 1; k < n; k++) {
            if(fabs(A[k][i]) > fabs(A[max_row][i])) max_row = k;
        }
        if(max_row != i) {
            for(j = 0; j < n; j++) {
                double temp = A[i][j];
                A[i][j] = A[max_row][j];
                A[max_row][j] = temp;
            }
            double temp_b = b[i];
            b[i] = b[max_row];
            b[max_row] = temp_b;
        }
    }
}

int main() {
    int n, i, j, iter;
    double A[MAX_DIM][MAX_DIM], b[MAX_DIM];
    double x[MAX_DIM] = {0};
    double x_old[MAX_DIM];
    double sum, error;
  
    printf("Dimensión del sistema: "); //ingresamos los valores conocidos de la matriz original
    scanf("%d", &n);
    
    printf("\nMatriz A (%dx%d):\n", n, n);
    for(i = 0; i < n; i++) {
        printf("Fila %d: ", i+1);
        for(j = 0; j < n; j++) scanf("%lf", &A[i][j]);
    }
    
    printf("\nVector b: "); //ingresamos los datos del vector b
    for(i = 0; i < n; i++) scanf("%lf", &b[i]);
    
 
    double det = calcularDeterminante(A, n); //calculamos el determinante
    printf("\nDeterminante: %f\n", det);
    if(fabs(det) < 1e-12) {
        printf("El sistema no puede tener una sola solcu\n");
    }
    
  
    aplicarPivoteo(A, b, n); //aplicamos el pivoteo :)))
  
    printf("\nIteraciones:\n"); //Aplicamos Siedel
    for(iter = 0; iter < MAX_ITER; iter++) {
        for(i = 0; i < n; i++) x_old[i] = x[i];
        
        for(i = 0; i < n; i++) {
            sum = 0.0;
            for(j = 0; j < n; j++) {
                if(j != i) sum += A[i][j] * x[j];
            }
            x[i] = (b[i] - sum) / A[i][i];
        }
        
        error = 0.0;
        for(i = 0; i < n; i++) {
            double diff = fabs(x[i] - x_old[i]);
            if(diff > error) error = diff;
        }
        
        if(error < TOL) break; //se rompe el ciclo
    } 
    
    printf("\nSolucion:\n");
    for(i = 0; i < n; i++) printf("x%d = %f\n", i+1, x[i]);
    
    printf("\nVerificacion:\n");
    for(i = 0; i < n; i++) {
        double resultado = 0.0; //mostramos los resultados
        for(j = 0; j < n; j++) resultado += A[i][j] * x[j];
        printf("Ecuacion %d: %f vs %f\n", i+1, resultado, b[i]);
    }
    
    return 0;
}