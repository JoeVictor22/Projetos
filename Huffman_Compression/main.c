#include <stdio.h>
#include <stdlib.h>

#define HEAP_MAX 6

typedef struct pHeap{
	char caractere;
	int frequencia;
	struct pHeap *esquerda;
	struct pHeap *direita;
}pHeap;



//-------------------BST-------------------//
pHeap *busca(pHeap *no, char *caractere);
pHeap *novo_pHeap(char caractere, int frequencia);
pHeap *inserir(pHeap *no, char caractere, int frequencia);
void em_ordem(pHeap *no);
void pre_ordem(pHeap *no);
void pos_ordem(pHeap *no);
//-------------------BST_FIM---------------//

//------------FREQUENCE_HUFFMAN-----------//
pHeap *gera_monte(pHeap *no);
pHeap *insere_no(pHeap *no1, pHeap *no2);
void sort(pHeap *vetor[], int j, int i);
//------------FREQUENCE_HUFFMAN_FIM-------//



int main(){

	//AAAAABBCCCCDEEEEEEE
	char text[HEAP_MAX] = {'a', 'b', 'c', 'd', 'e', 'f'};
	int freq[HEAP_MAX] = {5,9,12,13,16,45};
	int i;
	pHeap *arvore_frequencia = NULL;
	for(i = 0; i < HEAP_MAX; i++){
		arvore_frequencia = inserir(arvore_frequencia, text[i], freq[i]);
	}
	em_ordem(arvore_frequencia);
	printf("\n");
	pre_ordem(arvore_frequencia);
	printf("\n");
	pos_ordem(arvore_frequencia);
	printf("\n");


	pHeap * temp = gera_monte(arvore_frequencia);
	/*
	printf("arvore inicial\n");
	em_ordem(arvore_frequencia);
	printf("\n");
	printf("arvore final\n");
	em_ordem(temp);
	printf("\n");
    */
	return 0;
}



//-------------------BST-------------------//
pHeap *busca(pHeap *no, char *caractere){
	if(no->caractere == *caractere || no == NULL){
		return no;
	}else if(no->caractere > *caractere){
		return busca(no->esquerda, caractere);
	}else if(no->caractere < *caractere){
		return busca(no->direita, caractere);
	}
}

pHeap *novo_pHeap(char caractere, int frequencia){
	pHeap *no;
	no = (pHeap*)malloc(sizeof(pHeap));
	no->esquerda = NULL;
	no->direita = NULL;
	no->caractere = caractere;
	no->frequencia = frequencia;
	return no;
}

pHeap *inserir(pHeap *no, char caractere, int frequencia) {

    if (no == NULL)
		return novo_pHeap(caractere, frequencia);
    if (frequencia < no->frequencia)
        no->esquerda = inserir(no->esquerda, caractere, frequencia);
    else if (frequencia > no->frequencia)
        no->direita = inserir(no->direita, caractere, frequencia);

    return no;
}

void em_ordem(pHeap *no){

	if(no != NULL){
		em_ordem(no->esquerda);
		printf(" %c - %d,",no->caractere, no->frequencia);
		em_ordem(no->direita);
	}
}


void pre_ordem(pHeap *no){

	if(no != NULL){
		printf(" %c - %d,",no->caractere, no->frequencia);
		pre_ordem(no->esquerda);
		pre_ordem(no->direita);
	}
}

void pos_ordem(pHeap *no){

	if(no != NULL){
		pos_ordem(no->esquerda);
		pos_ordem(no->direita);
		printf(" %c - %d,",no->caractere, no->frequencia);
	}
}
//----------------BST_FIM-------------------//



/*
- A arvore a ser utilizada deve estar em ordem crescente de frequencias
- Cada nó criado, sendo ele a soma de duas folhas, deve possuir charater = NULL, indicando
que ele é um nó interno

*/
//------------PRIORIDADE_HUFFMAN------------//


pHeap *gera_monte(pHeap *raiz){

	pHeap *no = raiz;

	/*INI
	- cria um vetor auxiliar para ser realizado as alteracoes na arvore
	*/
	pHeap *vetor[HEAP_MAX];
	pHeap *fix;
	int i;
	for(i = 0; i < HEAP_MAX; i++){
        fix = no->direita;
        no->direita = NULL;
		vetor[i] = no;
		no = fix;

	}

	//print
	printf("\nvetor incial: ");
	for(i = 0; i <  HEAP_MAX; i++){
		printf(" %d - %c,", vetor[i]->frequencia, vetor[i]->caractere);
	}

	printf("\n\n\n");

	/*insert
	- soma os nos ate que o vetor so contenha 1 unico no
	*/


	int j = HEAP_MAX-1;
	for(i = 0; i < j; i++){
        vetor[i+1] = insere_no(vetor[i], vetor[i+1]);

		sort(vetor, j, i+1);

		printf("I : %d J : %d\n", i, j);
		//getchar();

	}

	/*
	printf("\neoq pvt, funciona ai meu : %d\n\n", vetor[j]->frequencia);
    printf("%d - %d\n", vetor[j]->esquerda->frequencia, vetor[j]->direita->frequencia);
    printf("%d ", vetor[j]->direita->esquerda->frequencia);
    printf("%d ", vetor[j]->direita->esquerda->esquerda->frequencia);
    printf("%d ", vetor[j]->direita->esquerda->direita->frequencia);
    printf("%d ", vetor[j]->direita->esquerda->direita->direita->frequencia);
    **/

    em_ordem(vetor[j]);

	return vetor[j];
}

pHeap *insere_no(pHeap *no1, pHeap *no2){
	pHeap *no;
	no = (pHeap*)malloc(sizeof(pHeap));

	no->esquerda = no1;
	no->direita = no2;
	no->frequencia = no1->frequencia + no2->frequencia;
	no->caractere = 'N';
	printf("no interno criado : %d - %c, a partir de : |%d - %c| e |%d - %c|\n",no->frequencia, no->caractere, no1->frequencia, no1->caractere, no2->frequencia, no2->caractere);

	return no;
}


//nao precisa passar j se tamanho for definido em HEAP_MAX
void sort(pHeap *vetor[], int j, int i){
	//int aux = temp->frequencia;
	pHeap *temp = vetor[i];
	printf("\nvalor a ser ordenado : %d\n", temp->frequencia);
	int l;
	printf("vetor : nao ordenado");
	for(l = i; l <=  j; l++){
		printf(" %d - %c,", vetor[l]->frequencia, vetor[l]->caractere);
	}
	printf("\n");

	int aux = temp->frequencia;
	while(i < j && aux >= vetor[i+1]->frequencia){
		vetor[i] = vetor[i+1];
		i++;
	}
	vetor[i] = temp;

	printf("valor a ser substittuido %d = %d\n", vetor[i]->frequencia, temp->frequencia);



	printf("vetor ordenado: ");
	for(l = i-2; l <=  j; l++){
		printf(" %d - %c,", vetor[l]->frequencia, vetor[l]->caractere);
	}
	printf("\n\n");


}


//------------PRIORIDADE_HUFFMAN_FIM--------//

