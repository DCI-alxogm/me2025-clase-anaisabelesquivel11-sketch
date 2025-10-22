//Ana Isabel Esquivel Castro
//436578
//Métodos Numéricos
//Tarea: Realizar un código para método de Gauss Jordan
//El código debe incluir lo mismo  que el código de Gauss pero con esta extensión de 
//Jordan


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DIM 10
#define TOL 1e-10

int main() {
    int n, i, j, k;
    double A[MAX_DIM][MAX_DIM], b[MAX_DIM], x[MAX_DIM];
    double factor, temp, max_val;
    
    printf("Dimension de la matriz: ");
    scanf("%d", &n);
    
    printf("Matriz A (%dx%d): \n", n, n);
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
    
                             //Aplicamos el  Método de Gauss-Jordan
    for(i = 0; i < n; i++) { //Se realiza el pivoteo parcial igual que en el método de Gauss
        
        int max_row = i;
        for(j = i+1; j < n; j++) {
            if(fabs(A[j][i]) > fabs(A[max_row][i])) max_row = j;
        }
        
        if(max_row != i) {
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
        
                                  
        if(fabs(A[i][i]) > TOL) { //En Gauss-Jordan normalizamos para que el pivote sea 1
            factor = A[i][i];
            for(j = 0; j < n; j++) {
                A[i][j] /= factor;
            }
            b[i] /= factor;
        }
        
       
        // En Gauss-Jordan eliminamos tanto arriba como abajo del pivote
        for(j = 0; j < n; j++) { //aquí se elimina 
            if(j != i) {  // No aplicamos a la fila del pivote
                factor = A[j][i];
                for(k = 0; k < n; k++) {
                    A[j][k] -= factor * A[i][k];
                }
                b[j] -= factor * b[i];
            }
        }
        
        // Mostrar matriz en cada paso (opcional, para ver el proceso)
        printf("\nPaso %d:\n", i+1);
        for(int ii = 0; ii < n; ii++) {
            for(int jj = 0; jj < n; jj++) printf("%8.3f ", A[ii][jj]);
            printf("| %8.3f\n", b[ii]);
        }
    }
    
    
    int bien_condicionado = 1; //reviar que el sistema esté bien condicionado para que  no
    for(i = 0; i < n; i++) { //sea sensible al  número de cifras significativassss
        if(fabs(A[i][i]) < TOL) {
            printf("ADVERTENCIA: Sistema mal condicionado\n");
            bien_condicionado = 0;
            break;
        }
    }
    if(bien_condicionado) printf("Sistema bien condicionado\n");
    
   
    for(i = 0; i < n; i++) { // en este método no se necesita realizar la sustitucón 
        x[i] = b[i]; // a la inversa para poder encontrar los valores de cada variable
    }
    
  
    printf("\nSolucion:\n"); //se muestra la solución de la matriz
    for(i = 0; i < n; i++) {
        printf("x%d = %f\n", i+1, x[i]);
    }
    
    return 0;
}