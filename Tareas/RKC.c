// Ana Isabel Esquivel Castro
// 436578
// MN - Proyecto Final
// Comparación RK4 vs RK2 con diferentes dt

#include <stdio.h>
#include <math.h>

// Función que calcula la derivada
void derivada(double t, double C, double *dCdt) {
    *dCdt = 0.45 * C * (1.0 - C);
}

// Función para calcular un paso con RK4
double paso_rk4(double t, double C, double paso) {
    double k1, k2, k3, k4;
    
    derivada(t, C, &k1);
    derivada(t + paso/2, C + paso*k1/2, &k2);
    derivada(t + paso/2, C + paso*k2/2, &k3);
    derivada(t + paso, C + paso*k3, &k4);
    
    return C + (paso/6.0)*(k1 + 2*k2 + 2*k3 + k4);
}

// Función para calcular un paso con RK2
double paso_rk2(double t, double C, double paso) {
    double k1, k2;
    
    derivada(t, C, &k1);
    derivada(t + paso, C + paso*k1, &k2);
    
    return C + (paso/2.0)*(k1 + k2);
}

int main() {
    double t = 0.0;
    double paso_rk4_valor = 0.1;
    double C_rk4 = 0.02, C_rk2 = 0.02;
    
   
    printf("RK4 usa dt = 0.1\n");
    printf("RK2 prueba diferentes dt\n\n");
    printf("Resultado RK4 (dt=0.1) en t=25 min:\n"); //primero calculamos RK4 con dt=0.1
    double tiempo_rk4 = 0.0;
    double C_rk4_final = 0.02;
    int pasos_rk4 = (int)(25.0 / paso_rk4_valor);
    
    for(int i = 0; i < pasos_rk4; i++) {
        C_rk4_final = paso_rk4(tiempo_rk4, C_rk4_final, paso_rk4_valor);
        tiempo_rk4 += paso_rk4_valor;
    }
    printf("C(25) = %.8f mol/L\n\n", C_rk4_final);
    printf("dt\t\tC(25) RK2\t\tDiferencia con RK4\n");//ahora probamos diferentes dt para RK2
    double dt_prueba[] = {0.1, 0.05, 0.02, 0.01, 0.005};
    
    for(int j = 0; j < 5; j++) {
        double dt = dt_prueba[j];
        double t_rk2 = 0.0;
        double C_rk2_temp = 0.02;
        int pasos_rk2 = (int)(25.0 / dt);
        
        for(int i = 0; i < pasos_rk2; i++) {
            C_rk2_temp = paso_rk2(t_rk2, C_rk2_temp, dt);
            t_rk2 += dt;
        }
        
        double diferencia = fabs(C_rk2_temp - C_rk4_final);
        printf("%.4f\t\t%.8f\t\t%.8f\n", dt, C_rk2_temp, diferencia);
    }
    
    double dt_prueba_fino = 0.01;
    double diferencia_minima = 1.0;
    double dt_optimo = 0.1;
    
    for(int intento = 0; intento < 10; intento++) {
        double t_rk2 = 0.0;
        double C_rk2_temp = 0.02;
        int pasos_rk2 = (int)(25.0 / dt_prueba_fino);
        
        for(int i = 0; i < pasos_rk2; i++) {
            C_rk2_temp = paso_rk2(t_rk2, C_rk2_temp, dt_prueba_fino);
            t_rk2 += dt_prueba_fino;
        }
        
        double diferencia = fabs(C_rk2_temp - C_rk4_final);
        printf("dt = %.6f -> C(25) = %.8f, diferencia = %.8f\n", 
               dt_prueba_fino, C_rk2_temp, diferencia);
        
        if (diferencia < diferencia_minima) {
            diferencia_minima = diferencia;
            dt_optimo = dt_prueba_fino;
        }
        
        dt_prueba_fino /= 2.0;  // Probamos con dt más pequeño
    }
    
    printf("Para obtener el mismo resultado que RK4 con dt=0.1,\n");
    printf("RK2 necesita dt ≈ %.6f min\n", dt_optimo);
    
    return 0;
}