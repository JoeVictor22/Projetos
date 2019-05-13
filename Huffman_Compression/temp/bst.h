#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARSET_SIZE 255
#define HEAP_MAX 6

//FREE CAMINHO //
//

typedef struct pHeap{
	int caractere;
	int frequencia;
	char *caminho;
	struct pHeap *esquerda;
	struct pHeap *direita;
}pHeap;

typedef struct dicionario{
	char *binario;
}Dict;

Dict tabela[CHARSET_SIZE]; 

//-------------------BST-------------------//
pHeap *busca(pHeap *no, int *caractere);
pHeap *novo_pHeap(int caractere, int frequencia);
pHeap *inserir(pHeap *no, int caractere, int frequencia);
void em_ordem(pHeap *no);
void pre_ordem(pHeap *no);
void pos_ordem(pHeap *no);
//-------------------BST_FIM---------------//


//---------------SALVAR_CAMINHO------------//
void salvar_caminho(pHeap *no);
void percorre(pHeap *no);
void atualiza_caminho(pHeap *no, char *caminho, char bin);
//---------------SALVAR_CAMINHO------------//



//-------------------BST-------------------//
pHeap *busca(pHeap *no, int *caractere){
	if(no->caractere == *caractere || no == NULL){
		return no;
	}else if(no->caractere > *caractere){
		return busca(no->esquerda, caractere);
	}else if(no->caractere < *caractere){
		return busca(no->direita, caractere);
	}
}

pHeap *novo_pHeap(int caractere, int frequencia){
	pHeap *no;
	no = (pHeap*)malloc(sizeof(pHeap));
	no->esquerda = NULL;
	no->direita = NULL;
	no->caractere = caractere;
	no->frequencia = frequencia;
	no->caminho;
	
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
void salvar_caminho(pHeap *no){
	Dict letra;
	letra.binario = no->caminho;
	tabela[no->caractere] = letra;
}


void percorre(pHeap *no, short nivel){	
	//se encontrar valor
	if(no->caractere != -1){
		salvar_caminho(no);
		printf("nivel valor %d\n", nivel);
	}else{
		nivel++;
		printf("nivel %d\n", nivel);
		if(no->direita != NULL){
			printf("direita igual : %s\n", no->caminho);
			system("pause");
			atualiza_caminho(no->direita, no->caminho, '1', nivel);
			percorre(no->direita, nivel);
		}
		if(no->esquerda != NULL){
			printf("esquerda igual : %s\n", no->caminho);
			system("pause");
			atualiza_caminho(no->esquerda, no->caminho, '0', nivel);
			percorre(no->esquerda, nivel);
		}
	}


}
//strcat e strcpy olhar teste
//
//
//

void atualiza_caminho(pHeap *no, char *caminho, char bin, int nivel){
	no->caminho = strcat(caminho, bin);

}
