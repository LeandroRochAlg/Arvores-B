//
// Created by Vanessa on 22/06/2022.
//

#ifndef LISTA_9_BTREE_H
#define LISTA_9_BTREE_H

typedef struct no no;

typedef struct bt bt;

typedef struct registro registro;

//Função que aloca e inicializa um novo nó
no *alocaNo(int ordem);

//Função que aloca e inicializa uma nova árvore com uma raiz alocada, porém vazia.
//Árvore B tradicional. A ordem m deve ser sempre par. Caso contrário, retorna NULL.
bt *criaArvore(int m);

//Função que retorna a raiz da árvore
no *retornaRaiz(bt *arvore);

//Função recursiva que retorna o nó onde o elemento está na árvore
no *buscaElemento(no *atual, int valor);

//Função que insere um novo elemento na árvore.
//Encontra a folha correta, realiza a inserção em árvore B tradicional
//Ou seja, se a folha estiver cheia, primeiro realiza o split e depois insere
//Se houve a inserção, retorna 1. Caso contrário, retorna -1
int insereElemento(bt *arvore, int valor, registro *reg);

//Função que realiza o split no noDesbal. A variável valor guarda o elemento que está sendo inserido (e que causou o split)
//Função chamada pela função insereElemento
//Sempre sobe o elemento do meio para o pai (m é sempre par).
//Caso o pai esteja cheio, a função se chama recursivamente.
no *split(bt *arvore, no *noDesbal, int valor);

//Função que remove um elemento da B-Tree
//Na remoção por cópia, usar o predecessor
//No caso de rotação e merge, tentar primeiro o irmão da esquerda e depois o da direita
//Se houve a remoção, retorna 1. Caso contrário, retorna -1
int removeElemento(bt *arvore, int valor);

//Função que implementa a rotação, levanto um elemento do pai para o nóDesbal e subindo um elemento do no irmão para o pai
// A variável posPai guarda a posição do ponteiro do pai que aponta para o nó noDesbal
void rotacao(no *noDesbal, no *irmao, int posPai);

//Função que implementa o merge do nó Desbal com seu irmão da esquerda ou da direita
//Se a variãvel posPai é maior que zero, o merge acontece com o irmão da esquerda
//Caso contrário, com o irmão da direita
no *merge(no *noDesbal, int posPai);

no* getRaiz(bt *tree);

no *alocaNo(int ordem);

void lerRegistros(bt *arv, char *nomeArquivo);

void insereElemento(bt *arv, registro reg);

void insereNaoCheio(no *no, registro reg, int ordem);

void divideNo(no *pai, int i, no *filho, int ordem);

registro *buscar(bt *arv, int matricula);

registro *buscaElementoNo(no *no, int matricula);

void removerElemento(bt *arv, int matricula);

void preencherNo(no* no, int indice);

void removerChave(no *no, int matricula, int ordem);

void removerElementoNo(no *no, int indice, int ordem);

registro *encontraPredescessor(no *no, int indice);

registro *encontraSucessor(no *no, int indice);

void rotacaoEsq(no *pai, int indice, int ordem);

void rotacaoDir(no *pai, int indice, int ordem);

void merge(no *pai, int indice, int ordem);

void gerarRegistros();

int gerarMatriculaUnica(int *matriculas, int n);

int buscaMatricula(int *matriculas, int n, int matricula);

void gerarNome(char *nome);

void gerarDataNascimento(char *dataNascimento);

void gerarEmail(char *email);

void buscarRegistro(int matricula);

#endif //LISTA_9_BTREE_H