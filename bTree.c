#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bTree.h"

struct no {
    registro* registros;
    no** filhos;
    no* pai;
    int folha;
    int ocupacao;

};

struct registro {
    int matricula;
    char nome[50];
    char dataNascimento[11];
    char email[50];
};

struct bt {
    int ordem;
    no* raiz;
};

// Função para ler os registros do arquivo e salvar na B-tree em memória
void lerRegistros(bt *arv, char *nomeArquivo) {
    FILE *arquivo;
    struct registro *reg = malloc(sizeof(struct registro));
    int matricula;
    char nome[50], dataNascimento[11], email[50];

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de registros.\n");
        return;
    }

    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^\n]\n", &matricula, nome, dataNascimento, email) == 4) {
        reg->matricula = matricula;
        strcpy(reg->nome, nome);
        strcpy(reg->dataNascimento, dataNascimento);
        strcpy(reg->email, email);

        // Salvar o registro na B-tree em memória
        insereElemento(arv, matricula, reg);
    }

    free(reg);
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

//Função que aloca e inicializa um novo nó
no* alocaNo(int ordem) {
    no* novo = (no*) malloc(sizeof(no));

    if (novo == NULL) {
        return NULL;
    }

    novo->registros = (registro*) malloc(sizeof(registro) * (ordem - 1));

    novo->filhos = (no**)malloc(sizeof(no*) * (ordem));

    if (novo->filhos == NULL) {
        return NULL;

    }

    for (int i = 0; i < ordem; i++) {
        novo->filhos[i] = NULL;

    }

    // Inicializa o nó
    novo->ocupacao = 0;
    novo->pai = NULL;
    novo->folha = 1;

    return novo;
}

bt* criaArvore(int ordem) {
    bt* arvore = (bt*) malloc(sizeof(bt));

    if (arvore == NULL) {
        return NULL;

    }

    arvore->ordem = ordem;
    arvore->raiz = alocaNo(ordem);

    if (arvore->raiz == NULL) {
        return NULL;
    }

    return arvore;
}

no* buscaElemento(no* atual, int valor) {
    if (atual == NULL) {
        return NULL;
    }

    int aux = 0;
    int qtd = atual->ocupacao;

    while ((atual->registros[aux].matricula < valor) && (aux < qtd)) {
        aux++;
    }

    if ((valor == atual->registros[aux].matricula) && (aux < qtd)) {
        return atual;
    }

    if (atual->folha == 1) {
        return NULL;
    }

    return buscaElemento(atual->filhos[aux], valor);
}

int insereElemento(bt* arvore, int valor, struct registro* reg) {
    no* aux = arvore->raiz;

    int qtd = aux->ocupacao, tam = arvore->ordem - 1;

    if ((aux->filhos[0] == NULL) && (tam >= qtd)) {
        while (tam >= qtd) {
            if (aux->registros[qtd].matricula > valor) {
                aux->registros[qtd] = *reg;
                aux->ocupacao++;
                return 1;
            }
            qtd++;
        }
    } else {
        while (aux->folha == 0) {
            int cont = 0;
            // Percorre o vetor de chaves
            while ((valor > aux->registros[cont].matricula) && (aux->ocupacao > cont)) {
                cont++;
            }
            aux = aux->filhos[cont];
        }
    }

    // Verifica se o nó está cheio
    if (aux->ocupacao == tam) {
        aux = split(arvore, aux, valor);
    }

    qtd = aux->ocupacao;

    while ((aux->registros[qtd - 1].matricula > valor) && (qtd > 0)) {
        aux->registros[qtd] = aux->registros[qtd - 1];
        qtd--;
    }

    aux->registros[qtd].matricula = valor;

    aux->ocupacao++;

    return 1;
}

no* split(bt* arvore, no* noDesbal, int valor) {
    int i = 0;
    no* pai = noDesbal->pai;
    no* novo = alocaNo(arvore->ordem);

    if (novo == NULL) {
        return NULL;
    }

    novo->folha = noDesbal->folha;
    novo->pai = noDesbal->pai;

    int chave = noDesbal->registros[(arvore->ordem - 1) / 2].matricula;
    int aux = ((arvore->ordem - 1) / 2) + 1;

    // Copia os registros do nó desbalanceado
    while (arvore->ordem - 1 > aux) {
        noDesbal->ocupacao--;
        novo->ocupacao++;
        novo->registros[i] = noDesbal->registros[aux];

        if (novo->folha == 0) {
            novo->filhos[i] = noDesbal->filhos[aux];
            noDesbal->filhos[aux]->pai = novo;
        }

        noDesbal->filhos[aux] = NULL;

        aux++;
        i++;
    }

    // Copia os filhos do nó desbalanceado
    if (novo->folha == 0) {
        novo->filhos[i] = noDesbal->filhos[aux];
        noDesbal->filhos[aux]->pai = novo;
    }

    novo->filhos[aux] = NULL;

    if (pai != NULL) {
        i = pai->ocupacao;

        if (arvore->ordem - 1 == i) {
            pai = split(arvore, pai, chave);
            i = pai->ocupacao;
        }

        while ((pai->registros[i - 1].matricula > chave) && (i > 0)) {
            pai->registros[i] = pai->registros[i - 1];
            pai->filhos[i + 1] = pai->filhos[i];
            i--;

        }

        pai->registros[i].matricula = chave;
        pai->filhos[i + 1] = novo;
        pai->ocupacao++;

        noDesbal->ocupacao--;

        novo->pai = pai;

    } else {
        no* raiz = alocaNo(arvore->ordem);

        if (raiz == NULL) {
            return NULL;
        }

        raiz->registros[0].matricula = chave;
        raiz->pai = NULL;
        raiz->folha = 0;
        raiz->ocupacao++;

        noDesbal->ocupacao--;

        raiz->filhos[0] = noDesbal;
        raiz->filhos[1] = novo;

        noDesbal->pai = raiz;

        novo->pai = raiz;

        arvore->raiz = raiz;
    }

    if (valor > chave){
        return novo;
    } else {
        return noDesbal;
    }
}

int removeElemento(bt* arvore, int valor) {
    no* remove = buscaElemento(arvore->raiz, valor);
    if (remove == NULL) {
        return -1;
    }

    no* aux;
    int i = 0;

    if (remove->folha == 0) {
        while ((valor > remove->registros[i].matricula) && (remove->ocupacao > i)) {
            i++;
        }

        aux = remove->filhos[i];

        while (aux->filhos[aux->ocupacao - 1] != NULL) {
            aux = aux->filhos[aux->ocupacao];
        }

        remove->registros[i].matricula = aux->registros[aux->ocupacao - 1].matricula;
        remove = aux;

        valor = remove->registros[remove->ocupacao - 1].matricula;
    }

    while ((valor > remove->registros[i].matricula) && (remove->ocupacao > i)) {
        i++;
    }

    while (remove->ocupacao > i) {
        remove->registros[i].matricula = remove->registros[i + 1].matricula;
        i++;
    }

    remove->ocupacao--;

    i = 0;
    int meio = (arvore->ordem - 1) / 2;

    if (meio > remove->ocupacao) {
        no* pai = remove->pai;
        while ((valor > pai->registros[i].matricula) && (pai->ocupacao > i)) {
            i++;
        }

        if ((pai->filhos[i - 1]->ocupacao > meio) && (i > 0)) {
            rotacao(remove, pai->filhos[i - 1], i);
        } else if ((pai->filhos[i + 1]->ocupacao > meio) && (pai->ocupacao > i)) {
            rotacao(remove, pai->filhos[i + 1], i);
        } else {
            merge(remove, i);
        }
    }

    return 1;
}

void rotacao(no* noDesbal, no* irmao, int posPai) {
    no* pai = irmao->pai;

    if (pai->filhos[posPai - 1] == irmao) {
        noDesbal->registros[noDesbal->ocupacao].matricula = pai->registros[posPai - 1].matricula;
        noDesbal->ocupacao++;
        pai->registros[posPai - 1].matricula = irmao->registros[irmao->ocupacao - 1].matricula;
        irmao->ocupacao--;
    } else {
        int aux = irmao->ocupacao - 1;
        noDesbal->registros[noDesbal->ocupacao].matricula = pai->registros[posPai].matricula;
        noDesbal->ocupacao++;
        pai->registros[posPai].matricula = irmao->registros[0].matricula;

        while (aux > 0) {
            irmao->registros[aux - 1].matricula = irmao->registros[aux].matricula;
            irmao->filhos[aux - 1] = irmao->filhos[aux];
            aux--;
        }

        irmao->ocupacao--;
    }
}

no* merge(no* noDesbal, int posPai) {
    no* pai = noDesbal->pai;  // Pai do nó desbalanceado
    no* irmao;  // Ponteiro do irmão
    int ret = 0;  // Variável para definir o retorno
    int aux = 0;  // Variável auxiliar para contar

    // Merge acontece com irmão da esquerda
    if (posPai > 0) {
        irmao = pai->filhos[posPai - 1];  // Irmão é o filho do pai na posição posPai-1

        // Adiciona a chave do pai no irmão
        irmao->registros[irmao->ocupacao].matricula = pai->registros[posPai - 1].matricula;
        irmao->ocupacao++;

        // Copia as chaves e filhos do nó desbalanceado para o irmão
        while (noDesbal->ocupacao > aux) {
            irmao->registros[irmao->ocupacao + aux].matricula = noDesbal->registros[aux].matricula;
            irmao->filhos[irmao->ocupacao + aux] = noDesbal->filhos[aux];
            irmao->ocupacao++;
            aux++;
        }

        aux = posPai;
        // Retorna o irmão (ret = 0)

        // Merge acontece com irmão da direita
    } else {
        irmao = pai->filhos[posPai + 1];  // Irmão é o filho do pai na posição posPai+1

        // Adiciona a chave do pai no nó desbalanceado
        noDesbal->registros[noDesbal->ocupacao].matricula = pai->registros[posPai].matricula;
        noDesbal->ocupacao++;

        // Copia as chaves e filhos do irmão para o nó desbalanceado
        while (irmao->ocupacao > aux) {
            noDesbal->registros[noDesbal->ocupacao + aux].matricula = irmao->registros[aux].matricula;
            noDesbal->filhos[noDesbal->ocupacao + aux] = irmao->filhos[aux];
            noDesbal->ocupacao++;
            aux++;
        }

        aux = posPai + 1;
        ret++;  // Retorna o nó desbalanceado
    }

    // Remove a chave do pai e os filhos deslocando as posições
    while (pai->ocupacao > aux) {
        pai->registros[aux - 1].matricula = pai->registros[aux].matricula;
        pai->filhos[aux] = pai->filhos[aux + 1];
        pai->ocupacao--;
        aux++;
    }

    // Define o retorno
    if (ret == 0) {
        return irmao;  // Retorna o irmão
    } else {
        return noDesbal;  // Retorna o nó desbalanceado
    }
}

no* getRaiz(bt *tree){
    return tree->raiz;
}

void buscarRegistro(int matricula) {
    FILE *arquivo;
    registro registro;

    arquivo = fopen("registros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de registros.\n");
        return;
    }

    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^\n]\n", &registro.matricula, registro.nome, registro.dataNascimento, registro.email) == 4) {
        if (registro.matricula == matricula) {
            break;
        }
    }

    fclose(arquivo);
}