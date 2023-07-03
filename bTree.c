// <-- Bibliotecas e extensões -->
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bTree.h"

// <-- Estrutura do nó -->
struct no {
    int* chaves;
    registro* registros;
    no** ponteiros;
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

// <-- Estrutura da árvore -->
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

	// Aloca um novo nó
    no* novo = (no*) malloc(sizeof(no));

	// Verifica se houve erro
    if (novo == NULL) {
        return NULL;
	
    }

	// Aloca a quantidade de chaves
	// baseado na ordem
    novo->registros = (registro*) malloc(sizeof(registro) * (ordem - 1));

	// Verifica se houve erro
    if (novo->registros == NULL) {
        return NULL;
	
    }

	// Aloca a quantidade de ponteiros
	// baseado na ordem
    novo->ponteiros = (no**)malloc(sizeof(no*) * (ordem));

	// Verifica se houve erro
    if (novo->ponteiros == NULL) {
        return NULL;
	
    }

	// Percorre o nó apontando todos
	// os ponteiros para NULL
    for (int i = 0; i < ordem; i++) {
        novo->ponteiros[i] = NULL;
	
    }

	// Atribui valores para o nó
    novo->ocupacao = 0;
	  novo->pai = NULL;
    novo->folha = 1;

	// Retorna o nó
    return novo;

}


//Função que aloca e inicializa uma nova árvore com uma raiz alocada, porém vazia.
//Árvore B tradicional. A ordem m deve ser sempre par. Caso contrário, retorna NULL.
bt* criaArvore(int m) {
    bt* arvore = (bt*) malloc(sizeof(bt));

    // Verificação de erro
    if (arvore == NULL) {
        return NULL;

    }

    // Define a ordem da árvore
    arvore->ordem = m;

    // Aloca um novo nó que será
    // a raiz da árvore
    arvore->raiz = alocaNo(m);

    // Verificação de erro
    if (arvore->raiz == NULL) {
        return NULL;

    }

    // Retorna a árvore
    return arvore;
}


//Função que retorna a raiz da árvore
no* retornaRaiz(bt* arvore) {
	return arvore->raiz;
	
}

//Função recursiva que retorna o nó onde o elemento está na árvore
no* buscaElemento(no* atual, int valor) {
	
	// Verifica se a árvore está vazia
	if (atual == NULL) {
		return NULL;
	
	}

	// Variável auxiliar
	// usada como contador
	int aux = 0;

	// Variável usada para
	// armazenar a quantidade
	// de elementos
	int qtd = atual->ocupacao;

	// Percorre a árvore enquanto o contador
	// for menor que a quantidade de elementos e
	// enquanto o parâmetro valor for maior que
	// o valor da chave de posição aux
	while ((atual->registros[aux].matricula < valor) && (aux < qtd)) {
		aux++;
	
	}

	// Verifica se o contador é menor do que
	// a quantidade de elementos da árvore e
	// se o parâmetro valor é igual ao valor
	// da chave de posição aux
	if ((valor == atual->registros[aux].matricula) && (aux < qtd)) {
		return atual;
	
	}

	// Verifica se o nó é folha	
    if (atual->folha == 1) {
		return NULL;
	
	}

	// A função chama a si mesma (recursiva) passando
	// os ponteiros e o valor como parâmetros
    return buscaElemento(atual->ponteiros[aux], valor);

}

int insereElemento(bt* arvore, int valor, struct registro* reg) {
    // Define um ponteiro para
    // a raiz da árvore
    no* aux = arvore->raiz;

    // Variável usada para
    // armazenar a quantidade
    // de elementos
    int qtd = aux->ocupacao;

    // Variável usada para
    // armazenar a ordem
    int ord = arvore->ordem - 1;

    // Verifica se o ponteiro inicial
    // é diferente de NULL e se a quantidade
    // de elementos é menor ou igual à ordem
    // da árvore
    if ((aux->ponteiros[0] == NULL) && (ord >= qtd)) {
        // Enquanto a quantidade de elementos
        // for menor ou igual à ordem, compara o
        // valor passado como parâmetro
        while (ord >= qtd) {
            // Encontra o lugar onde deve
            // ser realizada a inserção
            if (aux->registros[qtd].matricula > valor) {
                aux->registros[qtd] = *reg;
                aux->ocupacao++;
                return 1;
            }
            // Incrementa a ocupação
            qtd++;
        }
    } else {
        // Percorre enquanto o nó
        // não for um nó folha
        while (aux->folha == 0) {
            // Variável para
            // auxiliar na busca
            int cont = 0;
            // Enquanto o contador for menor do que
            // a ocupação do nó e o valor passado
            // como parâmetro for maior ou igual
            // ao valor das chaves do nó
            while ((valor > aux->registros[cont].matricula) && (aux->ocupacao > cont)) {
                cont++;
            }
            aux = aux->ponteiros[cont];
        }
    }

    // Verifica se a ocupação
    // do nó é igual à ordem,
    // se verdade, executa o split
    if (aux->ocupacao == ord) {
        aux = split(arvore, aux, valor);
    }

    // "Reseta" a variável usada para
    // armazenar a quantidade
    // de elementos
    qtd = aux->ocupacao;

    // Percorre o vetor de chaves
    // para organizar as posições
    while ((aux->registros[qtd - 1].matricula > valor) && (qtd > 0)) {
        aux->registros[qtd] = aux->registros[qtd - 1];
        qtd--;
    }

    // Atribui o parâmetro
    // valor à posição qtd
    // do vetor de chaves
    // do nó atual
    aux->registros[qtd].matricula = valor;

    // Incrementa a ocupação
    aux->ocupacao++;

    // Se a inserção for
    // bem sucedida, retorna 1
    return 1;
}

//Função que realiza o split no noDesbal. A variável valor guarda o elemento que está sendo inserido (e que causou o split)
//Função chamada pela função insereElemento
//Sempre sobe o elemento do meio para o pai (m é sempre par).
//Caso o pai esteja cheio, a função se chama recursivamente.
no* split(bt* arvore, no* noDesbal, int valor) {

    // Variável para
    // usar como contador
    int i = 0;

    // Ponteiro auxiliar
    // para armazenar a
    // referência ao pai
    // do nó desbalanceado
    no* pai = noDesbal->pai;

	// Aloca um novo nó
    no* novo = alocaNo(arvore->ordem);

    // Verificação de erro
    if (novo == NULL) {
        return NULL;
			
    }

    // Atribui os valores
    // ao novo nó
    novo->folha = noDesbal->folha;
    novo->pai = noDesbal->pai;

    // Variável para armazenar
    // o valor da chave que está
    // no meio da árvore
    int chave = noDesbal->registros[(arvore->ordem - 1) / 2].matricula;

    // Aux recebe meio + 1
    int aux = ((arvore->ordem - 1) / 2) + 1;

    // Enquanto o auxiliar for menor
    // do que o meio da árvroe
    while (arvore->ordem - 1 > aux) {

		// Decrementa a ocupação do
		// nó desbalanceado
        noDesbal->ocupacao--;

		// Incrementa a ocupação do
		// novo nó
        novo->ocupacao++;
		
        // Altera os valores
        // do vetor de chaves
        // do novo nó
        novo->registros[i].matricula = noDesbal->registros[aux].matricula;

        // Verifica se o novo nó
        // é uma folha
        if (novo->folha == 0) {
            
            // Altera os valores do vetor de ponteiros
            // do novo nó e aponta os ponteiros do
            // nó desbalanceado para o novo nó
            novo->ponteiros[i] = noDesbal->ponteiros[aux];
            noDesbal->ponteiros[aux]->pai = novo;

        }

        // Ponteiros do nó desbalanceado
        // apontam para NULL
        noDesbal->ponteiros[aux] = NULL;

		// Incrementa os contadores
        aux++;
        i++;

    }

    // Verifica se o novo nó
    // é uma folha
    if (novo->folha == 0) {

        // Altera os valores do vetor de ponteiros
        // do novo nó e aponta os ponteiros do
        // nó desbalanceado para o novo nó
        novo->ponteiros[i] = noDesbal->ponteiros[aux];
        noDesbal->ponteiros[aux]->pai = novo;

    }

    // Ponteiro de posição
    // aux do novo nó aponta
    // para NULL
    novo->ponteiros[aux] = NULL;

    // Verifica se o
    // nó pai é diferente
    // de NULL
    if (pai != NULL) {

        // Variável recebe a
        // ocupação do ponteiro pai
        i = pai->ocupacao;

        // Se a ocupação for igual a ordem 
        // da árvore - 1, chama a função recursivamente
        if (arvore->ordem - 1 == i) {
            pai = split(arvore, pai, chave);
            i = pai->ocupacao;

        }

        // Percorre o vetor de chaves e ponteiros
        // do nó pai e altera os valores
        while ((pai->registros[i - 1].matricula > chave) && (i > 0)) {
            pai->registros[i].matricula = pai->registros[i - 1].matricula;
            pai->ponteiros[i + 1] = pai->ponteiros[i];
            i--;

        }

        // Atribui o valor de aux
        // a posição i do vetor de chaves
        pai->registros[i].matricula = chave;

        // Atribui o valor de novo
        // para a posição i+1 do vetor de ponteiros
        pai->ponteiros[i + 1] = novo;

        // Incrementa ocupação
        // do nó pai
        pai->ocupacao++;

        // Decrementa a ocupação
        // do nó desbalanceado
        noDesbal->ocupacao--;

        // Atualiza a referência
        // do pai do novo nó
        novo->pai = pai;

    // Pai é NULL
    } else {

		// Aloca um novo nó
        no* raiz = alocaNo(arvore->ordem);

        // Verificação de erro
        if (raiz == NULL) {
            return NULL;
                
        }

        // Atribui valores
        // ao novo nó
        raiz->registros[0].matricula = chave;
        raiz->pai = NULL;
        raiz->folha = 0;
        raiz->ocupacao++;

        // Decrementa a ocupação
        // do nó desbalanceado
        noDesbal->ocupacao--;

        // Altera o valor armazenado
        // no vetor das duas primeiras
        // posições de ponteiros do
        // nó raiz
        raiz->ponteiros[0] = noDesbal;
        raiz->ponteiros[1] = novo;

        // Altera o pai do nó
        // desbalanceado para a raiz
        noDesbal->pai = raiz;

        // Altera o pai do novo nó
        // para a raiz
        novo->pai = raiz;

        // Altera a raiz da árvore
        // para a nova razz
        arvore->raiz = raiz;
		
    }

    // Compara o parâmetro valor
    // com a variável aux
    if (valor > chave){
        return novo;

    } else {
        return noDesbal;

    }

}


//Função que remove um elemento da B-Tree
//Na remoção por cópia, usar o predecessor
//No caso de rotação e merge, tentar primeiro o irmão da esquerda e depois o da direita
//Se houve a remoção, retorna 1. Caso contrário, retorna -1
int removeElemento(bt* arvore, int valor) {

    // Ponteiro usado para buscar
    // o elemento que será removido
    no* remove = buscaElemento(arvore->raiz, valor);

    // Verifica se o elemento
    // foi encontrado ou não
    if (remove == NULL) {
        return -1;

    }

    // Ponteiro auxiliar
    no* aux;

    // Variável auxiliar usada
    // como contador
    int i = 0;

    // Verifica se o nó
    // é do "tipo folha"
    if (remove->folha == 0) {

        // Percorre enquanto não i
        // for menor que a ocupação do nó
        // e o parâmetro valor for maior
        // que o valor armazenado na posição
        // i do vetor de chaves
        while ((valor > remove->registros[i].matricula) && (remove->ocupacao > i)) {
             i++;
        }

        // Variável auxiliar aponta
        // para o valor armazenado
        // na posição i do vetor
        // de ponteiros
        aux = remove->ponteiros[i];

        // Percorre o vetor de ponteiros
        // do nó auxiliar até chegar ao NULL
        while (aux->ponteiros[aux->ocupacao - 1] != NULL) {
            aux = aux->ponteiros[aux->ocupacao];

        }

        // Atualiza os valores do vetor
        // de chaves do elemento que será removido
        remove->registros[i].matricula = aux->registros[aux->ocupacao - 1].matricula;
        remove = aux;

        // Variável "valor" recebe
        // o valor armazenado no
        // vetor de chaves do
        // elemento que será removido 
        valor = remove->registros[remove->ocupacao - 1].matricula;

    }

    // Percorre enquanto não i
    // for menor que a ocupação do nó
    // e o parâmetro valor for maior
    // que o valor armazenado na posição
    // i do vetor de chaves
    while ((valor > remove->registros[i].matricula) && (remove->ocupacao > i)) {
        i++;

    }

    // Percorre o vetor de chaves
    // do elemento que será removido
    // para alterar a posição das chaves
    while (remove->ocupacao > i) {
        remove->registros[i].matricula = remove->registros[i + 1].matricula;
        i++;

    }

    // Decrementa a ocupação
    // do elemento
    remove->ocupacao--;

	// Reseta o contador i
    // para zero
    i = 0;

    // Variável usada para
    // indicar o meio da árvore
    int meio = (arvore->ordem - 1) / 2;

    // Se a ocupação do elemento que será
    // removido for menor que o meio da árvore
    if (meio > remove->ocupacao) {

        // Ponteiro pai armazena
        // a referência para o pai
        // do elemento que será removido
        no* pai = remove->pai;

        // Percorre enquanto não i
        // for menor que a ocupação do nó pai
        // e o parâmetro valor for maior
        // que o valor armazenado na posição
        // i do vetor de chaves do pai
        while ((valor > pai->registros[i].matricula) && (pai->ocupacao > i)) {
            i++;
        
        }

        // Verifica a necessidade de 
        // efetuar a rotação ou merge
        // Verifica se i é maior que zero
        // e se a ocupação armazenada na posição i-1 do
        // vetor de ponteiros do nó pai é maior que o meio
        if ((pai->ponteiros[i - 1]->ocupacao > meio) && (i > 0)) {
            rotacao(remove, pai->ponteiros[i - 1], i);

        // Verifica se i é menor que a ocupação do pai
        // e se a ocupação armazenada na posição i+1 do
        // vetor de ponteiros do nó pai é maior que o meio
        } else if ((pai->ponteiros[i + 1]->ocupacao > meio) && (pai->ocupacao > i)) {
            rotacao(remove, pai->ponteiros[i + 1], i);

        // Caso nenhuma das duas condições anteriores
        // sejam satisfeitas, é feito um merge
        } else {
            merge(remove, i);

        }

    }

    // Remoção bem sucedida,
    // então retorna 1
    return 1;

}


//Função que implementa a rotação, levanto um elemento do pai para o nóDesbal e subindo um elemento do no irmão para o pai
// A variável posPai guarda a posição do ponteiro do pai que aponta para o nó noDesbal
void rotacao(no* noDesbal, no* irmao, int posPai) {
    
    // Ponteiro aponta para
    // o pai do nó irmão
    no* pai = irmao->pai;

    // Verifica se o valor armazenado no ponteiro
    // de posição posPai - 1 é igual ao nó irmão
    if (pai->ponteiros[posPai - 1] == irmao) {

        // Altera o valor armazenado no vetor chaves
        // do nó desbalanceado para o valor armazenado
        // no vetor chaves do nó pai de posição posPai - 1
        noDesbal->registros[noDesbal->ocupacao].matricula = pai->registros[posPai - 1].matricula;

        // Incrementa a ocupação do
        // nó desbalanceado
        noDesbal->ocupacao++;

        // Altera o valor armazenado na posição
        // posPai - 1 do vetor de chaves do pai
        pai->registros[posPai - 1].matricula = irmao->registros[irmao->ocupacao - 1].matricula;

        // Decrementa a ocupação
        // do nó irmão
        irmao->ocupacao--;

    } else {

        // Variável auxiliar
        int aux = irmao->ocupacao - 1;

        // Altera o valor armazenado no vetor chaves
        // do nó desbalanceado para o valor armazenado
        // no vetor chaves do nó pai de posição posPai
        noDesbal->registros[noDesbal->ocupacao].matricula = pai->registros[posPai].matricula;

        // Incrementa a ocupação do
        // nó desbalanceado
        noDesbal->ocupacao++;

        // Altera o valor armazenado na posição
        // posPai do vetor de chaves do pai
        pai->registros[posPai].matricula = irmao->registros[0].matricula;

        // Percorre o vetor de chaves e
        // ponteiros do irmão e altera a
        // posição de todos os valores
        while (aux > 0) {
            irmao->registros[aux - 1].matricula = irmao->registros[aux].matricula;
            irmao->ponteiros[aux - 1] = irmao->ponteiros[aux];

            aux--;
        }

        // Decrementa a ocupação
        // do nó irmão
        irmao->ocupacao--;

    }

}


//Função que implementa o merge do nó Desbal com seu irmão da esquerda ou da direita
//Se a variãvel posPai é maior que zero, o merge acontece com o irmão da esquerda
//Caso contrário, com o irmão da direita
no* merge(no* noDesbal, int posPai) {

    // Ponteiro aponta para
    // o pai do nó desbalanceado
    no* pai = noDesbal->pai;

	// Ponteiro do irmão
	no* irmao;

    // Variável para definir
    // o retorno
    int ret = 0;

    // Variável auxiliar
    // para contar
    int aux = 0;

    // Merge acontece com
    // irmão da esquerda
    if (posPai > 0) {

        // Ponteiro aponta para
        // o valor armazenado no vetor
        // de ponteiros do pai na posição posPai-1
        irmao = pai->ponteiros[posPai - 1];

        // Altera o valor armazenado
        // no vetor de chaves do irmão
        irmao->registros[irmao->ocupacao].matricula = pai->registros[posPai - 1].matricula;

        // Incrementa a ocupação
        // do irmão
        irmao->ocupacao++;

        // Loop enquanto aux for menor
        // que a ocupação do nó desbalanceado
        while (noDesbal->ocupacao > aux) {
            
            // Altera o valor armazenado nos vetores
            // de chaves e ponteiros do nó irmão para os armazenados
            // nos vetores de chaves e ponteiros do nó desbalanceado
            irmao->registros[irmao->ocupacao + aux].matricula = noDesbal->registros[aux].matricula;
            irmao->ponteiros[irmao->ocupacao + aux] = noDesbal->ponteiros[aux];

            // Incrementa a ocupação do irmão
            irmao->ocupacao++;

            // Incrementa o contador
            aux++;
			
        }

        // Contador aux recebe
        // o valor de posPai
        aux = posPai;

        // Variável ret = 0, retorna o irmão

    // Merge acontece com
    // irmão da direita
    } else {

        // Ponteiro aponta para
        // o valor armazenado no vetor
        // de ponteiros do pai na posição posPai+1
        irmao = pai->ponteiros[posPai + 1];

        // Altera o valor armazenado
        // no vetor de chaves do nó desbalanceado
        noDesbal->registros[noDesbal->ocupacao].matricula = pai->registros[posPai].matricula;

        // Incrementa a ocupação do irmão
        noDesbal->ocupacao++;

        // Loop enquanto aux for menor
        // que a ocupação do nó irmão
        while (irmao->ocupacao > aux) {
            
            // Altera o valor armazenado nos vetores
            // de chaves e ponteiros do nó desbalanceado para os armazenados
            // nos vetores de chaves e ponteiros do nó irmão
            noDesbal->registros[noDesbal->ocupacao + aux].matricula = irmao->registros[aux].matricula;
            noDesbal->ponteiros[noDesbal->ocupacao + aux] = irmao->ponteiros[aux];

            // Incrementa a ocupação do nó desbalanceado
            noDesbal->ocupacao++;

            // Incrementa o contador
            aux++;
        }

        // Contador aux recebe
        // o valor de posPai+1
        aux = posPai + 1;

        // Variável ret = 1, retorna o
        // nó desbalanceado
        ret++;

    }

    // Loop enquanto aux for menor
    // que a ocupação do nó pai
    while (pai->ocupacao > aux) {

        // Altera a posição dos valores
        // armazenados nos vetores de chaves e
        // ponteiros do nó pai
        pai->registros[aux - 1].matricula = pai->registros[aux].matricula;
        pai->ponteiros[aux] = pai->ponteiros[aux + 1];

        // Decrementa a ocupação do nó pai
        pai->ocupacao--;

        // Incrementa o contador
        aux++;

    }

    // Define o retorno que
    // será feito
    if (ret == 0){
        // Retorna o irmão
        return irmao;

    } else {
        // Retorna o nó desbalanceado
        return noDesbal;

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