//Ana Isabel Esquivel Castro
//Ejercicio1 

//Realizar un ejercicio que imprima los resultados de las operaciones indicadas con el fin de 
//observar la jerarquía de operaciones
 #include <stdio.h>
 #include <math.h>

int main ()
{
  float a=3, b=4, c=5, d=7;
  float e;

  printf("e=(a+b)*c/d =%f\n",(a+b)*c/d);
  printf("e=((a+b)*c)/d =%f\n",((a+b)*c)/d);
  printf("((a+b)*c)/d =%f\n",a+b*c/d);
  printf("e=a+(b*c)/d =%f\n",e=a+(b*c)/d);

} 