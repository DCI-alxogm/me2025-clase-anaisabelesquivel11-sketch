//Ana Isabel Esquic¿vek Castro
//MN
//
#include <stdio.h>
#include <math.h>

double water_activity[] = {
    0.097, 0.147, 0.271, 0.358, 0.439, 0.492, 0.534, 0.564, 0.587, 0.604,
    0.621, 0.632, 0.641, 0.650, 0.658, 0.665, 0.674, 0.679, 0.689, 0.696,
    0.703, 0.711, 0.719, 0.727, 0.734, 0.743, 0.751, 0.760, 0.768, 0.777,
    0.784, 0.793, 0.802, 0.809, 0.818, 0.827, 0.835, 0.843, 0.851, 0.859,
    0.863, 0.863, 0.868, 0.871, 0.879, 0.883, 0.886, 0.887, 0.892, 0.894,
    0.899, 0.900
};

double moisture_content[] = {
    2.070, 2.080, 2.090, 2.110, 2.130, 2.150, 2.150, 2.170, 2.180, 2.190,
    2.210, 2.220, 2.220, 2.230, 2.250, 2.260, 2.260, 2.270, 2.290, 2.300,
    2.320, 2.330, 2.340, 2.360, 2.380, 2.410, 2.430, 2.470, 2.500, 2.540,
    2.580, 2.620, 2.670, 2.720, 2.780, 2.840, 2.900, 2.980, 3.060, 3.160,
    3.250, 3.360, 4.510, 5.720, 6.080, 6.550, 7.200, 7.700, 8.050, 8.330,
    8.570, 9.120
};


const double a0 = -1.62;
const double a01 = 545.40;
const double a1 = -0.59;
const double a11 = 197.91;
const double a2 = 2.45;
const double a3 = 4.81e-3;
const double a31 = -1.39;

const int num_datos = 52;
double calcular_moisture_predicted(double aw, double temp) {
    double tempK = temp + 273.15;
    double b0 = a0 + a01/tempK;
    double b1 = a1 + a11/tempK;
    double b2 = a2;
    double b3 = a3 + a31/tempK;
    
    // Aplicar el modelo Peleg
    double term1 = b0 * pow(aw, b1);
    double term2 = b2 * pow(aw, b3);
    
    return term1 + term2;
}

int main() {
    int i;
    double sum_residuals = 0.0;
    double sum_mean_dev = 0.0;
    double mean_moisture = 0.0;
    