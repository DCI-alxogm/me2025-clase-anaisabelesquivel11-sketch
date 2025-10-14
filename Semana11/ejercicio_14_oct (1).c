//Ana Isabel Esquivel Castro
//436578
//Eje3rcicio de clase: modificar el código de la sesión pasada para lograr obtener
//una matriz en la que la primera fila no admita 0, la segunda solo en la primera 
//posición, y la tercera, solo en la primera y segunda posición
//todo esto si es que existen 0



#include <stdio.h>

int main() {
    int n = 3, N = 3;
    double A[3][3];
    double B[3];
    double X[3];
    double factor, suma;
    int i, j, k;

    printf("Ingresa los valores de la matriz A (3x3):\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < N; j++) {
            printf("A[%d][%d] = ", i + 1, j + 1);
            scanf("%lf", &A[i][j]);
        }
        if (i == 0) {
            
            if (A[0][0] == 0) {
                printf( "Error: la primera fila no puede tener 0 en la primera posición.\n");
                return 1;
            }
        }

        if (i == 1) {
             //posición de la segunda fila
            if ((A[1][1] == 0) || (A[1][2] == 0 && A[1][1] != 0)) {
                printf("Error: en la segunda fila, el único 0 permitido es en la primera posición.\n");
                return 1;
            }
        }

        if (i == 2) { //posición de la tercera filaaaa
           
                printf("Error: en la tercera fila no se permite 0 en la tercera posición.\n");
                return 1;
            }
        }
    }
    printf("Da los valores del vector B:\n");//Ve
    for (i = 0; i < n; i++) {
        printf("B[%d] = ", i + 1);
        scanf("%lf", &B[i]);
    }
    for (k = 0; k < n - 1; k++) {
        for (i = k + 1; i < n; i++) {
            factor = A[i][k] / A[k][k];
            for (j = k; j < N; j++) {
                A[i][j] = A[i][j] - factor * A[k][j];
            }
            B[i] = B[i] - factor * B[k];
        }
    }
    for (i = n - 1; i >= 0; i--) {
        suma = 0;
        for (j = i + 1; j < N; j++) {
            suma += A[i][j] * X[j];
        }
        X[i] = (B[i] - suma) / A[i][i];
    }

  
    printf("Soluciones del sistema :D!!!:\n");
    for (i = 0; i < n; i++) {
        printf("X%d = %.6f\n", i + 1, X[i]);
    }

    return 0;
}
