//Ana Isabel Esquivel Castro
//436578
//MN
//Hacer casi el mismo código del método del gradiente hecho en clase pero con
//diferencias finitas para las derivadas
//Esta actividad es TAREAAA

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double funcion(double x, double y) { //se mete la función a trabajar
    return y - x - 2*x*x - 2*x*y - y*y;
}

double derivada_x(double x, double y) { //derivada parcial respecto a x 
    double h = 0.0001; 
    return (funcion(x + h, y) - funcion(x - h, y)) / (2 * h);
}

// Derivada parcial con respecto a y usando diferencias finitas
double derivada_y(double x, double y) {//derivada parcial respecto a y
    double h = 0.0001;
    return (funcion(x, y + h) - funcion(x, y - h)) / (2 * h);
}

int main() {
    double x, y, alpha;
    int iteraciones;
    double x_min, x_max, y_min, y_max;
    char tipo_busqueda;
    
    
  
    printf("          f(x,y) = y - x - 2x² - 2xy - y²\n");
    printf("¿Qué buscarás? (M: Maximo, m: Minimo): "); //yo como usuario ya debo saber si la funcion que busco da para máximo o mínimo al graficarla
    scanf(" %c", &tipo_busqueda);
  
    printf("\nRangos para  X,Y:\n");//metemos los rangos que nos dieron en clase
    printf("Rango minimo para x: ");
    scanf("%lf", &x_min);
    printf("Rango maximo para x: ");
    scanf("%lf", &x_max);
    printf("Rango minimo para y: ");
    scanf("%lf", &y_min);
    printf("Rango maximo para y: ");
    scanf("%lf", &y_max);
    printf("\nPunto inicial (dentro de los rangos):\n");
    printf("Coordenada x inicial: "); //estos son los datos que deben estar dentro del rango :))))
    scanf("%lf", &x);
    printf("Coordenada y inicial: ");
    scanf("%lf", &y);
    

    if(x < x_min || x > x_max || y < y_min || y > y_max) { //revisamos que el punto incial esté dentro del rango que ya establecimos 
        printf("\n¡ERROR! El punto inicial está fuera del rango.\n");
        printf("x debe estar entre [%.2f, %.2f]\n", x_min, x_max);
        printf("y debe estar entre [%.2f, %.2f]\n", y_min, y_max);
        return 1;
    }
    
    printf("Tasa de aprendizaje (alpha, ej: 0.1): ");
    scanf("%lf", &alpha);
    printf("Numero de iteraciones (ej: 50): ");
    scanf("%d", &iteraciones);
   
    printf("Buscar %s\n", (tipo_busqueda == 'M' || tipo_busqueda == 'm') ? 
           (tipo_busqueda == 'M' ? "MAXIMO" : "MINIMO") : "MAXIMO");
    printf("Rangos: x ∈ [%.2f, %.2f], y ∈ [%.2f, %.2f]\n", x_min, x_max, y_min, y_max);
    printf("Punto inicial: (%.2f, %.2f)\n", x, y);
    printf("Alpha: %.2f, Iteraciones: %d\n\n", alpha, iteraciones);
    
    printf("Iter\t   x\t\t   y\t\t  f(x,y)\n");
    double mejor_x = x, mejor_y = y;
    double mejor_valor = funcion(x, y);
    
    for(int i = 0; i < iteraciones; i++) {
        double dx = derivada_x(x, y); //calculamos derivadas
        double dy = derivada_y(x, y);
        double valor_actual = funcion(x, y);
        if(tipo_busqueda == 'M') { //modificar el valor si buscamos máximo o mínimo
            if(valor_actual > mejor_valor) { //para máximo
                mejor_valor = valor_actual;
                mejor_x = x;
                mejor_y = y;
            }
        } else {
            if(valor_actual < mejor_valor) { //para el mínimo
                mejor_valor = valor_actual;
                mejor_x = x;
                mejor_y = y;
            }
        }
        
        double x_nuevo, y_nuevo; //nuevo punto
        
       
        if(tipo_busqueda == 'M') { 
            x_nuevo = x + alpha * dx; //para máximo se mueve en dirección de gradiente
            y_nuevo = y + alpha * dy;
        } else {
            x_nuevo = x - alpha * dx;//para mínimo en dirección contraria
            y_nuevo = y - alpha * dy;
        }
        
        if(x_nuevo < x_min) x_nuevo = x_min; //revisar que el nuevo punto esté dentro del rango
        if(x_nuevo > x_max) x_nuevo = x_max;
        if(y_nuevo < y_min) y_nuevo = y_min;
        if(y_nuevo > y_max) y_nuevo = y_max;
        x = x_nuevo;
        y = y_nuevo;
    }
    
    printf("\nResultados\n");
    printf("%s encontrado en: (%.4f, %.4f)\n", 
           (tipo_busqueda == 'M') ? "MAXIMO" : "MINIMO", mejor_x, mejor_y);
    printf("Valor de la función: %.4f\n", mejor_valor);
    
    return 0;
}
