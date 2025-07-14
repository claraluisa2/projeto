#include <stdio.h>
#include <math.h>
#include <time.h>

#define PI 3.141592653589793
#define STEP 0.0125
#define TOTAL_TIME 25


float impedance_control(float k, float b, float teta_eq, float dteta, float teta) {
    float torque = k * (teta - teta_eq) - b * dteta;
    return torque;
}

int main() {

    struct timespec inicio, fim;
    double tempo_gasto;
    
 
    FILE *arquivo_csv;

    arquivo_csv = fopen("resultado_impedancia.csv", "w");

    if (arquivo_csv == NULL) {
        printf("Erro ao criar o arquivo CSV.\n");
        return 1; 
    }

    // Parâmetros de impedância
    float k = 5.0; // Coeficiente de rigidez
    float b = 0.2; // Coeficiente de amortecimento
    float teta_eq = 0.0; // Ângulo de equilibrio

    int N = ((int)(TOTAL_TIME / STEP) + 1);
    float time[N];
    float teta[N]; //vetor de valores de teta (posição angular)
    float dteta[N]; //vetor de valores de dteta (velocidade angular)
    float torque[N];

    for (int i = 0; i < N; i++) {
        time[i] = i * STEP;
        teta[i] = 1 * sin(2 * PI * 0.5 * time[i]);
    }

    for (int i = 0; i < N; i++) {
        if (i == 0) {
            // Para o primeiro ponto dteta = 0
            dteta[i] = 0.0;
        } else {
            // Derivada discreta (aproximação da diferença para trás)
            dteta[i] = (teta[i] - teta[i-1]) / STEP;
        }
        // Chama a função de controle de impedância com o teta atual e o dteta discreto
        torque[i] = impedance_control(k, b, teta_eq, dteta[i], teta[i]);
    }

    // --- Medição ---: Inicia o cronômetro
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    // Escrever o cabeçalho no arquivo CSV (usando vírgula como separador)
    fprintf(arquivo_csv, "time,teta,dteta,torque\n");

    //Escreve os dados no arquivo CSV dentro do loop
    for (int i = 0; i < N; i++) {

        fprintf(arquivo_csv, "%.3f,%.3f,%.3f,%.3f\n", time[i], teta[i], dteta[i], torque[i]);
    }

    fclose(arquivo_csv);

    printf("Arquivo 'resultado_impedancia.csv' gerado com sucesso!\n");

    clock_gettime(CLOCK_MONOTONIC, &fim);

    tempo_gasto = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;

    printf("Tempo de execução: %f segundos\n", tempo_gasto);


    return 0;
}