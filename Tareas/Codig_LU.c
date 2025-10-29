//Ana Isabel Esquivel Castro
//436578
//Métodos Numéricos 
//Realizar un código para factorización LU para la matriz mostrada en clase.
//Incluye solución de sistemas y cálculo de matriz inversa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DIM 10 //definimos la tolerancia y la dimensión maáxima
#define TOL 1e-10

void imprimirLinea(int longitud, char caracter) {
    for(int i = 0; i < longitud; i++) {
        printf("%c", caracter);
    }
    printf("\n");
}

int main() {
    int n, i, j, k, m;
    double A[MAX_DIM][MAX_DIM], L[MAX_DIM][MAX_DIM], U[MAX_DIM][MAX_DIM];
    double b[MAX_DIM], y[MAX_DIM], x[MAX_DIM];
    double invA[MAX_DIM][MAX_DIM];
    int opcion;
    

    
    printf("Dimensiónn de la matriz (maximo %d): ", MAX_DIM);
    scanf("%d", &n);
    
    if(n > MAX_DIM || n < 1) {
        printf("La dimensión qie ingresaste no es valida.\n");
        return 1;
    }
    
    printf("Ingresa la matriz A (%dx%d):\n", n, n);
    for(i = 0; i < n; i++) {
        printf("Fila %d (separa cada uno de los valores con espacio): ", i+1);
        for(j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
    
    printf("Seleccione una opcion:\n"); //mostramos un menú para ver si es necesario que el programa realice todas las operaciones 
    printf("1. Resolver sistema A*x = b\n");
    printf("2. Calcular matriz inversa A^-1\n");
    printf("3. Ambas opciones\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    
    if(opcion == 1 || opcion == 3) {
        printf("\nVector b (terminos independientes): ");
        for(i = 0; i < n; i++) {
            scanf("%lf", &b[i]);
        }
    }
    
    for(i = 0; i < n; i++) {   ///se inicializan U y L :D
        for(j = 0; j < n; j++) {
            if(i == j)
                L[i][j] = 1.0;
            else
                L[i][j] = 0.0;
            U[i][j] = 0.0;
            invA[i][j] = 0.0;
        }
    }
    
    for(i = 0; i < n; i++) {   //se hace la facotrización LU empleando el método de Doolittle
      
        for(j = i; j < n; j++) { //se calcula la fila i de U
            U[i][j] = A[i][j];
            for(k = 0; k < i; k++) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
        
        
        for(j = i + 1; j < n; j++) { //Se calcula la columna i de L
            L[j][i] = A[j][i];
            for(k = 0; k < i; k++) {
                L[j][i] -= L[j][k] * U[k][i];
            }
            if(fabs(U[i][i]) > TOL) {
                L[j][i] /= U[i][i];
            } else {
                printf("Error al tener una división por cero en la factorizacion LU.\n");
                return 1;
            }
        }
    }
    
    
    printf("\n"); //mostramos las matrices L y U obtenidas
    printf("Resultado de factorización LU\n");
    
    printf("\nMatriz L\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%10.6f ", L[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMatriz U\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%10.6f ", U[i][j]);
        }
        printf("\n");
    }
    
    
    if(opcion == 1 || opcion == 3) { //Ya podemos resolver el sistema si es que se pidió
        
        for(i = 0; i < n; i++) { //resolvemos Ly=b
            y[i] = b[i];
            for(j = 0; j < i; j++) {
                y[i] -= L[i][j] * y[j];
            }
            y[i] /= L[i][i];
        }
        
        
        for(i = n-1; i >= 0; i--) {  //resolvemos Ux=y
            x[i] = y[i];
            for(j = i+1; j < n; j++) {
                x[i] -= U[i][j] * x[j];
            }
            x[i] /= U[i][i];
        }
        
        printf("\n");
        printf("La solución del sistema A*x = b es\n");
        printf("\nVector solucion x:\n");
        for(i = 0; i < n; i++) {
            printf("x%d = %12.8f\n", i+1, x[i]);
        }
    }
    
  
    if(opcion == 2 || opcion == 3) { //definimos la matriz inversaA^-1 resolviendo A*X = I
        for(m = 0; m < n; m++) { // sabiendo que el vector b es la columna m de la matriz identidad
            for(i = 0; i < n; i++) {
                b[i] = (i == m) ? 1.0 : 0.0;
            }
            
           
            for(i = 0; i < n; i++) {
                y[i] = b[i];//tenemo Ly=b
                for(j = 0; j < i; j++) {
                    y[i] -= L[i][j] * y[j];
                }
                y[i] /= L[i][i];
            }
            
            for(i = n-1; i >= 0; i--) {
                x[i] = y[i];//tenemos Ux =y
                for(j = i+1; j < n; j++) {
                    x[i] -= U[i][j] * x[j];
                }
                x[i] /= U[i][i];
            }
    
            for(i = 0; i < n; i++) {
                invA[i][m] = x[i];
            }
        }
        
        printf("\n");
        
        printf("La matriz inversa A^-1\n");
        printf("\nLa matriz inversa completa es\n");
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                printf("%12.8f ", invA[i][j]); //este valor me lo sugirieron
            }
            printf("\n");
        }
        
        printf("\nColumnas de la matriz inversa:\n");
        for(m = 0; m < n; m++) {
            printf("\nColumna %d (solucion de A*x = ", m+1);
            printf("(");
            for(i = 0; i < n; i++) {
                printf("%d", (i == m) ? 1 : 0);
                if(i < n-1) printf(",");
            }
            printf(")):\n");
            
            for(i = 0; i < n; i++) {
                printf("  d%d%d = %12.8f\n", i+1, m+1, invA[i][m]);
            }
        }
    }
    
    
    
    return 0;
}