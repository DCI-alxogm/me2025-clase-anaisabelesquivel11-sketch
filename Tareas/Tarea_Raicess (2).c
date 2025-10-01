//Ana Isabe3l Esquivel Castro
//436578
//Tarea de código compilativo


#include <stdio.h>
#include <math.h>

double f(double x) {
    return cos(x) - x;
}


double df(double x) {
    return -sin(x) - 1;
}

double g(double x) {
    return cos(x);
}

// Bisección
double biseccion(double a, double b, int max_iter, double tol, int *iter, double *err) {
    double c, fa, fb;
    fa = f(a);
    fb = f(b);

    for (*iter = 1; *iter <= max_iter; (*iter)++) {
        c = (a + b) / 2.0;
        *err = fabs(f(c));
        if (*err < tol) break;
        if (fa * f(c) < 0) {
            b = c; fb = f(c);
        } else {
            a = c; fa = f(c);
        }
    }
    return c;
}

// Newton-Raphson
double newton(double x0, int max_iter, double tol, int *iter, double *err) {
    double x = x0;
    for (*iter = 1; *iter <= max_iter; (*iter)++) {
        double fx = f(x);
        double dfx = df(x);
        if (dfx == 0) break;
        double x_new = x - fx / dfx;
        *err = fabs(x_new - x);
        if (*err < tol) return x_new;
        x = x_new;
    }
    return x;
}

// Newton-Raphson modificado
double newton_mod(double x0, int max_iter, double tol, int *iter, double *err) {
    double x = x0;
    double dfx = df(x0);
    for (*iter = 1; *iter <= max_iter; (*iter)++) {
        double fx = f(x);
        if (dfx == 0) break;
        double x_new = x - fx / dfx;
        *err = fabs(x_new - x);
        if (*err < tol) return x_new;
        x = x_new;
    }
    return x;
}

// Secante
double secante(double x0, double x1, int max_iter, double tol, int *iter, double *err) {
    double x_prev = x0, x = x1, x_new;
    for (*iter = 1; *iter <= max_iter; (*iter)++) {
        double fx_prev = f(x_prev);
        double fx = f(x);
        if (fx - fx_prev == 0) break;
        x_new = x - fx * (x - x_prev) / (fx - fx_prev);
        *err = fabs(x_new - x);
        if (*err < tol) return x_new;
        x_prev = x;
        x = x_new;
    }
    return x;
}

// Punto fijo
double punto_fijo(double x0, int max_iter, double tol, int *iter, double *err) {
    double x = x0;
    for (*iter = 1; *iter <= max_iter; (*iter)++) {
        double x_new = g(x);
        *err = fabs(x_new - x);
        if (*err < tol) return x_new;
        x = x_new;
    }
    return x;
}

int main() {
    int iter;
    double err, raiz;

    FILE *fp = fopen("/content/results_roots.csv", "w");
    if (!fp) {
        perror("Error creando archivo CSV");
        return 1;
    }
    fprintf(fp, "Metodo,Raiz,Iteraciones,Error\n");

    printf("%-20s %-15s %-12s %-12s\n", "Metodo", "Raiz", "Iteraciones", "Error");

    // Bisección
    raiz = biseccion(0, 1, 50, 1e-6, &iter, &err);
    printf("%-20s %-15.10f %-12d %-12.6e\n", "Biseccion", raiz, iter, err);
    fprintf(fp, "Biseccion,%.10f,%d,%.6e\n", raiz, iter, err);

    // Newton-Raphson
    raiz = newton(0.5, 50, 1e-6, &iter, &err);
    printf("%-20s %-15.10f %-12d %-12.6e\n", "Newton-Raphson", raiz, iter, err);
    fprintf(fp, "Newton-Raphson,%.10f,%d,%.6e\n", raiz, iter, err);

    // Newton-Raphson modificado
    raiz = newton_mod(0.5, 50, 1e-6, &iter, &err);
    printf("%-20s %-15.10f %-12d %-12.6e\n", "Newton Modificado", raiz, iter, err);
    fprintf(fp, "Newton-Modificado,%.10f,%d,%.6e\n", raiz, iter, err);

    // Secante
    raiz = secante(0.0, 1.0, 50, 1e-6, &iter, &err);
    printf("%-20s %-15.10f %-12d %-12.6e\n", "Secante", raiz, iter, err);
    fprintf(fp, "Secante,%.10f,%d,%.6e\n", raiz, iter, err);

    // Finalmente, para Punto fijo
    raiz = punto_fijo(0.5, 50, 1e-6, &iter, &err);
    printf("%-20s %-15.10f %-12d %-12.6e\n", "Punto Fijo", raiz, iter, err);
    fprintf(fp, "Punto-Fijo,%.10f,%d,%.6e\n", raiz, iter, err);

    fclose(fp);
    printf("\nResultados guardados en: /content/results_roots.csv\n");

    return 0;
}
