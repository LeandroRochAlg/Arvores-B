#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "bTree.h"

int main() {
    char nomeArquivo[30];
    int opcao, matricula, ordem, teste, busca;
    struct timeval inicio, fim;
    long menorTempoArv = 1000, maiorTempoArv = -1, tempoTotalArv, tempo;
    long menorTempoArq = 1000, maiorTempoArq = -1, tempoTotalArq;
    float tempoMedioArv, tempoMedioArq;

    gerarRegistros();

    printf("Informe a ordem da B-Tree: ");
    scanf("%d", &ordem);

    no *raiz = NULL;

    bt *arv = criaArvore(ordem);

    registro *reg;

    srand(time(NULL));

    printf("Informe o nome do arquivo de registros: ");
    scanf("%s", nomeArquivo);
    lerRegistros(arv, nomeArquivo);
    printf("Registros inseridos na B-Tree!\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Procurar elemento\n");
        printf("2. Remover registro\n");
        printf("3. Calcular métricas\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                printf("Informe a matrícula a ser pesquisada: ");
                scanf("%d", &matricula);
                raiz = buscaElemento(getRaiz(arv), matricula);
                if (raiz != NULL) {
                    printf("Chave encontrada na B-Tree!\n");
                } else {
                    printf("Chave nao encontrada na B-Tree!\n");
                }
                break;

            case 2:
                printf("Informe a chave a ser removida: ");
                scanf("%d", &matricula);
                teste = removeElemento(arv, matricula);
                if(teste == 1){
                    printf("Chave removida da B-Tree!\n");
                }else if(teste == -1){
                    printf("Chave nao encontrada na B-Tree!\n");
                }
                break;

            case 3:
                printf("Iniciando calculo das metricas...\n");
                tempoTotalArv = 0;
                tempoTotalArq = 0;
                for (int i = 0; i<30; i++){
                    busca = rand() % 1000000;

                    gettimeofday(&inicio, NULL);
                    raiz = buscaElemento(getRaiz(arv), busca);
                    gettimeofday(&fim, NULL);
                    tempo = (fim.tv_sec * 1000000 + fim.tv_usec) - (inicio.tv_sec * 1000000 + inicio.tv_usec);

                    if (tempo < menorTempoArv){
                        menorTempoArv = tempo;
                    }
                    if (tempo > maiorTempoArv){
                        maiorTempoArv = tempo;
                    }

                    tempoTotalArv += tempo;

                    gettimeofday(&inicio, NULL);
                    buscarRegistro(busca);
                    gettimeofday(&fim, NULL);
                    tempo = (fim.tv_sec * 1000000 + fim.tv_usec) - (inicio.tv_sec * 1000000 + inicio.tv_usec);

                    if (tempo < menorTempoArq){
                        menorTempoArq = tempo;
                    }
                    if (tempo > maiorTempoArq){
                        maiorTempoArq = tempo;
                    }

                    tempoTotalArq += tempo;
                }
                tempoMedioArv = (float)tempoTotalArv/30.0;
                tempoMedioArq = (float)tempoTotalArq/30.0;

                printf("Menor tempo de busca na B-Tree: %ld microsegundos\n", menorTempoArv);
                printf("Maior tempo de busca na B-Tree: %ld microsegundos\n", maiorTempoArv);
                printf("Tempo medio de busca na B-Tree: %f microsegundos\n", tempoMedioArv);
                printf("Tempo total de busca na B-Tree: %ld microsegundos\n\n", tempoTotalArv);

                printf("Menor tempo de busca no arquivo: %ld microsegundos\n", menorTempoArq);
                printf("Maior tempo de busca no arquivo: %ld microsegundos\n", maiorTempoArq);
                printf("Tempo medio de busca no arquivo: %f microsegundos\n", tempoMedioArq);
                printf("Tempo total de busca no arquivo: %ld microsegundos\n\n", tempoTotalArq);
                break;

            case 4:
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}