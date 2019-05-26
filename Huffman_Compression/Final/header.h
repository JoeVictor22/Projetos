#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARSET_SIZE 255

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

Dict tabela[CHARSET_SIZE+10];

//-------------------BST-------------------//
pHeap *novo_pHeap(int caractere, int frequencia);
pHeap *inserirNaDireita(pHeap *no, int caractere, int frequencia);
void em_ordem(pHeap *no);
void pre_ordem(pHeap *no);
void pos_ordem(pHeap *no);
//-------------------BST_FIM---------------//


//---------------SALVAR_CAMINHO------------//
void salvar_caminho(pHeap *no);
void percorre(pHeap *no);
void printar_tabela(pHeap *no);
//---------------SALVAR_CAMINHO------------//



//-------------------BST-------------------//

pHeap *novo_pHeap(int caractere, int frequencia){
	pHeap *no;
	no = (pHeap*)malloc(sizeof(pHeap));
	no->esquerda = NULL;
	no->direita = NULL;
	no->caractere = caractere;
	no->frequencia = frequencia;
	no->caminho = (char*)malloc(sizeof(char));
	no->caminho[0] = '\0';
	
	return no;
}

pHeap *inserirNaDireita(pHeap *no, int caractere, int frequencia) {

    if (no == NULL){
		return novo_pHeap(caractere, frequencia);
    }else{
		no->direita = inserirNaDireita(no->direita, caractere, frequencia);    	
	}

    return no;
}

void em_ordem(pHeap *no){

	if(no != NULL){
		em_ordem(no->esquerda);
		printf(" %c - %d\n",no->caractere, no->frequencia);
		em_ordem(no->direita);
	}
}

//----------------BST_FIM-------------------//

void printar_tabela(pHeap *no){
	int i;
	printf("comecou");
	for(i = 0; i < CHARSET_SIZE; i++){
		if(tabela[i].binario != NULL){
			printf("%c - %s\n", i, tabela[i]);
		}
	}

	printf("print tabela FIM\n\n");

}
void salvar_caminho(pHeap *no){

	tabela[no->caractere].binario = (char*)malloc((strlen(no->caminho) + 1)*sizeof(char));

	strcpy(tabela[no->caractere].binario, no->caminho);
	
	printf("string : %s ------- ", tabela[no->caractere].binario);

	printf("salvou caminho : %s pra letra %c int = %d\n", no->caminho, no->caractere, no->caractere);

}


void percorre(pHeap *no){	
	//se encontrar valor
	if(no->caractere != -1){
		salvar_caminho(no);

	}else{
	
		pHeap *aux = (pHeap*)malloc(sizeof(pHeap));
		if(no->esquerda != NULL){
			aux = no->esquerda;
			//aux->caminho = no->caminho;
			aux->caminho = (char*)realloc(aux->caminho, ((strlen(no->caminho) + 2) * sizeof(char)));
			strcpy(aux->caminho, no->caminho);
			aux->caminho = (char*)realloc(aux->caminho, ((strlen(aux->caminho) + 2) * sizeof(char)));
			strcat(aux->caminho, "0");
			aux->caminho[strlen(aux->caminho)] = '\0';
					
			percorre(no->esquerda);
		}
	
		if(no->direita != NULL){	
			aux = no->direita;
			//aux->caminho = no->caminho;
			aux->caminho = (char*)realloc(aux->caminho, ((strlen(no->caminho) + 2) * sizeof(char)));
			strcpy(aux->caminho, no->caminho);
			aux->caminho = (char*)realloc(aux->caminho, ((strlen(aux->caminho) + 2) * sizeof(char)));
			strcat(aux->caminho, "1");
			aux->caminho[strlen(aux->caminho)] = '\0';
		
			percorre(no->direita);
		}
	
	}


}
