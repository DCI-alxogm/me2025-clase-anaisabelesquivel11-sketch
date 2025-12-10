// Ana Isabel Esquivel Castro
// 436578
// MN Proyecto Final
// Runge-Kutta 2° Orden

#include <stdio.h>


void calcular_derivada(double t, double C, double *dCdt) {// Función que calcula la derivada dC/dt
    double k = 0.45;//cte cinética
    double Cmax = 1.0;// concentración máxima
    
    // Ecuación logística: dC/dt = k * C * (Cmax - C)
    *dCdt = k * C * (Cmax - C);
}

int main() {
    double tiempo = 0.0;//tiempo 0
    double paso = 0.1;// saltos o pasos con delta Δt = 0.1
    double concentracion = 0.02;  // C(0) = 0.02 en mol por litro
    double k1, k2;//variables de las pendientes
    
    printf("Resultados\n");
    printf("Ecuacion: dC/dt = 0.45 *C*(1-C)\n");
    printf("C(0) = 0.02 mol/L, dt = 0.1 min\n\n");
    printf("t(min)\tC(mol/L)\n");
    printf("%.1f\t%.6f\n", tiempo, concentracion);//condición inicial
    int num_pasos = (int)(25.0 / paso); //calcular hasta t=25 min
    
    for(int i = 0; i < num_pasos; i++) { //ciclo para calcular k1 y k2
        calcular_derivada(tiempo, concentracion, &k1);
        calcular_derivada(tiempo + paso, 
                         concentracion + paso*k1, 
                         &k2);
        concentracion = concentracion + (paso/2.0)*(k1 + k2);
        tiempo = tiempo + paso;
        if (i % 25 == 0) { //resultado cada 2.5 min 
            printf("%.1f\t%.6f\n", tiempo, concentracion);
        }
    }
    
    return 0;
}