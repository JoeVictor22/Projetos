#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
	Quantidade de caracteres utilizados
	ANSI - ASCII Extended	
*/
#define CHARSET_SIZE 255

/*
	Estrutura de nó utilizada
	caractere - char salvo naquele nó, se char = -1 é um nó interno
	frequencia - frequencia daquele char ou a soma em um nó interno
	caminho - string binaria para se chegar naquele nó
*/
typedef struct pHeap{
	int caractere;
	int frequencia;
	char *caminho; 
	struct pHeap *esquerda;
	struct pHeap *direita;
}pHeap;


/*
	"dicionario" criado pra auxiliar no acesso das representacoes
*/
typedef struct dicionario{
	char *binario;
}Dict;

Dict tabela[CHARSET_SIZE+10];

//-------------------BST-------------------//
pHeap *novo_pHeap(int caractere, int frequencia);
void em_ordem(pHeap *no);
void libera_no(pHeap *no);

//-------------------HUFF-------------------//
void percorre(pHeap *no);
void salvar_caminho(pHeap *no);
pHeap *inserirNaDireita(pHeap *no, int caractere, int frequencia);



/*
	Cria um novo no
*/
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


/*
	Inseri nó no nivel mais profundo a direita
*/
pHeap *inserirNaDireita(pHeap *no, int caractere, int frequencia) {

    if (no == NULL){
		return novo_pHeap(caractere, frequencia);
    }else{
		no->direita = inserirNaDireita(no->direita, caractere, frequencia);    	
	}

    return no;
}


/*
	print
*/
void em_ordem(pHeap *no){

	if(no != NULL){
		em_ordem(no->esquerda);
		printf(" %c - %d\n",no->caractere, no->frequencia);
		em_ordem(no->direita);
	}
}


/*
	Percorre tds os nós e gera a string que representa o caractere
*/
void percorre(pHeap *no){	


	if(no->caractere != -1){
		salvar_caminho(no);
	}else{
	
		pHeap *aux = (pHeap*)malloc(sizeof(pHeap));
		if(no->esquerda != NULL){
			aux = no->esquerda;
			aux->caminho = (char*)realloc(aux->caminho, ((strlen(no->caminho) + 2) * sizeof(char)));
			strcpy(aux->caminho, no->caminho);
			aux->caminho = (char*)realloc(aux->caminho, ((strlen(aux->caminho) + 2) * sizeof(char)));
			strcat(aux->caminho, "0");
			aux->caminho[strlen(aux->caminho)] = '\0';
					
			percorre(no->esquerda);
		}
	
		if(no->direita != NULL){	
			aux = no->direita;
			aux->caminho = (char*)realloc(aux->caminho, ((strlen(no->caminho) + 2) * sizeof(char)));
			strcpy(aux->caminho, no->caminho);
			aux->caminho = (char*)realloc(aux->caminho, ((strlen(aux->caminho) + 2) * sizeof(char)));
			strcat(aux->caminho, "1");
			aux->caminho[strlen(aux->caminho)] = '\0';
		
			percorre(no->direita);
		}
	}
}


/*
	Auxiliar a funcao percorre
	Salvo a string na sua respectiva posicao na tabela
*/
void salvar_caminho(pHeap *no){
	tabela[no->caractere].binario = (char*)malloc((strlen(no->caminho) + 1)*sizeof(char));
	strcpy(tabela[no->caractere].binario, no->caminho);
}


/*
	Da free em tds os nós
*/
void libera_no(pHeap *no){
	if(no->esquerda != NULL){
		libera_no(no->esquerda);
	}
	if(no->direita != NULL){
		libera_no(no->direita);
	}
	free(no);
}
