#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bTree.h"

int main() {
    char nomeArquivo[30];
    int opcao, matricula, ordem;

    gerarRegistros();

    printf("Informe a ordem da B-Tree: ");
    scanf("%d", &ordem);

    no *raiz = NULL;

    bt *arv = criaArvore(ordem);

    registro *reg;

    while (1) {
        printf("\nMenu:\n");
        printf("0. Inserir registros\n");
        printf("1. Procurar elemento\n");
        printf("2. Remover registro\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

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
                removeElemento(arv, matricula);
                printf("Chave removida da B-Tree!\n");
                break;

            case 3:
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}