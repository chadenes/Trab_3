#include<stdio.h>
#include<stdlib.h>



/*estrutura de dados que será a base do programa*/
struct celula{
	int valor;
	int coluna;
	struct celula* prox;
};



/*estrutura de dados que será a base para as listas encadeadas*/

struct colunabase{
	int linha;
	struct celula* linha1;
	struct colunabase* prox;
};



//função que irá inserir elementos na matriz
void inserir(int k, int l, int n, struct colunabase *raiz){
	struct celula *a = NULL;
	struct celula *b = NULL;
	struct colunabase *pont = raiz;
	int i = 0; 
	while(pont->linha != l) { // laço de repetição para chegar na linha desejada
		pont = pont->prox;
	}
	if (pont->linha1 == NULL) { //se nao houver nada na linha, ja aloca o espaco para o novo item
		a = (struct celula*) malloc(sizeof(struct celula)); //alocação dinâmica de memória
		a->valor = k;
		a->coluna = n; 
		a->prox = NULL; // aterra o ponteiro 
		pont->linha1 = a;
	}
	else { //caso a linha já possua algum elemento
		a = pont->linha1;
		if (a->coluna > n) { //se o elemento deve vir antes do que já está na linha
			b = (struct celula*) malloc(sizeof(struct celula));
			b->valor = k;
			b->coluna = n;
			b->prox = a;
			pont->linha1 = b;
		}
		else{
			while(a->prox != NULL && a->coluna < n) { //chega na posicao correta
				a = a->prox;
			}
			b = (struct celula*) malloc(sizeof(struct celula));
			b->valor = k;
			b->coluna = n;
			b->prox = a->prox; //mantem a ordenacao
			a->prox = b;
		}
	}
}



main(){
	printf("Digite quantas linhas, quantas colunas e quantos elementos não nulos\na matriz ira ter, em seguida,(como explicado no pdf) entre com \n");
	printf("a linha do elemento, a coluna e o valor do mesmo, nessa ordem!\n");
	int l, c, e;
	scanf("%d %d %d", &l, &c, &e);
	struct colunabase *raiz = (struct colunabase *)malloc(sizeof(struct colunabase));// criando a raiz
	struct colunabase *pont = raiz;
	raiz->prox = NULL;
	raiz->linha1 = NULL;
	raiz->linha = 0;
	int i;
	for (i = 1; i <= c; i++){ //cria os elementos da coluna base
		pont->prox = (struct colunabase *)malloc(sizeof(struct colunabase));
		pont = pont->prox;
		pont->linha1 = NULL;
		pont->prox = NULL;
		pont->linha = i; // cada elemento já tem a sua linha
	}
	int l1, c1, k;
	for(i=0; i<e; i++){
		scanf("%d %d %d", &l1, &c1, &k);
		inserir(k, l1, c1, raiz);
	}
	printf("\nAgora que ja foram inseridos os elementos da matriz, escolha o que deseja fazer: \n");
	printf("1 - Exclusao da matriz\n2 - Consultar um valor de uma posicao\n3 - Consultar a soma dos valores de uma linha\n");
	printf("4 - Consultar a soma dos valores de uma coluna da matriz\n5 - Atribuicao de um valor em uma posicao\n6 - Sair");
	int escolha = 10;
	while(escolha != 6){
		switch(escolha){
			case 1: break;
			case 2: break;
		}
	}
}





