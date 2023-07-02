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

int gerarMatriculaUnica(int *matriculas, int i);

int buscaMatricula(int *matriculas, int n, int matricula);

void gerarNome(char *nome);

void gerarDataNascimento(char *dataNascimento);

void gerarEmail(char *email);

#endif //TRABALHO_2_BTREE_H
