/*

        Instituto de Matemática e Computação - Universidade Federal de Itajubá
   (UNIFEI)

        [DISCIPLINA]
        Algoritmo e Estrutura de Dados II
        Profa. Vanessa Souza

        [ASSUNTO]
    	Árvore B

        [DATA]
        18/07/2022

        [ALUNOS]
        Matheus Luz de Faria (2020032426)
        Thais Danieli Branco de Souza (2021001228)

*/


// <-- Bibliotecas e extensões -->
#include <stdio.h>
#include <stdlib.h>
#include "btree.h"


// <-- Estrutura do nó -->
struct no {
    int* chaves;
    no** ponteiros;
    no* pai;
    int folha;
    int ocupacao;

};


// <-- Estrutura da árvore -->
struct btree {
    int ordem;
    no* raiz;

};


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
    novo->chaves = (int*) malloc(sizeof(int) * (ordem - 1));

	// Verifica se houve erro
    if (novo->chaves == NULL) {
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
btree* criaArvore(int m) {

	// Verifica se a ordem é par
	// através do resto da divisão
	// Se o resto da divisão for zero,
	// significa que a ordem é par
    if (m % 2 == 0) {

		// Cria a árvore
        btree* arvore = (btree*) malloc(sizeof(btree));

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

	// Caso o resto da divisão seja diferente
	// de zero, deve retornar NULL
    } else {
        return NULL;
		
    }

}


//Função que retorna a raiz da árvore
no* retornaRaiz(btree* arvore) {
	return arvore->raiz;
	
}


//Função recursiva que imprime a árvore por profundidade
//Raiz, filho da esquerda até chegar na folha. E sobe imprimindo os filhos em sequência
void imprimeArvore(no* atual, int filho) {

	// Variável auxiliar
	int i = 0;
	
	// Verifica se a árvore está vazia
	if (atual == NULL) {
		return;
	
	}

	// Variável auxiliar armazena
	// a quantidade de elementos
	int aux = atual->ocupacao;

	// Verifica se o nó usado como
	// parâmetro é folha ou não
	// quando folha = 1, nó é folha
    if (atual->folha == 1) {

		// Percorre as chaves do nó
		// imprimindo uma a uma
		for (; i < aux; i++) {
            printf("%d  ", atual->chaves[i]);
		
        }
        printf("\n");

	// Se o nó não for folha
    } else {

		// Percorre as chaves do nó
		// imprimindo uma a uma
        for (; i < aux; i++) {
            printf("%d  ", atual->chaves[i]);
		
        }
        printf("\n");

		// Percorre os ponteiros do nó
		// imprimindo um a um
		i = 0;
		while (i <= aux) {
			imprimeArvore(atual->ponteiros[i], i);
			i++;
			
		}
	
    }

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
	while ((atual->chaves[aux] < valor) && (aux < qtd)) {
		aux++;
	
	}

	// Verifica se o contador é menor do que
	// a quantidade de elementos da árvore e
	// se o parâmetro valor é igual ao valor
	// da chave de posição aux
	if ((valor == atual->chaves[aux]) && (aux < qtd)) {
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


//Função que insere um novo elemento na árvore.
//Encontra a folha correta, realiza a inserção em árvore B tradicional
//Ou seja, se a folha estiver cheia, primeiro realiza o split e depois insere
//Se houve a inserção, retorna 1. Caso contrário, retorna -1
int insereElemento(btree* arvore, int valor) {
    
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
    // de elementos é menor do que a ordem
    // da árvore
    if ((aux->ponteiros[0] == NULL) && (ord > qtd)) {

	    // Enquanto a quantidade de elementos
		// for menor que a ordem, compara o
        // valor passado como parâmetro
        while (ord > qtd) {
			
            // Encontra o lugar onde deve
            // ser realizada a inserção
            if (aux->chaves[qtd] > valor) {
                aux->chaves[qtd] = valor;
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
			while ((valor > aux->chaves[cont]) && (aux->ocupacao > cont)) {
                cont++;

            }

            aux = aux->ponteiros[cont];

        }

    }

    // Verifica se a ocupação
    // do nó é igual a ordem,
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
    while ((aux->chaves[qtd - 1] > valor) && (qtd > 0)) {
        aux->chaves[qtd] = aux->chaves[qtd - 1];
        qtd--;
    
    }

    // Atribui o parâmetro
    // valor a posição qtd
    // do vetor de chaves
    // do nó atual
    aux->chaves[qtd] = valor;

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
no* split(btree* arvore, no* noDesbal, int valor) {

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
    int chave = noDesbal->chaves[(arvore->ordem - 1) / 2];

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
        novo->chaves[i] = noDesbal->chaves[aux];

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
        while ((pai->chaves[i - 1] > chave) && (i > 0)) {
            pai->chaves[i] = pai->chaves[i - 1];
            pai->ponteiros[i + 1] = pai->ponteiros[i];
            i--;

        }

        // Atribui o valor de aux
        // a posição i do vetor de chaves
        pai->chaves[i] = chave;

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
        raiz->chaves[0] = chave;
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
int removeElemento(btree* arvore, int valor) {

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
        while ((valor > remove->chaves[i]) && (remove->ocupacao > i)) {
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
        remove->chaves[i] = aux->chaves[aux->ocupacao - 1];
        remove = aux;

        // Variável "valor" recebe
        // o valor armazenado no
        // vetor de chaves do
        // elemento que será removido 
        valor = remove->chaves[remove->ocupacao - 1];

    }

    // Percorre enquanto não i
    // for menor que a ocupação do nó
    // e o parâmetro valor for maior
    // que o valor armazenado na posição
    // i do vetor de chaves
    while ((valor > remove->chaves[i]) && (remove->ocupacao > i)) {
        i++;

    }

    // Percorre o vetor de chaves
    // do elemento que será removido
    // para alterar a posição das chaves
    while (remove->ocupacao > i) {
        remove->chaves[i] = remove->chaves[i + 1];
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
        while ((valor > pai->chaves[i]) && (pai->ocupacao > i)) {
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
        noDesbal->chaves[noDesbal->ocupacao] = pai->chaves[posPai - 1];

        // Incrementa a ocupação do
        // nó desbalanceado
        noDesbal->ocupacao++;

        // Altera o valor armazenado na posição
        // posPai - 1 do vetor de chaves do pai
        pai->chaves[posPai - 1] = irmao->chaves[irmao->ocupacao - 1];

        // Decrementa a ocupação
        // do nó irmão
        irmao->ocupacao--;

    } else {

        // Variável auxiliar
        int aux = irmao->ocupacao - 1;

        // Altera o valor armazenado no vetor chaves
        // do nó desbalanceado para o valor armazenado
        // no vetor chaves do nó pai de posição posPai
        noDesbal->chaves[noDesbal->ocupacao] = pai->chaves[posPai];

        // Incrementa a ocupação do
        // nó desbalanceado
        noDesbal->ocupacao++;

        // Altera o valor armazenado na posição
        // posPai do vetor de chaves do pai
        pai->chaves[posPai] = irmao->chaves[0];

        // Percorre o vetor de chaves e
        // ponteiros do irmão e altera a
        // posição de todos os valores
        while (aux > 0) {
            irmao->chaves[aux - 1] = irmao->chaves[aux];
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
        irmao->chaves[irmao->ocupacao] = pai->chaves[posPai - 1];

        // Incrementa a ocupação
        // do irmão
        irmao->ocupacao++;

        // Loop enquanto aux for menor
        // que a ocupação do nó desbalanceado
        while (noDesbal->ocupacao > aux) {
            
            // Altera o valor armazenado nos vetores
            // de chaves e ponteiros do nó irmão para os armazenados
            // nos vetores de chaves e ponteiros do nó desbalanceado
            irmao->chaves[irmao->ocupacao + aux] = noDesbal->chaves[aux];
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
        noDesbal->chaves[noDesbal->ocupacao] = pai->chaves[posPai];

        // Incrementa a ocupação do irmão
        noDesbal->ocupacao++;

        // Loop enquanto aux for menor
        // que a ocupação do nó irmão
        while (irmao->ocupacao > aux) {
            
            // Altera o valor armazenado nos vetores
            // de chaves e ponteiros do nó desbalanceado para os armazenados
            // nos vetores de chaves e ponteiros do nó irmão
            noDesbal->chaves[noDesbal->ocupacao + aux] = irmao->chaves[aux];
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
        pai->chaves[aux - 1] = pai->chaves[aux];
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


//Função que lê dados do arquivo nomeArquivo e os insere ou remove da B-Tree arvore
//Se o status for "i", a função deve inserir todos os elementos do arquivo na árvore
//Se o status for "r", a função deve remover todos os elementos do arquivo da árvore
void manipulaBTree(btree* arvore, char* nomeArquivo, char status) {
    
    // Variável auxiliar
    int chave;

    // Abertura do arquivo
    FILE* arquivo = fopen(nomeArquivo, "r");

    // Verifica se houve erro na abertura
    if (arquivo == NULL) {
        return;
        
    }

    // Insere ou remove os
    // dados na árvore
	while(!feof(arquivo)) {
	    if(fscanf(arquivo, "%d", &chave) == 0) {
	        
			// Erro na leitura do arquivo
	        fclose(arquivo);
	        return;
	    
	    } else {
            
            // Insere elemento
            if (status == 'i') {
                insereElemento(arvore, chave);
                imprimeArvore(arvore->raiz, 0);

            // Remove elemento
            } else if (status == 'r') {
                removeElemento(arvore, chave);
                imprimeArvore(arvore->raiz, 0);
            
            } else {
				
			}
	    
	    }
	
	}

	// Inserções ou remoções
    // ocorreram com sucesso
	fclose(arquivo);

}
  no* getRaiz(btree *tree){
    return tree->raiz;
  }