#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "btree.h"

#define MAX_REGISTERS 10

// Função para gerar um número aleatório entre min e max (inclusive)
int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Função para gerar um arquivo com dados aleatórios
void generateDataFile() {
    FILE* file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    srand(time(NULL));

    for (int i = 0; i < MAX_REGISTERS; i++) {
        fprintf(file, "%d\n", getRandomNumber(1, MAX_REGISTERS));
    }

    fclose(file);
}

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
                    no *found = buscaElemento(raiz, value);
                    clock_t end = clock();
                    double time = ((double) (end - start)) / CLOCKS_PER_SEC;

                    if (found) {
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

                    if (removed) {
                        printf("Registro removido com sucesso.\n");
                    } else {
                        printf("Registro não encontrado na B-Tree.\n");
                    }

                    printf("Tempo de remoção: %.6f segundos\n", time);
                }
                break;
            case 4:
                // Sair
                printf("Encerrando o programa.\n");
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
