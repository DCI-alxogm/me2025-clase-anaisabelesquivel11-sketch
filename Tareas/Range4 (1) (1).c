//Ana Isabel Esquivel Castro 
//436578
//range 4° Orden 
//MN

#include <stdio.h>

void calcular_derivadas(double t_val, double x_val, double y_val, double *dx, double *dy){
    *dx = x_val + y_val;     // Primera ecuación diferencial
    *dy = -x_val + y_val;    // Segunda ecuación diferencial
}

int main(){
    double tiempo = 0.0, intervalo = 0.1;//tiempo inicial y paso
    double x_actual = 1.0, y_actual = 0.0;//condiciones iniciales
    double pend1_x, pend1_y, pend2_x, pend2_y, pend3_x, pend3_y, pend4_x, pend4_y;//las 4 pendientes
    
    for(int contador = 0; contador < 10; contador++){//voy a hacer 10 vueltas
        calcular_derivadas(tiempo, x_actual, y_actual, &pend1_x, &pend1_y); //pendiente 1
        
        calcular_derivadas(tiempo + intervalo/2, x_actual + intervalo*pend1_x/2, 
                          y_actual + intervalo*pend1_y/2, &pend2_x, &pend2_y); //pendiente 2
        
        calcular_derivadas(tiempo + intervalo/2, x_actual + intervalo*pend2_x/2, 
                          y_actual + intervalo*pend2_y/2, &pend3_x, &pend3_y); //pendiente 3
        
        calcular_derivadas(tiempo + intervalo, x_actual + intervalo*pend3_x, 
                          y_actual + intervalo*pend3_y, &pend4_x, &pend4_y); //pendiente 4
        
        x_actual = x_actual + (intervalo/6.0)*(pend1_x + 2*pend2_x + 2*pend3_x + pend4_x);//sctualizo x
        y_actual = y_actual + (intervalo/6.0)*(pend1_y + 2*pend2_y + 2*pend3_y + pend4_y);//actualizo y
        tiempo = tiempo + intervalo;//sumo el intervalo al tiempo
        
        printf("t=%.2f  x=%.4f  y=%.4f\n", tiempo, x_actual, y_actual);
    }
    
    return 0; }