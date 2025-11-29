//Ana Isabel Esquivel Castro 
//436578
//range 2° Orden 
//MN


#include <stdio.h>

void obtener_derivadas(double t_val, double x_val, double y_val, double *dx, double *dy){
    *dx = x_val + y_val;//Calculo dx/dt
    *dy = -x_val + y_val;//Calculo dy/dt
}

int main(){
    double t_actual = 0.0, paso = 0.1;//Inicializo tiempo y paso
    double x_valor = 1.0, y_valor = 0.0; //Valores iniciales
    double k1x, k1y, k2x, k2y;//Variables para las pendientes
    
    for(int i = 0; i < 10; i++){//10 pasos de cálculo
        obtener_derivadas(t_actual, x_valor, y_valor, &k1x, &k1y); 
        
        obtener_derivadas(t_actual + paso, x_valor + paso*k1x, 
                         y_valor + paso*k1y, &k2x, &k2y);            
        x_valor = x_valor + paso * 0.5 * (k1x + k2x);//Promedio para x
        y_valor = y_valor + paso * 0.5 * (k1y + k2y);//promedio para y
        t_actual = t_actual + paso;//aumento el tiempo
        
        printf("t=%.2f  x=%.4f  y=%.4f\n", t_actual, x_valor, y_valor);//Resultados
    }
    
    return 0;
}