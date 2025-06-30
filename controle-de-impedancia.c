
#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793
#define STEP 0.0125
#define TOTAL_TIME 0.1

double impedance_control(double k, double b, double teta_eq, double dteta, double teta) {
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
    double teta[N]; //vetor de valores de teta (velocidade)
    double torque[N];

    for (int i = 0; i < N; i++) {
        time[i] = i * STEP;
        teta[i] = 1 * sin(2 * PI * 0.5 * time[i]);
    }

    for (int i = 0; i < N; i++) {
        double dteta;

        if (i == 0) {
            // Para o primeiro ponto dteta = 0
            dteta = 0.0;
        } else {
            // Derivada discreta (aproximação da diferença para trás)
            // (teta[n] - teta[n-1]) / STEP
            dteta = (teta[i] - teta[i-1]) / STEP;
        }
        // Chama a função de controle de impedância com o teta atual e o dteta discreto
        torque[i] = impedance_control(k, b, teta_eq, dteta, teta[i]);
    }

    printf("time\ttorque\n");
    for (int i = 0; i < N; i++) {
        printf("%.4f\t%.4f\n", time[i], torque[i]);
    }

    return 0;
}
