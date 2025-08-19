//Ana Isabel Esquivel Castro
//436578
// Tarea 1 Semana 2
// Realizar un programa para resolver una ec. cuadrática siguiendo el diagrama de flujo mostrado en clase

#include <stdio.h> //inicializamos
#include <math.h>

int main()

{
  float a, b, c, dsrc, x1, x2, xi1, xi2; //definimos todas las variables posibles incluyendo las raíces imaginarias
 char opcion;  //esta es una variable de control que nos permite decidir si el ciclo se repite o no con s y S del final o n para terminar    

 do
 {
 printf("Por favor, ingresa valores enteros para a,b y c: ");
 scanf("%f %f %f", &a, &b, &c); //& solo se usa para scanf

 if( (a != (int)a) || (b != (int)b) || (c != (int)c) ) // a partir del cuadro de signos lógicos, estamos haciendo negaciones de enteros al ingresar !=
  {
 printf("Los valores que ingresaste no son enteros \n");
 continue;    
 }

 if(a == 0 && b == 0)//en caso de que tengamos dos valores de a y b = 0 
 {
   printf("Para los valores que ingresaste no se obtiene una solución cuadrática ni lineal, ingresa nuevos valores para a,b y c \n");
  continue;
  }

 if(a == 0) 
{
  x1 = -c / b;
  printf ("<Obtuvimos una solucón lineal: x = %.2f \n", x1);
} 
else
 {
 dsrc = (b * b) - (4 * a * c);

 if(dsrc < 0) //si la raíz obtenida es menor a 0, se trata de soluciones imaginariass
 {
 printf("Con estos valores no obtuvimos raíces reales\n");
 }
 else if(dsrc == 0)  
  {
 x1=-b/(a*2);
 printf("Obtuvimos la siguiente raíz doble: x = %.2f\n", x1);
 }
 else 

 {
  x1= (-b+sqrt(dsrc)) / (a*2);
 x2= (-b-sqrt(dsrc)) / (a*2);
 printf("Dos raices reales: x1 = %.2f x2 = %.2f \n", x1,x2);

 }
 }

//Regresamos al paso de ingresar valores para a,b y c en caso de que así lo desee el usuario
 printf("¿Desea resolver otrz ecuación con diferentes valores para a,b y c? Responde s para si y n para no (s/n): ");
 getchar();  //usamos getchar para "limpiar" o "recetear" los valores ingresados en el programa       
 scanf("%c", &opcion);
 printf("\n");   

 } while(opcion == 's' || opcion == 'S');  

 return 0;
}
