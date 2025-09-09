//Ana Isabel Esquivel Castro
//436578
//Ejercicio de clase 1, semana 6
//Realizar un código que aplique el método de bisección con el objetivo de encontrar raíces 
//para cualquier función dada. Realizar un for para aznalizar cuándo tenemos cambios de signos.

#include <stdio.h>
#include <math.h>

int main (){
  }
float f(float c) {
  return (9.81*68.1)/c*(1-exp(-(c/68.1)*10))-40;
}

if (f(a) * f(b) > 0) { //Aplicamos un cliclo for para analizar si hay cambio de signo
  printf("No hay cambio de signo en el intervalo, no se puede aplicar biseccion.\n");
return 0;
}

kold = a;

do {
iter++;
k = (a + b) / 2.0; //en esta parte tenemos el método de bisccción

if (f(k) * f(a) < 0)
b = k;
else
a = k;
Eri = fabs((k - kold) / k);//El error se calcula a partir  de la segunda iteración
kold = k;

printf("Iter %d: k = %.6f, Error = %.6f\n", iter, k, Eri);

} while (Eri > Ermax);


return 0;
{}
