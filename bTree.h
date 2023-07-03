//
// Created by rocha on 01/07/2023.
//

#ifndef TRABALHO_2_BTREE_H
#define TRABALHO_2_BTREE_H

typedef struct no no;
typedef struct bt bt;
typedef struct registro registro;

bt *criaBTree(int ordem);

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

#endif //TRABALHO_2_BTREE_H
