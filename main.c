#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "bTree.h"

int main() {
    char nomeArquivo[30];
<<<<<<< HEAD
    int opcao, matricula, ordem, teste, busca;
    struct timeval inicio, fim;
    long menorTempoArv = 1000000, maiorTempoArv = -1, tempoTotalArv, tempo;
    long menorTempoArq = 1000000, maiorTempoArq = -1, tempoTotalArq;
    float tempoMedioArv, tempoMedioArq;

    gerarRegistros();

    while(1) {
        printf("Informe a ordem da B-Tree (3 a 15): ");
        scanf("%d", &ordem);

        if (ordem <= 15 && ordem >= 3) {
            break;
        } else {
            printf("Ordem invalida!\n");
        }
    }
=======
    int opcao, matricula, ordem;

    gerarRegistros();

    printf("Informe a ordem da B-Tree: ");
    scanf("%d", &ordem);
>>>>>>> 420472fec158129bca815a91c490a3874d2ac9d0

    no *raiz = NULL;

    bt *arv = criaArvore(ordem);

    registro *reg;

    srand(time(NULL));

    printf("Informe o nome do arquivo de registros: ");
    scanf("%s", nomeArquivo);
    lerRegistros(arv, nomeArquivo);
    printf("Registros inseridos na B-Tree!\n");

<<<<<<< HEAD
=======
    registro *reg;

>>>>>>> 420472fec158129bca815a91c490a3874d2ac9d0
    while (1) {
        printf("\nMenu:\n");
        printf("0. Inserir registros\n");
        printf("1. Procurar elemento\n");
        printf("2. Remover registro\n");
        printf("3. Calcular métricas\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

<<<<<<< HEAD
        switch (opcao){
            case 1:
                printf("Informe a matrícula a ser pesquisada: ");
                scanf("%d", &matricula);
                raiz = buscaElemento(getRaiz(arv), matricula);
                if (raiz != NULL) {
=======
        switch (opcao) {
            case 0:
                printf("Informe o nome do arquivo de registros: ");
                scanf("%s", nomeArquivo);
                lerRegistros(arv, nomeArquivo);
                printf("Registros inseridos na B-Tree!\n");
                break;
            case 1:
                printf("Informe a matrícula a ser pesquisada: ");
                scanf("%d", &matricula);
                reg = buscar(arv, matricula);
                if (reg != NULL) {
>>>>>>> 420472fec158129bca815a91c490a3874d2ac9d0
                    printf("Chave encontrada na B-Tree!\n");
                } else {
                    printf("Chave nao encontrada na B-Tree!\n");
                }
                break;

            case 2:
                printf("Informe a chave a ser removida: ");
                scanf("%d", &matricula);
<<<<<<< HEAD
                teste = removeElemento(arv, matricula);
                if(teste == 1){
                    printf("Chave removida da B-Tree!\n");
                }else if(teste == -1){
                    printf("Chave nao encontrada na B-Tree!\n");
                }
=======
                removerElemento(arv, matricula);
                printf("Chave removida da B-Tree!\n");
>>>>>>> 420472fec158129bca815a91c490a3874d2ac9d0
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