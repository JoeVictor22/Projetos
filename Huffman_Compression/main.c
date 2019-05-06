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
void sort(pHeap *vetor[], int j);
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
		 	
	arvore_frequencia = gera_monte(arvore_frequencia);

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
	no->esquerda = no->direita = NULL;
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
	int i;
	for(i = 0; i < HEAP_MAX; i++){
		vetor[i] = no;
		no = no->direita;
	}

	//print
	printf("\nvetor : ");
	for(i = 0; i <  HEAP_MAX; i++){
		printf(" %d - %c,", vetor[i]->frequencia, vetor[i]->caractere);
	}	

	printf("\n");
			
	/*insert
	- soma os nos ate que o vetor so contenha 1 unico no
	*/
	
	int l;

	pHeap *temp;	
	int j = HEAP_MAX-1;
	i = 0;
	while(i < j){
		temp = insere_no(vetor[i], vetor[i+1]);
		i++;		
		vetor[i] = temp;		
		sort(vetor, j);
		

		printf("I : %d J : %d\n", i, j);
		//getchar();
		printf("vetor : ");
		for(l = 0; l <  j; l++){
			printf(" %d - %c,", vetor[l]->frequencia, vetor[l]->caractere);
		}		
		printf("\n\n");

	}

	em_ordem(vetor[0]);
	printf("\n");

	return no;	
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

void sort(pHeap *vetor[], int j){
	//int aux = temp->frequencia;
	int aux = vetor[1]->frequencia;
	int i = 1;
	while(i < j && vetor[i+1]->frequencia <= aux){
		vetor[i] = vetor[i+1];
		i++;
	}
	vetor[i] = vetor[1];
}
//------------PRIORIDADE_HUFFMAN_FIM--------//

