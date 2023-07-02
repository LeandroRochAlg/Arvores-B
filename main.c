#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bTree.h"

int main() {
    int ordem;
    printf("Informe a ordem da B-Tree: ");
    scanf("%d", &ordem);

    no *raiz = NULL;

    bt *arv = criaBTree(ordem);

    int opcao, chave;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Procurar elemento\n");
        printf("2. Remover registro\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Informe a chave a ser pesquisada: ");
                scanf("%d", &chave);
                no *noEncontrado = buscar(raiz, chave);
                if (noEncontrado != NULL) {
                    printf("Chave encontrada na B-Tree!\n");
                } else {
                    printf("Chave nao encontrada na B-Tree!\n");
                }
                break;

            case 2:
                printf("Informe a chave a ser removida: ");
                scanf("%d", &chave);
                raiz = remover(raiz, chave);
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