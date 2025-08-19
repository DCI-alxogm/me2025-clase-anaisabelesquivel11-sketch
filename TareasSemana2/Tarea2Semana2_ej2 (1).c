//Ana Isabel Esquivel
//436578
//Métodos numéricos
//Análisis de números par e impar


#include <stdio.h>
#include <math.h>


int preguntaPorEntero()
 {
  int num;
  char term;
  printf("Por favor, ingresa un número entero para evaluar: ");

  while (scanf("%d%c", &num, &term) != 2 || term != '\n') {
    printf("Entrada inválida. Por favor, ingrese un número entero: ");
   
    while (getchar() != '\n')
      ;
  }
  return num;
}

int main() {
  int num;
  char term;
  char continuar;

  do {

  printf("Ingrese un número: ");
  
  if (scanf("%d%c", &num, &term) != 2 || term != '\n') {
    while (getchar() != '\n')
      ;
    num = preguntaPorEntero();
  }

  
  if (num % 2 == 0) {
    printf("Se trata de número par\n");
  } else {
    printf("Se trata de número no par\n");
  }

  printf ("¿Te gustaría volver a evaluar un número nuevo? Ingresa s para si y n para no");
  scanf ("%c",&continuar);
  while(getchar()!='\n');
 }While (continuar == 's'|| continuar =='S');


  return 0;
}