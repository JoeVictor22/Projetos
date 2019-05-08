#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARSET_SIZE 255

typedef struct pHeap{
	int caractere;
	int frequencia;
	struct pHeap *esquerda;
	struct pHeap *direita;
}pHeap;



//-------------------BST-------------------//
pHeap *busca(pHeap *no, int *caractere);
pHeap *novo_pHeap(int caractere, int frequencia);
pHeap *inserir(pHeap *no, int caractere, int frequencia);
void em_ordem(pHeap *no);
void pre_ordem(pHeap *no);
void pos_ordem(pHeap *no);
//-------------------BST_FIM---------------//

//-------------------BST-------------------//

pHeap *busca(pHeap *no, int *caractere){
	printf("rodou");
	if(no->caractere == *caractere || no == NULL){
		printf("\n");
		return no;
	}else if(no->esquerda != NULL){
		printf("0");
		return busca(no->esquerda, caractere);
	}else if(no->direita != NULL){
		printf("1");
		return busca(no->direita, caractere);
	}else{
		printf("\ndeu ruim\n\n");
		return no;
	}
}


pHeap *novo_pHeap(int caractere, int frequencia){
	pHeap *no;
	no = (pHeap*)malloc(sizeof(pHeap));
	no->esquerda = NULL;
	no->direita = NULL;
	no->caractere = caractere;
	no->frequencia = frequencia;
	return no;
}

pHeap *inserir(pHeap *no, int caractere, int frequencia) {

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
		printf(" %c - %d\n",no->caractere, no->frequencia);
		em_ordem(no->direita);
	}
}


void pre_ordem(pHeap *no){

	if(no != NULL){
		printf(" %c - %d\n",no->caractere, no->frequencia);
		pre_ordem(no->esquerda);
		pre_ordem(no->direita);
	}
}

void pos_ordem(pHeap *no){

	if(no != NULL){
		pos_ordem(no->esquerda);
		pos_ordem(no->direita);
		printf(" %c - %d\n",no->caractere, no->frequencia);
	}
}
//----------------BST_FIM-------------------//

