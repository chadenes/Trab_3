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

/* A função de consulta eh bem simples, ela primeiramente vai até a linha desejada e depois
até a coluna, se o elemento não se encontra na matriz esparsa ela devolve 0*/

int consulta(struct colunabase *raiz, int m, int n)
{
	struct colunabase *pont = raiz;
	struct celula *a = NULL;
	while(pont->linha != m) //chega na linha desejada
	{
		pont = pont->prox;
	}
	if(pont->linha1 == NULL) 
	{
		return 0; //o numero nao se encontra na matriz esparsa, ou seja, eh zero
	}
	a = pont->linha1;
	while(a->coluna < n) //procura a coluna desejada
	{
		a = a->prox;
	}
	if(a->coluna == n)
	{
		return(a->valor); //acha o numero e retorna ele
	}
	else if(a->coluna != n)
	{
		return 0; //nao existe o numero
	}
}




// a função soma serve para retornar a soma dos valores de uma linha
int somal(struct colunabase *raiz, int k)
{
	struct colunabase *pont = raiz;
	struct celula *a = NULL;
	int soma = 0;
	while(pont->linha != k) //laço de repetição para chegar na linha inserida
	{
		pont = pont->prox;
	}
	if (pont->linha1 == NULL)
	{
		return 0;//se nao existe nada na linha, sua soma eh zero
	}
	a = pont->linha1;
	while(a != NULL) //atravessa a linha somando cada elemento
	{
		soma = soma + a->valor;
		a = a->prox;
	}
	return (soma); //retorna o valor obtido
}



//a função somac serve para retornar a soma dos valores de uma coluna
int somac(struct colunabase *raiz, int k)
{
	struct colunabase *pont = raiz;
	struct celula *a = pont->linha1;
	int soma = 0;
	while (pont != NULL)//percorre todas as linhas da matriz
	{
		a = pont->linha1;
		if(a != NULL)//se a linha nao for nula, procura a coluna desejada
		{ 
			while(a->coluna < k && a != NULL)//percorre o item desejado 
			{
				a = a->prox;
			}
			if(a->coluna == k) //caso seja o item desejado, faz a soma
			{
				soma = soma + a->valor;
			}
		}
		pont = pont->prox;
	}
	return (soma); //retorna o valor da soma
}



main(){
	printf("Digite quantas linhas, quantas colunas e quantos elementos nao nulos\na matriz ira ter, em seguida,(como explicado no pdf) entre com \n");
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
	printf("4 - Consultar a soma dos valores de uma coluna da matriz\n5 - Atribuicao de um valor em uma posicao\n6 - Sair\n");
	int escolha = 10 ;
	while(escolha != 6){  //o menu esta contido dentro da main
		scanf("%d", &escolha);
		int n;
		switch(escolha){
			case 1: escolha = 6;
					printf("Matriz excluida");
					 break;
			case 2:printf("\nDigite a linha e a coluna que deseja conferir: ");
					scanf("%d %d", &l1, &c1);
					n = consulta(raiz, l1, c1); 
					printf("O numero dessa posicao eh : %d\n\n", n);
					break;
			case 3:printf("\nDigite a linha na qual deseja obter a soma: ");
					scanf("%d", &l1);
					n = somal(raiz, l1);
					printf("\nA soma dessa linha eh : %d \n\n", n);
					break;
			case 4:	printf("\nDigite a coluna na qual deseja obter a soma: ");
					scanf("%d", &c1);
					n = somac(raiz, c1);
					printf("\nA soma dessa coluna eh: %d \n\n", n);	
			case 5: printf("\nDigite a linha, a coluna e o valor do elemento, por favor insira\numa posicao que ainda nao esta ocupada: ");
					scanf("%d %d %d", &l1, &c1, &n);
					inserir(n, l1, c1, raiz);
					printf("\nValor inserido na matriz\n\n");		
		}
	}
}





