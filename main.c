#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LINE_LENGTH 100
#define OUTPUT_FILE "SituacaoFinal.csv"
#define MAX_NOTAS 10

typedef struct {
    char nome[MAX_LINE_LENGTH];
    char telefone[MAX_LINE_LENGTH];
    char curso[MAX_LINE_LENGTH];
    float notas[MAX_NOTAS];
    int numNotas;
} Aluno;

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
    setlocale(LC_ALL, "");
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
        Aluno aluno; 

        char *token = strtok(linha, ",");
        strcpy(aluno.nome, token);
        token = strtok(NULL, ",");
        strcpy(aluno.telefone, token);
        token = strtok(NULL, ",");
        strcpy(aluno.curso, token);
        aluno.numNotas = 0;
        token = strtok(NULL, ",");
        while (token != NULL && aluno.numNotas < MAX_NOTAS) {
            aluno.notas[aluno.numNotas++] = strtof(token, NULL);
            token = strtok(NULL, ",");
        }

        float media = calcular_media(aluno.notas, aluno.numNotas);

        const char* situacao = determinar_situacao(media);

        // Escreve os dados do aluno no arquivo de saída
        fprintf(saida, "%s, %.2f, %s\n", aluno.nome, media, situacao);
    }

    fclose(entrada);
    fclose(saida);

    printf("Processamento concluído. %s.\n", OUTPUT_FILE);

    return 0;
}
