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
    struct registro *registros;
    struct no **filhos;
    struct no *pai;
    int folha;
    int ocupacao;
};

// Estrutura para a B-tree
struct bt {
    int ordem;
    struct no *raiz;
};

// Função para criar uma B-tree
bt *criaBTree(int ordem) {
    bt *arv = (bt *) malloc(sizeof(bt));
    arv->ordem = ordem;
    arv->raiz = alocaNo(ordem);
    return arv;
}

//Função que aloca e inicializa um novo nó
no *alocaNo(int ordem){
    no *novoNo = (no *) malloc(sizeof(no));

    novoNo->numChaves = 0;
    novoNo->registros = (registro *) malloc(sizeof(registro) * (ordem - 1));
    novoNo->filhos = (no **) malloc(sizeof(no *) * ordem);
    novoNo->folha = 1;
    novoNo->ocupacao = 0;
    novoNo->pai = NULL;

    return novoNo;
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
        insereElemento(arv, reg);
    }

    fclose(arquivo);
    printf("Registros lidos com sucesso e salvos na B-tree em memória.\n");
}

// Função para inserir um elemento na B-tree
void insereElemento(bt *arv, registro reg) {
    no *raiz = arv->raiz;

    // Se a raiz estiver cheia, é necessário criar uma nova raiz
    if (raiz->numChaves == (2 * arv->ordem - 1)) {
        no *novaRaiz = alocaNo(arv->ordem);
        arv->raiz = novaRaiz;
        novaRaiz->folha = 0;
        novaRaiz->filhos[0] = raiz;
        raiz->pai = novaRaiz;

        if(arv->ordem%2 == 0){
            insereNaoCheio(novaRaiz, reg, arv->ordem-1);
            divideNo(novaRaiz, 0, raiz, arv->ordem-1);
        }else{
            divideNo(novaRaiz, 0, raiz, arv->ordem);
            insereNaoCheio(novaRaiz, reg, arv->ordem);
        }
    } else {
        insereNaoCheio(raiz, reg, arv->ordem);
    }
}

// Função para inserir um elemento em um nó não cheio
void insereNaoCheio(no *no, registro reg, int ordem) {
    int i = no->numChaves - 1;

    if (no->folha) {
        while (i >= 0 && reg.matricula < no->registros[i].matricula) {
            no->registros[i + 1] = no->registros[i];
            i--;
        }

        no->registros[i + 1] = reg;
        no->numChaves++;
    } else {
        while (i >= 0 && reg.matricula < no->registros[i].matricula) {
            i--;
        }

        i++;

        if (no->filhos[i]->numChaves == (2 * ordem - 1)) {
            divideNo(no, i, no->filhos[i], ordem);
            if (reg.matricula > no->registros[i].matricula) {
                i++;
            }
        }

        insereNaoCheio(no->filhos[i], reg, ordem);
    }
}

// Função para dividir um nó
void divideNo(no *pai, int i, no *filho, int ordem) {
    no *novoFilho = alocaNo(ordem);
    novoFilho->folha = filho->folha;
    novoFilho->numChaves = ordem - 1;

    int j;
    for (j = 0; j < ordem - 1; j++) {
        novoFilho->registros[j] = filho->registros[j + ordem];
    }

    if (!filho->folha) {
        for (j = 0; j < ordem; j++) {
            novoFilho->filhos[j] = filho->filhos[j + ordem];
        }
    }

    filho->numChaves = ordem - 1;

    for (j = pai->numChaves; j >= i + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }

    pai->filhos[i + 1] = novoFilho;

    for (j = pai->numChaves - 1; j >= i; j--) {
        pai->registros[j + 1] = pai->registros[j];
    }

    pai->registros[i] = filho->registros[ordem - 1];
    pai->numChaves++;
}

// Função para buscar um elemento na B-tree
registro *buscar(bt *arv, int matricula) {
    no *raiz = arv->raiz;
    int i = 0;

    while (i < raiz->numChaves && matricula > raiz->registros[i].matricula) {
        i++;
    }

    if (i < raiz->numChaves && matricula == raiz->registros[i].matricula) {
        return &raiz->registros[i];
    } else if (raiz->folha) {
        return NULL;
    } else {
        return buscaElementoNo(raiz->filhos[i], matricula);
    }
}

// Função para buscar um elemento em um nó
registro *buscaElementoNo(no *no, int matricula) {
    int i = 0;

    while (i < no->numChaves && matricula > no->registros[i].matricula) {
        i++;
    }

    if (i < no->numChaves && matricula == no->registros[i].matricula) {
        return &no->registros[i];
    } else if (no->folha) {
        return NULL;
    } else {
        return buscaElementoNo(no->filhos[i], matricula);
    }
}

// Função para remover um elemento na B-tree
void removerElemento(bt *arv, int matricula) {
    no *raiz = arv->raiz;

    if (raiz->numChaves == 0) {
        printf("A árvore está vazia.\n");
        return;
    }

    removerChave(raiz, matricula, arv->ordem);

    if (raiz->numChaves == 0) {
        if (raiz->folha) {
            arv->raiz = NULL;
        } else {
            arv->raiz = raiz->filhos[0];
            arv->raiz->pai = NULL;
        }
        free(raiz);
    }
}

// Função para remover uma chave em um nó
void removerChave(no *no, int matricula, int ordem) {
    int i = 0;

    while (i < no->numChaves && matricula > no->registros[i].matricula) {
        i++;
    }

    if (i < no->numChaves && matricula == no->registros[i].matricula) {
        removerElementoNo(no, i, ordem);
    } else if (!no->folha) {
        if (no->filhos[i]->numChaves < ordem) {
            preencherNo(no, i);
        }
        removerChave(no->filhos[i], matricula, ordem);
    }
}

void preencherNo(no* no, int indice) {
    // Move os registros e filhos para a esquerda
    for (int i = indice + 1; i < no->numChaves; i++) {
        no->registros[i - 1] = no->registros[i];
        no->filhos[i] = no->filhos[i + 1];
    }

    // Decrementa o número de chaves do nó
    no->numChaves--;
}

// Função para remover um elemento de um nó
void removerElementoNo(no *no, int indice, int ordem) {
    if (no->folha) {
        for (int i = indice; i < no->numChaves - 1; i++) {
            no->registros[i] = no->registros[i + 1];
        }
        no->numChaves--;
    } else {
        registro *elemento = &no->registros[indice];

        if (no->filhos[indice]->numChaves >= ordem) {
            registro *predescessor = encontraPredescessor(no, indice);
            no->registros[indice] = *predescessor;
            removerChave(no->filhos[indice], predescessor->matricula, ordem);
        } else if (no->filhos[indice + 1]->numChaves >= ordem) {
            registro *sucessor = encontraSucessor(no, indice);
            no->registros[indice] = *sucessor;
            removerChave(no->filhos[indice + 1], sucessor->matricula, ordem);
        } else {
            merge(no, indice, ordem);
            removerChave(no->filhos[indice], elemento->matricula, ordem);
        }
    }
}

// Função para encontrar o predecessor de um elemento
registro *encontraPredescessor(no *no, int indice) {
    no = no->filhos[indice];

    while (!no->folha) {
        no = no->filhos[no->numChaves];
    }

    return &no->registros[no->numChaves - 1];
}

// Função para encontrar o sucessor de um elemento
registro *encontraSucessor(no *no, int indice) {
    no = no->filhos[indice + 1];

    while (!no->folha) {
        no = no->filhos[0];
    }

    return &no->registros[0];
}

// Função para realizar uma rotação à esquerda
void rotacaoEsq(no *pai, int indice, int ordem) {
    no *filho = pai->filhos[indice];
    no *irmao = pai->filhos[indice + 1];

    filho->registros[filho->numChaves] = pai->registros[indice];
    filho->numChaves++;

    if (!filho->folha) {
        filho->filhos[filho->numChaves] = irmao->filhos[0];
    }

    pai->registros[indice] = irmao->registros[0];

    for (int i = 0; i < irmao->numChaves - 1; i++) {
        irmao->registros[i] = irmao->registros[i + 1];
        irmao->filhos[i] = irmao->filhos[i + 1];
    }

    if (!irmao->folha) {
        irmao->filhos[irmao->numChaves - 1] = irmao->filhos[irmao->numChaves];
    }

    irmao->numChaves--;
}

// Função para realizar uma rotação à direita
void rotacaoDir(no *pai, int indice, int ordem) {
    no *filho = pai->filhos[indice];
    no *irmao = pai->filhos[indice - 1];

    for (int i = filho->numChaves - 1; i >= 0; i--) {
        filho->registros[i + 1] = filho->registros[i];
        filho->filhos[i + 1] = filho->filhos[i];
    }

    filho->filhos[0] = irmao->filhos[irmao->numChaves];
    filho->registros[0] = pai->registros[indice - 1];

    pai->registros[indice - 1] = irmao->registros[irmao->numChaves - 1];

    filho->numChaves++;
    irmao->numChaves--;
}

// Função para realizar o merge de dois nós
void merge(no *pai, int indice, int ordem) {
    no *filho = pai->filhos[indice];
    no *irmao = pai->filhos[indice + 1];

    filho->registros[filho->numChaves] = pai->registros[indice];
    filho->numChaves++;

    for (int i = 0; i < irmao->numChaves; i++) {
        filho->registros[filho->numChaves + i] = irmao->registros[i];
        filho->filhos[filho->numChaves + i] = irmao->filhos[i];
    }

    if (!filho->folha) {
        filho->filhos[filho->numChaves + irmao->numChaves] = irmao->filhos[irmao->numChaves];
    }

    for (int i = indice + 1; i < pai->numChaves; i++) {
        pai->registros[i - 1] = pai->registros[i];
        pai->filhos[i] = pai->filhos[i + 1];
    }

    filho->numChaves += irmao->numChaves;
    pai->numChaves--;

    free(irmao);
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