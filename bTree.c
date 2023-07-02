//
// Created by rocha on 01/07/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bTree.h"

// Estrutura para os registros
struct registro {
    int matricula;
    char nome[50];
    char dataNascimento[11];
    char email[50];
};

// Estrutura para os nós da B-tree
struct no {
    int numChaves;
    int folha;
    int* chaves;
    registro** registros;
    struct no** filhos;
};

// Estrutura para a B-tree
struct bt {
    no* raiz;
    int minChaves;
    int maxChaves;
};

// Função para criar um novo nó
no* criarNo(int folha, bt* btree) {
    no* novo_no = (no*)malloc(sizeof(no));
    novo_no->numChaves = 0;
    novo_no->folha = folha;
    novo_no->chaves = (int*)malloc(sizeof(int) * (2 * btree->minChaves));
    novo_no->registros = (registro**)malloc(sizeof(registro*) * (2 * btree->minChaves));
    novo_no->filhos = (no**)malloc(sizeof(no*) * (2 * btree->minChaves + 1));
    return novo_no;
}


// Função para criar uma nova B-tree
bt* criarbt(int ordem) {
    bt* btree = (bt*)malloc(sizeof(bt));
    btree->raiz = criarNo(ordem, btree);
    btree->minChaves = ordem - 1;
    btree->maxChaves = 2 * ordem - 1;
    return btree;
}


// Função para liberar a memória ocupada por um nó
void liberarNo(no* no) {
    free(no->chaves);
    free(no->registros);
    free(no->filhos);
    free(no);
}

// Função para liberar a memória ocupada pela B-tree
void liberarbt(bt* btree) {
    if (btree != NULL) {
        if (btree->raiz != NULL) {
            liberarNo(btree->raiz);
        }
        free(btree);
    }
}

// Função para buscar um registro na B-tree
registro* buscarRegistro(bt* btree, int matricula) {
    no* no = btree->raiz;
    int i = 0;
    while (no != NULL) {
        i = buscarPosicaoRegistro(no, matricula);
        if (i < no->numChaves && no->chaves[i] == matricula) {
            return no->registros[i];
        } else if (no->folha) {
            return NULL;
        } else {
            no = no->filhos[i];
        }
    }
    return NULL;
}

// Função para buscar a posição de inserção de uma matrícula em um nó
int buscarPosicaoInsercao(no* no, int matricula) {
    int i = 0;
    while (i < no->numChaves && matricula > no->chaves[i]) {
        i++;
    }
    return i;
}

// Função para buscar a posição de um registro em um nó
int buscarPosicaoRegistro(no* no, int matricula) {
    int i = 0;
    while (i < no->numChaves && matricula > no->chaves[i]) {
        i++;
    }
    return i;
}

// Função para buscar o sucessor de um registro na B-tree
no* buscarSucessor(bt* btree, no* no, int indice) {
    struct no *atual;
    atual = no->filhos[indice + 1];
    while (!atual->folha) {
        atual = atual->filhos[0];
    }
    return atual;
}

// Função para inserir um registro em um nó não cheio
void inserirNoNaoCheio(bt* btree, no* no, registro* registro) {
    int i = no->numChaves;
    if (no->folha) {
        while (i > 0 && registro->matricula < no->chaves[i - 1]) {
            no->chaves[i] = no->chaves[i - 1];
            no->registros[i] = no->registros[i - 1];
            i--;
        }
        no->chaves[i] = registro->matricula;
        no->registros[i] = registro;
        no->numChaves++;
    } else {
        while (i > 0 && registro->matricula < no->chaves[i - 1]) {
            i--;
        }
        if (no->filhos[i]->numChaves == btree->maxChaves) {
            dividirNo(btree, no, i);
            if (registro->matricula > no->chaves[i]) {
                i++;
            }
        }
        inserirNoNaoCheio(btree, no->filhos[i], registro);
    }
}

// Função para dividir um nó cheio
void dividirNo(bt* btree, no* no, int indiceFilho) {
    struct no *filho;
    struct no *novoNo;
    filho = no->filhos[indiceFilho];
    novoNo = criarNo(filho->folha, btree);
    novoNo->numChaves = btree->minChaves;

    for (int j = 0; j < btree->minChaves; j++) {
        novoNo->chaves[j] = filho->chaves[j + btree->minChaves];
        novoNo->registros[j] = filho->registros[j + btree->minChaves];
    }

    if (!filho->folha) {
        for (int j = 0; j <= btree->minChaves; j++) {
            novoNo->filhos[j] = filho->filhos[j + btree->minChaves];
        }
    }

    filho->numChaves = btree->minChaves;

    for (int j = no->numChaves; j > indiceFilho; j--) {
        no->filhos[j + 1] = no->filhos[j];
    }

    no->filhos[indiceFilho + 1] = novoNo;

    for (int j = no->numChaves - 1; j >= indiceFilho; j--) {
        no->chaves[j + 1] = no->chaves[j];
        no->registros[j + 1] = no->registros[j];
    }

    no->chaves[indiceFilho] = filho->chaves[btree->minChaves - 1];
    no->registros[indiceFilho] = filho->registros[btree->minChaves - 1];

    no->numChaves++;
}

// Função para inserir um registro na B-tree
void inserirRegistro(bt* btree, registro* registro) {
    no* raiz = btree->raiz;
    if (raiz->numChaves == (2 * btree->minChaves)) {
        no* novoNo = criarNo(0, btree);
        btree->raiz = novoNo;
        novoNo->filhos[0] = raiz;
        dividirNo(btree, novoNo, 0);
        inserirNoNaoCheio(btree, novoNo, registro);
    } else {
        inserirNoNaoCheio(btree, raiz, registro);
    }
}

// Função para percorrer a B-tree em ordem
void percorrerEmOrdem(bt* btree) {
    no* raiz = btree->raiz;
    if (raiz != NULL) {
        int i;
        for (i = 0; i < raiz->numChaves; i++) {
            if (!raiz->folha) {
                percorrerEmOrdem(btree->raiz->filhos[i]);
            }
            exibirRegistro(raiz->registros[i]);
        }
        if (!raiz->folha) {
            percorrerEmOrdem(raiz->filhos[i]);
        }
    }
}

// Função para exibir um registro
void exibirRegistro(registro* registro) {
    printf("Matrícula: %d\n", registro->matricula);
    printf("Nome: %s\n", registro->nome);
    printf("Data de Nascimento: %s\n", registro->dataNascimento);
    printf("Email: %s\n", registro->email);
    printf("------------------------\n");
}

// Função para remover um registro da B-tree
void removerRegistro(bt* btree, int matricula) {
    no* raiz = btree->raiz;
    if (raiz == NULL) {
        return;
    }
    int indice = buscarPosicaoRegistro(raiz, matricula);
    if (indice < raiz->numChaves && raiz->chaves[indice] == matricula) {
        if (raiz->folha) {
            for (int i = indice; i < raiz->numChaves - 1; i++) {
                raiz->chaves[i] = raiz->chaves[i + 1];
                raiz->registros[i] = raiz->registros[i + 1];
            }
            raiz->numChaves--;
        } else {
            no* filhoEsq = raiz->filhos[indice];
            no* filhoDir = raiz->filhos[indice + 1];
            if (filhoEsq->numChaves >= btree->minChaves) {
                no* antecessor = buscarSucessor(btree, raiz, indice);
                raiz->chaves[indice] = antecessor->chaves[0];
                removerRegistro(btree, antecessor->chaves[0]);
            } else if (filhoDir->numChaves >= btree->minChaves) {
                no* sucessor = buscarSucessor(btree, raiz, indice + 1);
                raiz->chaves[indice] = sucessor->chaves[0];
                removerRegistro(btree, sucessor->chaves[0]);
            } else {
                mesclarNos(btree, raiz, indice, indice);
                removerRegistro(btree, matricula);
            }
        }
    } else {
        no* filho = raiz->filhos[indice];
        if (filho->numChaves >= btree->minChaves) {
            removerRegistro(btree, matricula);
        } else {
            no* irmaoEsq = NULL;
            no* irmaoDir = NULL;
            int indiceIrmao = -1;
            if (indice > 0) {
                irmaoEsq = raiz->filhos[indice - 1];
                indiceIrmao = indice - 1;
            }
            if (indice < raiz->numChaves) {
                irmaoDir = raiz->filhos[indice + 1];
                indiceIrmao = indice;
            }
            if (irmaoEsq && irmaoEsq->numChaves >= btree->minChaves) {
                redistribuirNos(btree, raiz, indiceIrmao, indice - 1);
            } else if (irmaoDir && irmaoDir->numChaves >= btree->minChaves) {
                redistribuirNos(btree, raiz, indiceIrmao, indice);
            } else if (irmaoEsq) {
                mesclarNos(btree, raiz, indice - 1, indice - 1);
            } else if (irmaoDir) {
                mesclarNos(btree, raiz, indice, indice);
            }
            removerRegistro(btree, matricula);
        }
    }
}

// Função para mesclar dois nós irmãos
void mesclarNos(bt* btree, no* no, int indiceIrmao, int indiceChave) {
    struct no *filhoDir;
    struct no *filhoEsq;
    filhoEsq = no->filhos[indiceIrmao];
    filhoDir = no->filhos[indiceIrmao + 1];

    filhoEsq->chaves[btree->minChaves - 1] = no->chaves[indiceChave];

    for (int i = 0; i < filhoDir->numChaves; i++) {
        filhoEsq->chaves[i + btree->minChaves] = filhoDir->chaves[i];
        filhoEsq->registros[i + btree->minChaves] = filhoDir->registros[i];
    }

    if (!filhoEsq->folha) {
        for (int i = 0; i <= filhoDir->numChaves; i++) {
            filhoEsq->filhos[i + btree->minChaves] = filhoDir->filhos[i];
        }
    }

    for (int i = indiceChave; i < no->numChaves - 1; i++) {
        no->chaves[i] = no->chaves[i + 1];
        no->registros[i] = no->registros[i + 1];
    }

    for (int i = indiceIrmao + 1; i < no->numChaves; i++) {
        no->filhos[i] = no->filhos[i + 1];
    }

    no->filhos[no->numChaves] = NULL;
    no->numChaves--;

    liberarNo(filhoDir);
}

// Função para redistribuir os registros entre dois nós irmãos
void redistribuirNos(bt* btree, no* no, int indiceIrmao, int indiceChave) {
    struct no *filhoDir;
    struct no *filhoEsq;
    filhoEsq = no->filhos[indiceIrmao];
    filhoDir = no->filhos[indiceIrmao + 1];

    if (indiceIrmao < indiceChave) {
        filhoEsq->chaves[btree->minChaves - 1] = no->chaves[indiceIrmao];
        filhoEsq->registros[btree->minChaves - 1] = no->registros[indiceIrmao];
        no->chaves[indiceIrmao] = filhoDir->chaves[0];
        no->registros[indiceIrmao] = filhoDir->registros[0];
        for (int i = 0; i < filhoDir->numChaves - 1; i++) {
            filhoDir->chaves[i] = filhoDir->chaves[i + 1];
            filhoDir->registros[i] = filhoDir->registros[i + 1];
        }
        if (!filhoDir->folha) {
            filhoDir->filhos[filhoDir->numChaves] = filhoDir->filhos[filhoDir->numChaves + 1];
        }
    } else {
        for (int i = filhoEsq->numChaves; i > 0; i--) {
            filhoEsq->chaves[i] = filhoEsq->chaves[i - 1];
            filhoEsq->registros[i] = filhoEsq->registros[i - 1];
        }
        if (!filhoEsq->folha) {
            for (int i = filhoEsq->numChaves + 1; i > 0; i--) {
                filhoEsq->filhos[i] = filhoEsq->filhos[i - 1];
            }
        }
        filhoEsq->chaves[btree->minChaves - 1] = no->chaves[indiceChave];
        filhoEsq->registros[btree->minChaves - 1] = no->registros[indiceChave];
        no->chaves[indiceChave] = filhoDir->chaves[filhoDir->numChaves - 1];
        no->registros[indiceChave] = filhoDir->registros[filhoDir->numChaves - 1];
        if (!filhoDir->folha) {
            filhoEsq->filhos[btree->minChaves] = filhoDir->filhos[filhoDir->numChaves];
        }
    }

    filhoEsq->numChaves++;
    filhoDir->numChaves--;
}