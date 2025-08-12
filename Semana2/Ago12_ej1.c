//Ejercicio de clase 12 de agosto
//Repaso de ciclos for, errores de redondedo, jerarquía de operaciones y condicionalo if and else


#include <stdio.h>
#include<math.h>

int main()
{
  int num[5]={1,2,3,4,5};
  int tamaño= sizeof(num)/sizeof(num[0]);
  float resultados[5];
  for (int i=0; i<tamaño; i++)
  {
  //printf("%d %d\n", num[i], num[i]%2);
  if(num[i]%2==0)
  {
  resultados[i]=log10(num[i]+1);
  printf("x= %i\n log10(x+1)=%.2f\n ", num[i], resultados[i]);
  }
  else{
    resultados[i]=exp(num[i])+cos(num[i]);
    printf("x= %i\n exp(x)+cos(x)=%.2f\n", num[i], resultados[i]);
  }
  }
  printf("Pi + Pi= %lf", 3.1415926536+3.1415926536);
  return 0;
}