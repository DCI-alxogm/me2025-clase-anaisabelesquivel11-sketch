// Ana Isabel Esquivel Castro
// 436578
// MN Proyecto Final
//436578
// Runge-Kutta 4° orden


#include <stdio.h>

void calcular_derivada(double t, double C, double *dCdt) { //función que calcula la derivada de dc/dt
    double k = 0.45;//cte cinética
    double Cmax = 1.0;//concentración máxima
    
    // Ecuación logística: dC/dt = k * C * (Cmax - C)
    *dCdt = k * C * (Cmax - C);
}
int main() {
    double tiempo = 0.0;//definimos el tiempo inicial
    double paso = 0.1;//nuestro delta t es  Δt = 0.1
    double concentracion = 0.02;// la concentración en 0 es  C(0) = 0.02, usando litros por mol
    double k1, k2, k3, k4; //tenemos las variables para las 4 pendientes de RK4
    
    printf("Resultados\n");
    printf("dC/dt= 0.45*C*(1-C)\n");
    printf("C(0)= 0.02 mol/L, dt= 0.1 min\n\n");
    printf("t(min)\tC(mol/L)\n");
    printf("%.1f\t%.6f\n", tiempo, concentracion);//mostramos la condición inicial
    
    int num_pasos = (int)(25.0 / paso);//calculamos hasta t=25 min
    
    for(int i = 0; i < num_pasos; i++) { //ciclo para calcular la pendiente k1, k2, k3 y k4
        calcular_derivada(tiempo, concentracion, &k1);
        calcular_derivada(tiempo + paso/2, 
                         concentracion + paso*k1/2, 
                         &k2);
        calcular_derivada(tiempo + paso/2, 
                         concentracion + paso*k2/2, 
                         &k3);
        calcular_derivada(tiempo + paso, 
                         concentracion + paso*k3, 
                         &k4);
        concentracion = concentracion + (paso/6.0)*(k1 + 2*k2 + 2*k3 + k4); //actualixamos la concentración usando la fórmula de RK4 
        tiempo = tiempo + paso;
        if (i % 25 == 0) { //Resultasdo cada 2.5 min
            printf("%.1f\t%.6f\n", tiempo, concentracion);
        }
    }
    return 0;
}