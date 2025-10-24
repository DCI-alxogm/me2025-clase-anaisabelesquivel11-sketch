//Gauss Siedel
//Ana Isabel Esquivel Castro 
//436578
// Métodos Numéricos
//Tarea (Realizar el código de Gauss Siedel)
//Usé las bases de los códigos anteriores para este método
//por eso lucen tan similares, pero en los ciclos es donde ya 
//cambia el código :D!


#include <stdio.h> //Definimos las librerías a emplear
#include <stdlib.h>
#include <math.h>

#define MAX_DIM 10 //definimos la dimesión de la matriz y  
#define MAX_ITER 100 //el núemro máximo de iteaciones 
#define TOL 1e-6 //la tolerancia 

int main() {
    int n, i, j, iter;
    double A[MAX_DIM][MAX_DIM], b[MAX_DIM];
    double x[MAX_DIM] = {0};  // aquí obtenemos la solución inicial empezando con ceros  
    printf("Método Gauss Siedel\n"); //se pide al usuario que meta la dimensión de la matriz
    printf("Dimension del sistema (ej. 3 para 3x3): ");
    scanf("%d", &n);//ingresa el dato
    
    
    printf("\nIngresa valores para la matriz A (%dx%d):\n", n, n); //pedimos la matriz A
    for(i = 0; i < n; i++) {
        printf("Fila %d: ", i+1);
        for(j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
    
    
    printf("\nIngresa valores para  el vector b: "); //pedimos el vector b
    for(i = 0; i < n; i++) {
        scanf("%lf", &b[i]);
    }
    
    printf("\nSistema de ecuaciones:\n"); //aquí se muestra el sistema de la matriz original
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%8.3f ", A[i][j]);
        }
        printf("| %8.3f\n", b[i]);
    }
    
    
    int es_diagonal_dominante = 1; //veridicamos que la  convergencia matriz diagonalmente dominante
    for(i = 0; i < n; i++) {
        double suma_fila = 0.0;
        for(j = 0; j < n; j++) {
            if(j != i) {
                suma_fila += fabs(A[i][j]);
            }
        }
        if(fabs(A[i][i]) <= suma_fila) {
            es_diagonal_dominante = 0;
            break;
        }
    }
    
    if(es_diagonal_dominante) {
        printf("\nLa matriz es diagonalmente dominante - convergencia garantizada\n");
    } else {
        printf("\n La matriz no es diagonalmente dominante\n");
        printf("La convergencia no se garantiza\n");
    }
    
    
    printf("\nIteraciones de Gauss Seidel:\n"); //aplicamos Gauss Siedel
    printf("Iter |");
    for(i = 0; i < n; i++) printf("   x%d     |", i+1);
    printf("   Error\n");
    
    for(iter = 0; iter < MAX_ITER; iter++) {
        
      for(i = 0; i < n; i++) { //a partir de los datos anteriores se calcula el error
            x_old[i] = x[i];
        }
        
      
        for(i = 0; i < n; i++) { //actualizamos los valores de las variables :)
            sum = 0.0;
            for(j = 0; j < n; j++) {
                if(j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            
            x[i] = (b[i] - sum) / A[i][i]; //ya en este punto se puede obtener el valor nuevo de x[i] 
        }
        
        error = 0.0;
        for(i = 0; i < n; i++) {
            double diff = fabs(x[i] - x_old[i]);
            if(diff > error) {
                error = diff; //error obtenido
            }
        }
        
       
        if(iter < 10 || iter % 5 == 0 || error < TOL) {
            printf("%4d |", iter+1); //mostramos el avance cada que pasan 5 iteraciones o en las primeras 10
            for(i = 0; i < n; i++) {
                printf(" %9.6f |", x[i]);
            }
            printf(" %e\n", error);
        }
        
    
        if(error < TOL) { //se busca si la matriz si puede converger
            printf("\n la convergencia fue alcanzada en %d iteraciones!!!\n", iter+1);
            break;
        }
    }
    
    if(iter == MAX_ITER) { //RESULTADOS :)
        printf("\n No convergio después de %d iteraciones\n", MAX_ITER);
        printf("El error final es: %e\n", error);
    }
    
    printf("\n solución\n");
    for(i = 0; i < n; i++) {
        printf("x%d = %f\n", i+1, x[i]);
    }
    
    
    printf("\ verificación\n");
    for(i = 0; i < n; i++) {
        double resultado = 0.0;
        for(j = 0; j < n; j++) {
            resultado += A[i][j] * x[j];
        }
        printf("Ecuacion %d: Calculado = %f, Esperado = %f, Error = %f\n", 
               i+1, resultado, b[i], fabs(resultado - b[i]));
    }
    
    return 0;
}