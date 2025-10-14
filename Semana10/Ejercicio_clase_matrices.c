//Ana Isabel Esquivel Castro
//436578
//Realizar un código que siga el método de Gauss para 
//resolver matrices en las que nosotros mismos definamos su tamaño



#include <stdio.h>
 
int main() {

  //1.- Definimos la matriz y sus valores correspondientes :)))
  double A[3][3]={
    {3, -0.1, -0.2},
    {0.1, 7, -0.3},
    {0.3, 0.2, 10}
  };
  //Definimos el vector B
  double B[3]={7.85, -19.3, 71.4};
  double X[3];
  double factor, suma;
  int n, m, k;

  for (k=0; k<2; k++) {
    for (n=k+1; n<3; n++) {
        factor=A[n][k]/A[k][k];
        for (m=k; m<3; m++) {
            A[n][m]=A[n][m]-factor*A[k][n];
        }
        B[n]=B[n]-factor*B[k];
      }
    }
 
  for (n=2; n>=0; n--) {
      suma=0;
      for (m=n+1; m<3; m++) {
          suma+=A[n][m]*X[m];
      }
      X[n]=(B[n]-suma)/A[n][n];
    }
  printf("Valores encontrados :D!!!:\n");
    for (n=0; n<3; n++) {
      printf("X%d = %.6f\n", n+1, X[n]);
    }
  return 0;
}