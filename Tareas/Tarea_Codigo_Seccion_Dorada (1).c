//Ana Isabel Esquivel Castro 
//436578
//MN
//Tarea C+odigo de la Sección Dorada
//Corregí el código que hicimos de actividad de clase 

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR 200
char funcion_global[MAX_EXPR];//definimos una variable global para guardar la función que ingresemos
int buscar_minimo = 1;//variable para buscar el mínimo
double evaluar_expresion(const char* expresion, double x) {//definimos un double para la función para evaluar una expresión  al tener una cadena y un valor de x
    char copia[MAX_EXPR];
    strcpy(copia, expresion);

    char temp[MAX_EXPR] = ""; //inicializamos una cadena que esté "vacía" :)
    char num[50]; 
    sprintf(num, "%.6f", x); //convertimos el double x a string con 6 decimales 
    
    
    for(int i = 0, j = 0; expresion[i] != '\0'; i++) {  // Recorremos y reemplazamos a x por el string
        if(expresion[i] == 'x') { //
            strcat(temp, num); 
            j += strlen(num); 
        } else {
            temp[j++] = expresion[i]; 
            temp[j] = '\0'; //la cadena debe terminar en nulo
        }
    }   
    FILE *fp; //hacemos la evaluación de la expresión usando system()
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
    
    remove("temp_eval.c");//Limpiamos los archivos 
    remove("temp_eval");
    
    return resultado;
}

double funcion(double x) {//hacemos la fubnción que llama a evaluar expresion pero con la función global
    return evaluar_expresion(funcion_global, x);
}


void encontrar_intervalo(double *a, double *b) {//función para encontrar un intervalo [a, b] que contenga un mínimo o máxim, dependiendo del caso
    double punto_inicial = 0.0; 
    double paso = 1.0; 
    double x1, x2, x3;
    double f1, f2, f3;
    
    x1 = punto_inicial;//evaluamos la función en el punto inicial
    f1 = funcion(x1); 
    x2 = x1 + paso;//probar punto a la derecha
    f2 = funcion(x2);
   
    if ((buscar_minimo && f2 < f1) || (!buscar_minimo && f2 > f1)) {//como vimos en clase, si estamos buscando un mínimo y f2 < f1, o un máximo y f2 > f1, entonces el extremo está a la derecha
        while ((buscar_minimo && f2 < f1) || (!buscar_minimo && f2 > f1)) {
            x1 = x2;
            f1 = f2;
            paso *= 2;//duplicamos para hacer mÁas rápido 
            x2 = x1 + paso;
            f2 = funcion(x2);
        }
        *a = x1 - paso/2; 
        *b = x2;
    } else {
        x2 = x1 - paso;
        f2 = funcion(x2);
        printf("f(%.2f) = %.4f\n", x2, f2);
        
        while ((buscar_minimo && f2 < f1) || (!buscar_minimo && f2 > f1)) {
            x1 = x2;
            f1 = f2;
            paso *= 2;
            x2 = x1 - paso;
            f2 = funcion(x2);
        }
        *a = x2;//definimos el intervalo que contiene el extremo
        *b = x1 + paso/2;
    }
    printf("Intervalo encontrado: [%.2f, %.2f]\n", *a, *b);
}
double seccion_dorada(double a, double b, double tolerancia) { //aplicamos el método 
    double r = (sqrt(5) - 1) / 2;  // Razón dorada ≈ 0.618
    double x1, x2, f1, f2;
    int iter = 0;
    
    printf("\nIter\t   a\t\t  x1\t\t  x2\t\t   b\t\t  f(x1)\t\t  f(x2)\n");
    printf("---------------------------------------------------------------------------\n");
    
   
    while (fabs(b - a) > tolerancia && iter < 100) {//iteramos hasta que el intervalo sea menor que la tolerancia o se alcance el máximo de iteraciones
        x1 = b - r * (b - a); //usamos la razón dorada
        x2 = a + r * (b - a);
        f1 = funcion(x1); //evaluamos la función
        f2 = funcion(x2);
        printf("%3d\t%8.4f\t%8.4f\t%8.4f\t%8.4f\t%10.4f\t%10.4f\n", 
               iter, a, x1, x2, b, f1, f2);
        if (buscar_minimo) {
            if (f1 < f2) { //para mínimo nos quedamos con el intervalo con el valor más pequeño
                b = x2;  
            } else {
                a = x1;
            }
        } else {
            // Para máximo: nos quedamos con el subintervalo que tiene el valor más grande
            if (f1 > f2) {
                b = x2;
            } else {
                a = x1;
            }
        }
        
        iter++;
    }
    return (a + b) / 2;
}

int main() {
    double a, b, tolerancia, resultado;
    char opcion;
    printf("Ingresa una funcion en términos de x:\n");
    printf("\nsigue la sintaxis:\n");
    printf("multiplicacion: use * (ej: 2*x, no 2x)\n");
    printf("potencia: use x*x o pow(x,2)\n");
    printf("funciones: sin(x), cos(x), exp(x), log(x), sqrt(x)\n");
    printf("\nfuncion: f(x) = ");
  
    fgets(funcion_global, MAX_EXPR, stdin);
    funcion_global[strcspn(funcion_global, "\n")] = 0;//eliminamos el salto de línea final
    
    printf("\n¿Qué se busca encontrar? (m: minimo, M: maximo): ");
    scanf(" %c", &opcion);
    buscar_minimo = (opcion == 'm' || opcion == 'M') ? (opcion == 'm') : 1;
    printf("\nTolerancia (ej: 0.001): ");//tolerancia deseada
    scanf("%lf", &tolerancia);
    encontrar_intervalo(&a, &b);
    resultado = seccion_dorada(a, b, tolerancia); //aplicamos el método
  
    printf("\nResultados\n"); //mostrar resultadoss
    printf("%s encontrado en: x = %10.6f\n", 
           buscar_minimo ? "Minimo" : "Maximo", resultado);
    printf("Valor de la funcion: f(x) = %10.6f\n", funcion(resultado));
    printf("Intervalo final: [%10.6f, %10.6f]\n", a, b);
    
    return 0;
}