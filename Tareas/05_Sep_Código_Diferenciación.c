
//Ana Isabel Esquivel Castr
//436578
//Métodos Numéricos, Tarea Diferenciación por pasos

#include <stdio.h>
#include <math.h>
{
int main(){

float x[]={0.0,0.5,1.0}; //valores de x
float fx[]={1.2,0.925,0.2}; // valores de f(x)
float e=-0.9125; //valor exacto ya establecido
float h=x[2]-x[1];} //espacio de h :D
float adelante,atras,centrada;
float erroradelante,erroratras,errorcentrada;

a=(fx[2]-fx[1])/h;  //Ecuaciones para diferenciaciones
b=(fx[1]-fx[0])/h;
c=(fx[2]-fx[0])/(2*h);

erroradelante=(e-a)/e;
errorcentrada=(e-c)/e;
erroratras=(e-b)/e;

printf("estos son los resultados obtenidos para la diferenciacion por pasos\n\n");

printf("Primera diferenciación hacia adelante:\n");
printf("f'(0.5) ≈ %.2f\n",a); //IMPORTANTE: Usamos el símbolo de aproximación porqeu las diferencias
//finitas no son valor exacto de la derivada, solo son aproximaciones
printf("error relativo: %.2f%%\n\n",erroradelante*100);

printf("Primera diferencia hacia atras:\n");
printf("f'(0.5) ≈ %.2f\n",b);
printf("error relativo: %.2f%%\n\n",erroratras*100);

printf("Primera diferencia centrada:\n");
printf("f'(0.5) ≈ %.2f\n",c);
printf("error relativo: %.2f%%\n",errorcentrada*100);

return 0;
}
