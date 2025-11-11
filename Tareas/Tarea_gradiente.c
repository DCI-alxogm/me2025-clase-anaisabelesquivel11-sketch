// Ana Isabel Esquivel Castro
// 436578
// MN
// Tarea - Método del Gradiente

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR 200
#define MAX_DIM 10  // Dimensión máxima permitida
#define H 0.0001    // Paso para derivadas numéricas

// Estructura para representar un punto en n dimensiones
typedef struct {
    double coordenadas[MAX_DIM];
    int dimension;
} Punto;

// Variables globales
char funcion_global[MAX_EXPR];
int buscar_minimo = 1;  // 1 para mínimo, 0 para máximo
int dimension_actual = 2; // Dimensión por defecto

// Función para evaluar expresiones matemáticas en n dimensiones
double evaluar_expresion_nd(const char* expresion, Punto punto) {
    char temp[MAX_EXPR] = "";
    char num[50];
    char expresion_temp[MAX_EXPR];
    
    strcpy(expresion_temp, expresion);
    
    // Reemplazar cada variable x0, x1, x2, ... por sus valores
    for(int i = 0; i < punto.dimension; i++) {
        char variable[10];
        sprintf(variable, "x%d", i);  // Crear "x0", "x1", etc.
        sprintf(num, "%.6f", punto.coordenadas[i]);  // Valor de la coordenada
        
        char temp2[MAX_EXPR] = "";
        for(int j = 0, k = 0; expresion_temp[j] != '\0'; j++) {
            // Verificar si encontramos la variable actual
            int coincide = 1;
            for(int m = 0; variable[m] != '\0'; m++) {
                if(expresion_temp[j + m] != variable[m]) {
                    coincide = 0;
                    break;
                }
            }
            
            if(coincide) {
                strcat(temp2, num);
                k += strlen(num);
                j += strlen(variable) - 1;  // Saltar la variable
            } else {
                temp2[k++] = expresion_temp[j];
                temp2[k] = '\0';
            }
        }
        strcpy(expresion_temp, temp2);
    }
    
    // Evaluar la expresión resultante
    FILE *fp;
    double resultado;
    
    fp = fopen("temp_eval.c", "w");
    fprintf(fp, "#include <stdio.h>\n#include <math.h>\nint main() { double x = %s; printf(\"%%f\", x); return 0; }", expresion_temp);
    fclose(fp);
    
    system("gcc -o temp_eval temp_eval.c -lm 2>/dev/null");
    fp = popen("./temp_eval", "r");
    if (fp == NULL) {
        printf("Error al evaluar la expresión\n");
        return 0;
    }
    fscanf(fp, "%lf", &resultado);
    pclose(fp);
    
    remove("temp_eval.c");
    remove("temp_eval");
    
    return resultado;
}

// Función wrapper para evaluar la función en n dimensiones
double funcion_nd(Punto punto) {
    return evaluar_expresion_nd(funcion_global, punto);
}

// Calcular el gradiente (vector de derivadas parciales)
void calcular_gradiente(Punto punto, Punto *gradiente) {
    gradiente->dimension = punto.dimension;
    
    for(int i = 0; i < punto.dimension; i++) {
        Punto punto_plus = punto;
        Punto punto_minus = punto;
        
        punto_plus.coordenadas[i] += H;
        punto_minus.coordenadas[i] -= H;
        
        double f_plus = funcion_nd(punto_plus);
        double f_minus = funcion_nd(punto_minus);
        
        gradiente->coordenadas[i] = (f_plus - f_minus) / (2 * H);
    }
}

// Calcular la norma (magnitud) de un vector
double norma(Punto vector) {
    double suma_cuadrados = 0.0;
    for(int i = 0; i < vector.dimension; i++) {
        suma_cuadrados += vector.coordenadas[i] * vector.coordenadas[i];
    }
    return sqrt(suma_cuadrados);
}

// Multiplicar un vector por un escalar
Punto multiplicar_por_escalar(Punto vector, double escalar) {
    Punto resultado;
    resultado.dimension = vector.dimension;
    for(int i = 0; i < vector.dimension; i++) {
        resultado.coordenadas[i] = vector.coordenadas[i] * escalar;
    }
    return resultado;
}

// Sumar dos vectores
Punto sumar_vectores(Punto a, Punto b) {
    Punto resultado;
    resultado.dimension = a.dimension;
    for(int i = 0; i < a.dimension; i++) {
        resultado.coordenadas[i] = a.coordenadas[i] + b.coordenadas[i];
    }
    return resultado;
}

// Método del gradiente para optimización en n dimensiones
Punto metodo_gradiente(Punto punto_inicial, double tasa_aprendizaje, double tolerancia, int max_iter) {
    Punto punto_actual = punto_inicial;
    Punto gradiente;
    double magnitud_gradiente;
    int iter = 0;
    
    printf("\nIter\t");
    for(int i = 0; i < punto_actual.dimension; i++) {
        printf("    x%d\t\t", i);
    }
    printf("  f(x)\t\t  ||∇f||\n");
    
    // Línea separadora
    printf("----------------------------------------------------------------------------------------\n");
    
    do {
        iter++;
        
        // Calcular gradiente en el punto actual
        calcular_gradiente(punto_actual, &gradiente);
        magnitud_gradiente = norma(gradiente);
        
        // Mostrar información de la iteración
        printf("%3d\t", iter);
        for(int i = 0; i < punto_actual.dimension; i++) {
            printf("%8.6f\t", punto_actual.coordenadas[i]);
        }
        printf("%8.6f\t%8.6f\n", funcion_nd(punto_actual), magnitud_gradiente);
        
        // Actualizar posición: x_new = x_old - alpha * gradiente (para mínimo)
        // Para máximo: x_new = x_old + alpha * gradiente
        Punto direccion = multiplicar_por_escalar(gradiente, tasa_aprendizaje);
        
        if(buscar_minimo) {
            // Para mínimo: movernos en dirección opuesta al gradiente
            for(int i = 0; i < punto_actual.dimension; i++) {
                punto_actual.coordenadas[i] -= direccion.coordenadas[i];
            }
        } else {
            // Para máximo: movernos en la misma dirección del gradiente
            for(int i = 0; i < punto_actual.dimension; i++) {
                punto_actual.coordenadas[i] += direccion.coordenadas[i];
            }
        }
        
    } while(magnitud_gradiente > tolerancia && iter < max_iter);
    
    printf("\nConvergencia alcanzada después de %d iteraciones\n", iter);
    printf("Magnitud final del gradiente: %f\n", magnitud_gradiente);
    
    return punto_actual;
}

// Función para mostrar un punto
void mostrar_punto(Punto punto, const char* nombre) {
    printf("%s = (", nombre);
    for(int i = 0; i < punto.dimension; i++) {
        printf("%.6f", punto.coordenadas[i]);
        if(i < punto.dimension - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main() {
    Punto punto_inicial, resultado;
    double tasa_aprendizaje, tolerancia;
    char opcion;
    int max_iter;
    
    printf("================================================================================\n");
    printf("                      METODO DEL GRADIENTE MULTIDIMENSIONAL\n");
    printf("================================================================================\n\n");
    
    // Solicitar dimensión del problema
    printf("Ingrese la dimensión del problema (1-%d): ", MAX_DIM);
    scanf("%d", &dimension_actual);
    
    if(dimension_actual < 1 || dimension_actual > MAX_DIM) {
        printf("Error: Dimensión debe estar entre 1 y %d\n", MAX_DIM);
        return 1;
    }
    
    // Configurar dimensiones
    punto_inicial.dimension = dimension_actual;
    
    // Solicitar función al usuario
    printf("\nIngresa una función en términos de x0, x1, x2, ...:\n");
    printf("Sintaxis:\n");
    printf("  Multiplicacion: use * (ej: 2*x0, x0*x1)\n");
    printf("  Potencia: use x0*x0 o pow(x0,2)\n");
    printf("  Funciones: sin(x0), cos(x0), exp(x0), log(x0), sqrt(x0)\n");
    printf("  Ejemplos:\n");
    printf("    - 2D: x0*x0 + x1*x1\n");
    printf("    - 3D: x0*x0 + x1*x1 + x2*x2\n");
    printf("    - Rosenbrock 2D: (1-x0)*(1-x0) + 100*(x1-x0*x0)*(x1-x0*x0)\n");
    printf("\nFuncion: f(x) = ");
    
    getchar(); // Limpiar buffer
    fgets(funcion_global, MAX_EXPR, stdin);
    funcion_global[strcspn(funcion_global, "\n")] = 0;
    
    // Preguntar si busca mínimo o máximo
    printf("\n¿Qué deseas encontrar? (m: minimo, M: maximo): ");
    scanf(" %c", &opcion);
    buscar_minimo = (opcion == 'm' || opcion == 'M') ? (opcion == 'm') : 1;
    
    // Solicitar punto inicial
    printf("\nIngrese el punto inicial:\n");
    for(int i = 0; i < dimension_actual; i++) {
        printf("x%d = ", i);
        scanf("%lf", &punto_inicial.coordenadas[i]);
    }
    
    // Solicitar parámetros del método
    printf("\nIngrese la tasa de aprendizaje (alpha, ej: 0.01): ");
    scanf("%lf", &tasa_aprendizaje);
    
    printf("Ingrese la tolerancia (ej: 0.0001): ");
    scanf("%lf", &tolerancia);
    
    printf("Ingrese el número máximo de iteraciones: ");
    scanf("%d", &max_iter);
    
    // Aplicar método del gradiente
    printf("\nEjecutando método del gradiente...\n");
    resultado = metodo_gradiente(punto_inicial, tasa_aprendizaje, tolerancia, max_iter);
    
    // Mostrar resultados finales
    printf("\n================================================================================\n");
    printf("                          RESULTADOS FINALES\n");
    printf("================================================================================\n");
    
    printf("%s encontrado en:\n", buscar_minimo ? "Minimo" : "Maximo");
    mostrar_punto(resultado, "x*");
    
    printf("Valor de la funcion: f(x*) = %10.6f\n", funcion_nd(resultado));
    printf("Tasa de aprendizaje utilizada: %f\n", tasa_aprendizaje);
    printf("Tolerancia utilizada: %f\n", tolerancia);
    
    // Mostrar gradiente en el punto final (debería ser cercano a cero)
    Punto gradiente_final;
    calcular_gradiente(resultado, &gradiente_final);
    printf("Gradiente en el punto final: ");
    mostrar_punto(gradiente_final, "∇f(x*)");
    
    return 0;
}