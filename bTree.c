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
    int *chaves;
    struct no **filhos;
    int folha;
};

// Estrutura para a B-tree
struct bt {
    int ordem;
    int numChaves;
    struct no *raiz;
};

// Função para criar uma B-tree
bt *criaBTree(int ordem) {
    bt *arv = (bt *) malloc(sizeof(bt));
    arv->ordem = ordem;
    arv->numChaves = 0;
    arv->raiz = NULL;
    return arv;
}

// Função para ler os registros do arquivo e salvar na B-tree em memória
void lerRegistros(bt *arv, char *nomeArquivo) {
    FILE *arquivo;
    struct registro reg;
    int matricula;
    char nome[50], dataNascimento[11], email[50];

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de registros.\n");
        return;
    }

    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^\n]\n", &matricula, nome, dataNascimento, email) == 4) {
        reg.matricula = matricula;
        strcpy(reg.nome, nome);
        strcpy(reg.dataNascimento, dataNascimento);
        strcpy(reg.email, email);

        // Salvar o registro na B-tree em memória
        insereRegistro(btree, matricula, reg);
    }

    fclose(arquivo);
    printf("Registros lidos com sucesso e salvos na B-tree em memória.\n");
}

// Função para gerar e salvar os registros no arquivo
void gerarRegistros() {
    FILE *arquivo;
    int matriculas[10000];
    int matricula, i;
    char dataNascimento[11], email[50], nome[50];

    arquivo = fopen("registros.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de registros.\n");
        return;
    }

    srand(time(NULL));

    for (i = 0; i < 10000; i++) {
        matricula = gerarMatriculaUnica(matriculas, i);
        matriculas[i] = matricula;

        gerarNome(nome);
        gerarDataNascimento(dataNascimento);
        gerarEmail(email);

        fprintf(arquivo, "%d;%s;%s;%s\n", matricula, nome, dataNascimento, email);
    }

    fclose(arquivo);
    printf("Registros gerados com sucesso e salvos no arquivo 'registros.txt'.\n");
}

// Função para gerar uma matrícula única
int gerarMatriculaUnica(int *matriculas, int n) {
    int matricula;

    do {
        matricula = rand() % 1000000 + 1;
    } while (buscaMatricula(matriculas, n, matricula) != -1);

    return matricula;
}

// Função para buscar uma matrícula no vetor de matrículas
int buscaMatricula(int *matriculas, int n, int matricula) {
    int i;
    for (i = 0; i < n; i++) {
        if (matriculas[i] == matricula) {
            return i;
        }
    }
    return -1;
}

// Função para gerar um nome aleatório
void gerarNome(char *nome) {
    char *nomes[107] = {"Joao", "Maria", "Jose", "Ana", "Pedro", "Paulo", "Carlos", "Marcos", "Lucas", "Mateus",
                       "Ana Paula", "Ana Maria", "Ana Julia", "Ana Luiza", "Ana Beatriz", "Ana Carolina", "Ana Clara",
                       "Ana Laura", "Ana Livia","João", "João Pedro", "João Lucas", "João Gabriel", "João Miguel",
                       "João Vitor", "João Guilherme", "João Victor", "João Paulo","João Miguel", "João Pedro",
                       "João Gabriel", "João Vitor", "João Guilherme", "João Victor", "João Paulo", "João Miguel",
                       "Felipe", "Rafaela", "Leandro", "Leticia", "Gabriel", "Gustavo", "Guilherme", "Rafael",
                       "Lucas", "Matheus", "Nicolas", "Pedro Henrique", "Ryan", "Enzo", "Vitor", "Victor",
                       "Douglas", "Eduardo", "Erick", "Fernando", "Filipe", "Francisco", "Frederico", "Giovane",
                       "Antônio", "Luiza", "Luisa", "Luna", "Maitê", "Manuela", "Marcela", "Maria", "Maria Alice",
                       "Maria Cecília", "Maria Clara", "Maria Eduarda", "Maria Fernanda", "Maria Flor", "Maria Helena",
                       "Caio", "Kaio", "Raffaela", "Raffael", "Breno", "Alejandro", "Raphael", "Vanessa", "Wanessa",
                       "Juliana", "Julia", "Julio", "Julio Cesar", "Julio Cezar", "Julio César", "Julio Cézar","Roberto",
                       "Roberta", "Roberto Carlos", "Marcos", "Marcos Paulo", "Marcos Vinicius", "Marcos Vinnícius", "Vinnícius",
                       "Vinycius", "Vinnicios", "Diego", "Diogo", "Dagoberto", "Bruno", "Bruna", "Bruno Henrique"};
    char *sobrenomes[71] = {"Silva", "Santos", "Oliveira", "Souza", "Lima", "Pereira", "Ferreira", "Alves", "Ribeiro",
                            "Rodrigues", "Costa", "Gomes", "Martins", "Araujo", "Melo", "Barbosa", "Rocha",
                            "Moreira", "Carvalho", "Santana", "Liberato","Gonçalves", "Cardoso", "Azevedo",
                            "Teixeira", "Moura", "Cavalcante", "Dias", "Castro", "Campos", "Bezerra",
                            "Correia", "Fernandes", "Nascimento", "Macedo", "Jesus", "Pinto", "Lopes", "Ramos",
                            "Souza", "Almeida", "Albuquerque", "Alencar", "Almeida", "Alves", "Amaral", "Amorim",
                            "Braz", "Camargo", "Teixeira", "Correia", "Coutinho", "Cruz", "Dias", "Duarte",
                            "Farias", "Galhardo", "Nascimento", "Gomes", "Gonçalves", "Lima", "Lopes", "Macedo",
                            "Machado", "Marques", "Martins", "Melo", "Mendes", "Moraes", "Moreira", "Grande"};

    strcpy(nome, nomes[rand() % 107]);
    strcat(nome, " ");
    strcat(nome, sobrenomes[rand() % 71]);
}

// Função para gerar uma data de nascimento aleatória
void gerarDataNascimento(char *dataNascimento) {
    int dia, mes, ano;

    dia = rand() % 28 + 1;
    mes = rand() % 12 + 1;
    ano = rand() % 40 + 1980;

    sprintf(dataNascimento, "%02d/%02d/%04d", dia, mes, ano);
}

// Função para gerar um e-mail aleatório
void gerarEmail(char *email) {
    char dominio[] = "exemplo.com";
    char letras[] = "abcdefghijklmnopqrstuvwxyz";
    int i;

    // Gera uma sequência aleatória de 10 letras para o nome do e-mail
    for (i = 0; i < 10; i++) {
        email[i] = letras[rand() % 26];
    }

    email[i++] = '@';

    // Copia o domínio fixo
    int j = 0;
    while (dominio[j] != '\0') {
        email[i++] = dominio[j++];
    }

    email[i] = '\0';    // Finaliza a string
}