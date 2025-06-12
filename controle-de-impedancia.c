
#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793
#define STEP 0.0125
#define TOTAL_TIME 10.0

double impedance_control(double t, double k, double b, double teta_eq, double amplitude, double freq) {
    double teta = amplitude * sin(2 * PI * freq * t); // posição da junta no tempo t
    double dteta = 2 * PI * freq * amplitude * cos(2 * PI * freq * t); //velocidade da junta no tempo t
    double torque = k * (teta - teta_eq) - b * dteta;
    return torque;
}

int main() {

    // Parâmetros de impedância
    double k = 5.0; // Coeficiente de rigidez
    double b = 0.2; // Coeficiente de amortecimento
    double teta_eq = 0.0; // Ângulo de equilibrio

    int N = ((int)(TOTAL_TIME / STEP) + 1);
    double time[N];
    double torque[N];

    for (int i = 0; i < N; i++) {
        time[i] = i * STEP;
        torque[i] = impedance_control(time[i], k, b, teta_eq, 0.5, 1);
    }

    printf("time\ttorque\n");
    for (int i = 0; i < N; i++) {
        printf("%.4f\t%.4f\n", time[i], torque[i]);
    }

    return 0;
}
