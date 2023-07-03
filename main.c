#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "btree.h"

#define MAX_REGISTERS 20

int main() {
    int option;
    btree* tree = NULL;
    no* raiz = NULL;

    do {
        printf("Menu\n");
        printf("1. Criar índice\n");
        printf("2. Procurar elementos\n");
        printf("3. Remover registro\n");
        printf("4. Sair\n");
        printf("5. Testar árvore\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                // Criar índice
                if (tree != NULL) {
                    printf("O índice já foi criado.\n");
                } else {
                    tree = criaArvore(4);
                    raiz = getRaiz(tree);
                    manipulaBTree(tree, "data.txt", 'i');
                    printf("Índice criado com sucesso.\n");
                }
                break;
            case 2:
                // Procurar elementos
                if (tree == NULL) {
                    printf("O índice não foi criado.\n");
                } else {
                    int value;
                    printf("Digite o valor a ser procurado: ");
                    scanf("%d", &value);

                    clock_t start = clock();
                    int found = buscarChave(raiz, value);
                    clock_t end = clock();
                    double time = ((double) (end - start)) / CLOCKS_PER_SEC;

                    if (found != -1) {
                        printf("Valor encontrado na B-Tree.\n");
                    } else {
                        printf("Valor não encontrado na B-Tree.\n");
                    }

                    printf("Tempo de busca: %.6f segundos\n", time);
                }
                break;
            case 3:
                // Remover registro
                if (tree == NULL) {
                    printf("O índice não foi criado.\n");
                } else {
                    int value;
                    printf("Digite o valor a ser removido: ");
                    scanf("%d", &value);

                    clock_t start = clock();
                    int removed = removeElemento(tree, value);
                    clock_t end = clock();
                    double time = ((double) (end - start)) / CLOCKS_PER_SEC;

                    if (removed != -1) {
                        printf("Registro removido com sucesso.\n");
                        imprimeArvore(raiz, 0);
                    } else {
                        printf("Registro não encontrado na B-Tree.\n");
                        imprimeArvore(raiz, 0);
                    }

                    printf("Tempo de remoção: %.6f segundos\n", time);
                }
                break;
            case 4:
                // Sair
                printf("Encerrando o programa.\n");
                break;

            case 5:
                //testar
                generateDataFile;
                imprimeArvore(raiz, 0);
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }

        printf("\n");
    } while (option != 4);

    // Liberar a memória alocada pela B-Tree
    if (tree != NULL) {
        //liberaArvore(tree);
    }

    return 0;
}
