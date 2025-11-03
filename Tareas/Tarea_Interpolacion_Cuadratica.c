//Ana Isabel Esquivel Castro
//436578
//MN
//Tarea de Método  de Interpolación Cuadrática
// Inclusión de bibliotecas necesarias
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR 200
char funcion_global[MAX_EXPR]; 
int buscar_minimo = 1;//definimos 1 para mínimo, 0 para máximo


double evaluar_expresion(const char* expresion, double x) {
    char temp[MAX_EXPR] = "";
    char num[50];
    sprintf(num, "%.6f", x);//convertimos el valor de x a un srting
    for(int i = 0, j = 0; expresion[i] != '\0'; i++) {//reemplazamos todas las 'x' 
        if(expresion[i] == 'x') {
            strcat(temp, num);
            j += strlen(num);
        } else {
            temp[j++] = expresion[i];
            temp[j] = '\0';
        }
    }
    FILE *fp; //se crea un archivo para la evaluación
    double resultado;
    
    fp = fopen("temp_eval.c", "w");
    fprintf(fp, "#include <stdio.h>\n#include <math.h>\nint main() { double x = %s; printf(\"%%f\", x); return 0; }", temp);
    fclose(fp);
    system("gcc -o temp_eval temp_eval.c -lm 2>/dev/null");
    fp = popen("./temp_eval", "r");
    if (fp == NULL) {
        printf("Error al evaluar la expresión\n");
        return 0;
    }
    fscanf(fp, "%lf", &resultado);
    pclose(fp);
    remove("temp_eval.c"); //limpiamos  la basura
    remove("temp_eval");
    
    return resultado;
}

double funcion(double x) {//evalúa la funcón global
    return evaluar_expresion(funcion_global, x);
}


void intercambiar(double *a, double *b) {//función para evaluar la función que es global
    double temp = *a; 
    *a = *b;
    *b = temp;
}
double interpolacion_cuadratica(double x0, double x1, double x2, double tolerancia, int max_iter) {//definimos el método de la interpolación cuadrática
    double fx0, fx1, fx2, x3, fx3;
    double error = tolerancia + 1;
    int iter = 0;

    fx0 = funcion(x0); //evaluamos las funciones en los puntos iniciales
    fx1 = funcion(x1);
    fx2 = funcion(x2);
    
    printf("\nIter\t   x0\t\t  x1\t\t  x2\t\t  x3\t\t  f(x3)\t\t  Error\n");
    while (error > tolerancia && iter < max_iter) {
        iter++;
        double numerador = pow(x1 - x0, 2) * (fx1 - fx2) - pow(x1 - x2, 2) * (fx1 - fx0); //interpolación cuadrática para encontrar el vértice
        double denominador = (x1 - x0) * (fx1 - fx2) - (x1 - x2) * (fx1 - fx0);
  
        if (fabs(denominador) < 1e-10) { //revisaer que el denominaador no sea igual a cero
            printf("Error: Denominador cercano a cero en iteración %d\n", iter);
            break;
        }
        x3 = x1 - 0.5 * (numerador / denominador); //calculamos un nuevo punto
        fx3 = funcion(x3);

        error = fabs(x3 - x1); //error
      
        if (buscar_minimo) {// Actualizar puntos según si buscamos mínimo o máximo, para mínimo mantener puntos alrededor del valor más pequeño
            if (fx3 < fx1) {
                if (x3 < x1) {
                    x2 = x1; fx2 = fx1;
                    x1 = x3; fx1 = fx3;
                } else {
                    x0 = x1; fx0 = fx1;
                    x1 = x3; fx1 = fx3;
                }
            } else {
                if (x3 < x1) {
                    x0 = x3; fx0 = fx3;
                } else {
                    x2 = x3; fx2 = fx3;
                }
            }
        } else {
            if (fx3 > fx1) { //para máximo mantenemos los puntos alrededor del valor más grande
                if (x3 < x1) {
                    x2 = x1; fx2 = fx1;
                    x1 = x3; fx1 = fx3;
                } else {
                    x0 = x1; fx0 = fx1;
                    x1 = x3; fx1 = fx3;
                }
            } else {
                if (x3 < x1) {
                    x0 = x3; fx0 = fx3;
                } else {
                    x2 = x3; fx2 = fx3;
                }
            }
        }
        
        if (x0 > x1) { intercambiar(&x0, &x1); intercambiar(&fx0, &fx1); }//ordenamos
        if (x1 > x2) { intercambiar(&x1, &x2); intercambiar(&fx1, &fx2); }
        if (x0 > x1) { intercambiar(&x0, &x1); intercambiar(&fx0, &fx1); }
    }
    double mejor_x = x0; //se busca el mejor punto de los tres
    double mejor_fx = fx0;
    
    if (buscar_minimo) {
        if (fx1 < mejor_fx) { mejor_x = x1; mejor_fx = fx1; }
        if (fx2 < mejor_fx) { mejor_x = x2; mejor_fx = fx2; }
    } else {
        if (fx1 > mejor_fx) { mejor_x = x1; mejor_fx = fx1; }
        if (fx2 > mejor_fx) { mejor_x = x2; mejor_fx = fx2; }
    }
    
    return mejor_x;
}

int main() {
    double x0, x1, x2, tolerancia, resultado;
    char opcion;
    int max_iter;

    printf("Ingresa una funcion en términos de x:\n"); //pedir datos al usuario
    printf("Sintaxis:\n"); //recordamos la sintaxis
    printf("  Multiplicacion: use * (ej: 2*x)\n");
    printf("  Potencia: use x*x o pow(x,2)\n");
    printf("  Funciones: sin(x), cos(x), exp(x), log(x), sqrt(x)\n");
    printf("Funcion: f(x) = ");
    
    fgets(funcion_global, MAX_EXPR, stdin);
    funcion_global[strcspn(funcion_global, "\n")] = 0;
    printf("¿Qué se busca encontrar? (m: minimo, M: maximo): ");
    scanf(" %c", &opcion);
    buscar_minimo = (opcion == 'm' || opcion == 'M') ? (opcion == 'm') : 1;
    
    printf("Puntos iniciales (x0, x1, x2):\n"); //solicitamos los puntos iniciales
    printf("x0 = ");
    scanf("%lf", &x0);
    printf("x1 = ");
    scanf("%lf", &x1);
    printf("x2 = ");
    scanf("%lf", &x2);
    

    printf("ITolerancia (ej: 0.0001): ");//ingresamos la tolerancia
    scanf("%lf", &tolerancia);
    printf("Número máximo de iteraciones: ");
    scanf("%d", &max_iter);

    resultado = interpolacion_cuadratica(x0, x1, x2, tolerancia, max_iter); //aplicamos el método 
    printf("%s encontrado en: x = %10.6f\n",  //mostramos los resultados finales
           buscar_minimo ? "Minimo" : "Maximo", resultado);
    printf("Valor de la funcion: f(x) = %10.6f\n", funcion(resultado));
    printf("Tolerancia utilizada: %f\n", tolerancia);
    
    return 0;
}