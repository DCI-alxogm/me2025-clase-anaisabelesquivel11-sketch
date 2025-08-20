//Ana Isabel Esquivel Castro
//436578
//Semana 3, Tarea 1
//Realizar un código para la serie de Mclaurin

#include <stdio.h>
#include <math.h>

int main() {
double x, termino, suma = 0.0;
int iteracion = 0, n;
double error_objetivo = 0.1; // 0.1% de error

    
printf("Por favor, ingrese el valor de x con dos decimales: ");
scanf("%lf", &x);
// Calcular el valor real de e^x
double valor_real = exp(x);

printf("\nIteracion\tTermino\t\tSuma Parcial\tError\n");

// Ciclo principal para la serie de Maclaurin
 
 do {
double factorial = 1.0;
double potencia = 1.0;
        
  
if(iteracion > 0) { //Ciclo for para calcular factoriales
for(int i = 1; i <= iteracion; i++) {
factorial *= i;
}

}  
for(int i = 1; i <= iteracion; i++) { //Ciclo for para calcular xexpn
potencia *= x;
}

 if(iteracion == 0) { //calcular termino actual de la serie y guardarlo
termino = 1.0; // El primer término es 1
} else {
termino = potencia / factorial;
}

suma += termino; //sumanos el término actial al resultado anterior y así sucesivamente

double error = fabs((valor_real - suma) / valor_real) * 100; //error relativo
        
printf("%d\t\t%.3f\t%.3f\t%.3f%%\n", 
iteracion, termino, suma, error);
        
if(error < error_objetivo) { //Condiciones e iterar 20 veces máx
printf("Se alcanzó la condición de error < 0.1%%\n");
break;
} else if(iteracion >= 20) {
printf("Con el número de iteraciones establecidas (20) no se ha podido llegar al valor\n");
break;
}
iteracion++;

} while(1); // Ciclo infinito controlado por break

printf("Error relativo final: %.3f%%\n", fabs((valor_real - suma) / valor_real) * 100);
return 0;
}