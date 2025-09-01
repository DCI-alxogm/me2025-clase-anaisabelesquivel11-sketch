//Ana Isabel Esquivel Castro
//Métodos numéricos
//Código Serie de Taylor 


#include <stdio.h>
#include <math.h>

long factorial(int n){
long fact=1;
for(int i=1;i<=n;i++){
fact*=i;
}
return fact;
}

double derivada(int opcion,int k,double x){
switch(opcion){

  // Para esta parte es necesario declarar las 5 derivadas de cada una de las funciones
  // porque en C como tal no podemos calcular derivadas, es más conveniente hacierlo de esta
  //manera para solo llamarlas más adelante

case 1: //obligatorio usar case
return exp(x);

case 2:
if(k==0)return sin(x);
if(k==1)return cos(x);
if(k==2)return -sin(x);
if(k==3)return -cos(x);
if(k==4)return sin(x);
if(k==5)return cos(x);
return 0;

case 3:
if(k==0)return cos(x);
if(k==1)return -sin(x);
if(k==2)return -cos(x);
if(k==3)return sin(x);
if(k==4)return cos(x);
if(k==5)return -sin(x);
return 0; 

case 4:
if(k==0)return 1.0/(1+x);
if(k==1)return -1.0/pow(1+x,2);
if(k==2)return 2.0/pow(1+x,3);
if(k==3)return -6.0/pow(1+x,4);
if(k==4)return 24.0/pow(1+x,5);
if(k==5)return -120.0/pow(1+x,6);
return 0;

case 5:
if(k==0)return sqrt(1+x);
if(k==1)return 0.5/sqrt(1+x);
if(k==2)return -0.25/pow(1+x,1.5);
if(k==3)return 0.375/pow(1+x,2.5);
if(k==4)return -0.9375/pow(1+x,3.5);
if(k==5)return 3.28125/pow(1+x,4.5);
return 0;

default:
return 0;

}
}

int main(){
int opcion,k;
double h,epsilon,suma,termino,error_aprox,rn;
char continuar;

do{
printf("\n Este es el menú de las 5 posibles funciones que este programa puede evaluar\n");
printf("1) f(x)=e^x\n");
printf("2) f(x)=sin(x)\n");
printf("3) f(x)=cos(x)\n");
printf("4) f(x)=1/(1+x)\n");
printf("5) f(x)=sqrt(1+x)\n");
printf("Por favor, elige una función del menú: ");
scanf("%d",&opcion);

if(opcion<1||opcion>5){
printf("Esta opción no se encuentra en el menú, selecciona de nuevo alguna función de la 1 a la 5\n");
continue;
}

printf("Asigna un valor de h (x - x0): ");
scanf("%lf",&h); // lf es para numeros double pero también podría usar solo float  porque con las 5 derivadas no voy a llegar a algo con tnaotos decimales 
printf("Propon un valor de truncamiento (epsilon): ");
scanf("%lf",&epsilon);

suma=0.0;
k=0;
error_aprox=0.0;

do{
termino=derivada(opcion,k,0)*pow(h,k)/factorial(k);
suma+=termino;
error_aprox=fabs(termino);
k++;

if(k>5&&error_aprox>epsilon){
printf("\nNo hay suficientes derivadas almacenadas para alcanzar el error deseado.\n");
printf("Debes elegir un epsilon mas grande.\n");
break;
}
}while(error_aprox>epsilon&&k<=5);

rn=derivada(opcion,k,0)*pow(h,k)/factorial(k);

printf(" Resultados obtenidos \n"); //mostramos los resultados de las itewraciones :C
printf("h = %.10lf\n",h);
printf("Suma S_n = %.10lf\n",suma);
printf("Error aproximado = %.10lf\n",error_aprox);
printf("Error de truncamiento R_n = %.10lf\n",rn);

printf("¿Deseas calcular otra funcion? (s/n): ");
scanf(" %c",&continuar);

}while(continuar=='s'||continuar=='S');

return 0;
}
