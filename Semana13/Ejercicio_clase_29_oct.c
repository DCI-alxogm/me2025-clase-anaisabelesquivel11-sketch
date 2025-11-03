//Ana Isabel Esquicvel Catro 
//436578
//MN
//Actividad de clase del 29 de octubre del 2025
//Código   de la sección dorada :))


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR 200


char funcion_global[MAX_EXPR]; //se declara la función global antes de usarla

double x_value;
double evaluar_expresion(const char* expresion) {
    char copia[MAX_EXPR];
    strcpy(copia, expresion);
  
    char temp[MAX_EXPR] = ""; //le tenemos que da4r a x un va,or numérico 
    char num[50];
    sprintf(num, "%.6f", x_value);
    
    for(int i = 0, j = 0; expresion[i] != '\0'; i++) {
        if(expresion[i] == 'x') {
            strcat(temp, num);
            j += strlen(num);
        } else {
            temp[j++] = expresion[i];
            temp[j] = '\0';
        }
    }
    
    