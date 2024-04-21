#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define OUTPUT_FILE "SituacaoFinal.csv"

float calcular_media(float notas[], int numNotas) {
    float soma = 0;
    for (int i = 0; i < numNotas; i++) {
        soma += notas[i];
    }
    return soma / numNotas;
}

const char* determinar_situacao(float media) {
    if (media >= 7.0) {
        return "APROVADO";
    } else {
        return "REPROVADO";
    }
}

int main() {
    FILE *entrada, *saida;
    char linha[MAX_LINE_LENGTH];

    entrada = fopen("DadosEntrada.csv", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    saida = fopen(OUTPUT_FILE, "w");
    if (saida == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        fclose(entrada);
        return 1;
    }

    while (fgets(linha, sizeof(linha), entrada)) {
        char *nome, *telefone, *curso, *notaStr;
        float notas[10];
        int numNotas = 0;

        nome = strtok(linha, ",");
        telefone = strtok(NULL, ",");
        curso = strtok(NULL, ",");
        notaStr = strtok(NULL, ",");

        while (notaStr != NULL) {
            notas[numNotas++] = atof(notaStr);
            notaStr = strtok(NULL, ",");
        }

        float media = calcular_media(notas, numNotas);

        const char* situacao = determinar_situacao(media);

        fprintf(saida, "%s, %.2f, %s\n", nome, media, situacao);
    }

    fclose(entrada);
    fclose(saida);

    printf("Processamento concluído. %s.\n", OUTPUT_FILE);

    return 0;
}