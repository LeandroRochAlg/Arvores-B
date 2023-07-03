#ifndef ARVORE_B
#define ARVORE_B

typedef struct no no;

typedef struct bt bt;

typedef struct registro registro;

//Aloca um novo nó
no *alocaNo(int ordem);

//Aloca uma nova B-Tree
bt *criaArvore(int m);

//Busca um elemento na B-Tree
no *buscaElemento(no *atual, int valor);

//Insere um elemento na B-Tree
int insereElemento(bt *arvore, int valor, registro *reg);

//Divide um nó
no *split(bt *arvore, no *noDesbal, int valor);

//Remove um elemento da B-Tree
int removeElemento(bt *arvore, int valor);

//Rotaciona um nó
void rotacao(no *noDesbal, no *irmao, int posPai);

//Combina dois nós
no *merge(no *noDesbal, int posPai);

//Retorna a raiz da B-Tree
no* getRaiz(bt *tree);

//Processa os registros do arquivo
void lerRegistros(bt *arv, char *nomeArquivo);

//Gera os registros aleatórios
void gerarRegistros();

//Gera um número aleatório
int gerarMatriculaUnica(int *matriculas, int i);

//Busca uma matrícula no vetor de matrículas
int buscaMatricula(int *matriculas, int n, int matricula);

//Gera um nome aleatório
void gerarNome(char *nome);

//Gera uma data de nascimento aleatória
void gerarDataNascimento(char *dataNascimento);

//Gera um e-mail aleatório
void gerarEmail(char *email);

//Busca um registro no arquivo
void buscarRegistro(int matricula);

#endif //ARVORE_B