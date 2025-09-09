//Ana Isabel Esquivel Castr
//436578
//Métodos Numéricos, Tarea Diferenciación por pasos

#include <stdio.h>
#include <math.h>

int main(){

float x[]={0.0,0.5,1.0,1.5}; //valores de x  (se agregó un punto más para poder hacer tercera derivada)
float fx[]={1.2,0.925,0.2,-0.7}; // valores de f(x) (tienes que poner el valor real de f(1.5))
float e=-0.9125; //valor exacto ya establecido
float h=x[1]-x[0]; //espacio de h :D
float a;
float erroradelante;

//Ecuaciones para  tercera diferenciación hacia adelante
a= (fx[3] - 3*fx[2] + 3*fx[1] - fx[0]) / (h*h*h);

erroradelante=(e-a)/e;

printf("estos son los resultados obtenidos para la tercera diferenciacion hacia aedelante\n\n");

printf("Tercera diferenciación hacia adelante:\n");
printf("f'(0.5) ≈ %.2f\n",a); //IMPORTANTE: Usamos el símbolo de aproximación porqeu las diferencias
//finitas no son valor exacto de la derivada, solo son aproximaciones
printf("error relativo: %.2f%%\n\n",erroradelante*100);

return 0;
}
