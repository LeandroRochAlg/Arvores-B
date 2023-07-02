//
// Created by rocha on 01/07/2023.
//

#ifndef TRABALHO_2_BTREE_H
#define TRABALHO_2_BTREE_H

typedef struct no no;
typedef struct bt bt;
typedef struct registro registro;

bt *criaBTree(int ordem);

void lerRegistros(bt *arv, char *nomeArquivo);

void gerarRegistros();

// Função para criar um novo nó
no* criarNo(int folha, bt* btree);

// Função para criar uma nova B-tree
bt* criarBTree();

// Função para liberar a memória ocupada pela B-tree
void liberarBTree(bt* btree);

// Função para buscar um registro na B-tree
registro* buscarRegistro(bt* btree, int matricula);

// Função para inserir um registro na B-tree
void inserirRegistro(bt* btree, registro* registro);

// Função para dividir um nó cheio
void dividirNo(bt* btree, no* no, int indiceFilho);

// Função para inserir um registro em um nó não cheio
void inserirNoNaoCheio(bt* btree, no* no, registro* registro);

// Função para percorrer a B-tree em ordem
void percorrerEmOrdem(bt* btree);

// Função para buscar a posição de inserção de uma matrícula em um nó
int buscarPosicaoInsercao(no* no, int matricula);

// Função para buscar a posição de um registro em um nó
int buscarPosicaoRegistro(no* no, int matricula);

// Função para buscar o sucessor de um registro na B-tree
no* buscarSucessor(bt* btree, no* no, int indice);

// Função para remover um registro da B-tree
void removerRegistro(bt* btree, int matricula);

// Função para mesclar dois nós irmãos
void mesclarNos(bt* btree, no* no, int indiceIrmao, int indiceChave);

// Função para redistribuir os registros entre dois nós irmãos
void redistribuirNos(bt* btree, no* no, int indiceIrmao, int indiceChave);

// Função para exibir um registro
void exibirRegistro(registro* registro);

#endif //TRABALHO_2_BTREE_H
