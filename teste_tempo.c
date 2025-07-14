#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   

#define NUM_AMOSTRAS 100
#define NUM_FLOATS_POR_AMOSTRA 20
#define NOME_ARQUIVO "dados_gravacao.csv"

int main() {
    // matriz para armazenar os dados 
    float amostras[NUM_AMOSTRAS][NUM_FLOATS_POR_AMOSTRA];

    
    srand(time(NULL)); // inicializa o gerador de números aleatórios

    printf("Gerando %d amostras de %d floats em memória...\n", NUM_AMOSTRAS, NUM_FLOATS_POR_AMOSTRA);
    for (int i = 0; i < NUM_AMOSTRAS; i++) {
        for (int j = 0; j < NUM_FLOATS_POR_AMOSTRA; j++) {
            amostras[i][j] = ((float)rand() / (float)(RAND_MAX)) * 100.0; // gera um float aleatório entre 0.000 e 99.999
        }
    }
    printf("Dados gerados com sucesso.\n\n");

    FILE *arquivo;
    // Variáveis para clock()
    clock_t inicio_cpu, fim_cpu;
    double tempo_gasto_cpu;

    // Variáveis para clock_gettime()
    struct timespec inicio_real, fim_real;
    double tempo_gasto_real;

    printf("Iniciando cronômetro e a gravação no arquivo '%s'...\n", NOME_ARQUIVO);

    // Inicia o cronômetro
    inicio_cpu = clock();
    clock_gettime(CLOCK_MONOTONIC, &inicio_real);


    // Abre o arquivo para escrita
    arquivo = fopen(NOME_ARQUIVO, "w");
    if (arquivo == NULL) {
        perror("Erro crítico ao abrir o arquivo para escrita");
        return 1;
    }

    // Loop para escrever todas as amostras no arquivo
    for (int i = 0; i < NUM_AMOSTRAS; i++) {
        for (int j = 0; j < NUM_FLOATS_POR_AMOSTRA; j++) {
            fprintf(arquivo, "%.3f", amostras[i][j]);

            // põe uma vírgula para todos menos o último número
            if (j < NUM_FLOATS_POR_AMOSTRA - 1) {
                fprintf(arquivo, ",");
            }
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    fim_cpu = clock();
    tempo_gasto_cpu = ((double)(fim_cpu - inicio_cpu)) / CLOCKS_PER_SEC;
    clock_gettime(CLOCK_MONOTONIC, &fim_real);
    tempo_gasto_real = (fim_real.tv_sec - inicio_real.tv_sec) +
                       (fim_real.tv_nsec - inicio_real.tv_nsec) / 1000000000.0;

    printf("\n--- Resultados ---\n");
    printf("Tempo medido por clock()      (CPU Time): %f segundos\n", tempo_gasto_cpu);
    printf("Tempo medido por clock_gettime() (Real Time):  %f segundos\n", tempo_gasto_real);
    
    return 0;
}