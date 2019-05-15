#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"


int frequencia[CHARSET_SIZE+10];
//Dict tabela[CHARSET_SIZE+10]; 

void criar_vetor_frequencia(FILE *fptr);

FILE *abrir_arquivo();
void fechar_arquivo(FILE *fptr);

/*
- quando referenciar CHARSET_SIZE usar menor ou igual

*/
pHeap *gera_arvore_de_frequencia(pHeap *arvore_frequencia);

//------------FREQUENCE_HUFFMAN-----------//
pHeap *gera_monte(pHeap *no, int qnt_caracteres);
pHeap *insere_no(pHeap *no1, pHeap *no2);
void sort(pHeap *vetor[], int n, int i);
//------------FREQUENCE_HUFFMAN_FIM-------//


//-------------salvar arquivo

void criar_binario(FILE *fptr);
//char * reverse( char * s );
char *decimal_to_binary(int n);



int main(){

	int i;
	pHeap *arvore_frequencia = NULL;

	arvore_frequencia = gera_arvore_de_frequencia(arvore_frequencia);

	pHeap *aux = arvore_frequencia->direita;
	aux = aux->direita;
	aux = aux->direita;

	//printf("\nESPACO 111\n%d - %c\n", aux->frequencia, aux->caractere);
	system("pause");

	percorre(arvore_frequencia);

	//printar_tabela(arvore_frequencia);
	FILE *fptr = abrir_arquivo();

	system("color 0a");
	criar_binario(fptr);

	fechar_arquivo(fptr);	
	return 0;
}




pHeap *gera_arvore_de_frequencia(pHeap *arvore_frequencia){
	
	int i;
	int qnt_caracteres;
	FILE *fptr = abrir_arquivo();
	criar_vetor_frequencia(fptr);

	//inserindo na ordem de leitura
	for(i = 0, qnt_caracteres = 0; i <= CHARSET_SIZE; i++){
		if(frequencia[i] > 0){
			arvore_frequencia = inserirNaDireita(arvore_frequencia, i, frequencia[i]);
			qnt_caracteres++;	
		}
		
	}
	
	
	//teste inserir direita
	pHeap *aux = arvore_frequencia;
	for(i = 0; i < qnt_caracteres; i++){
		printf("%c - %d\n", aux->caractere, aux->frequencia);
		aux = aux->direita;
	}
	printf("inserir_direita FIM\n\n");
	
	//arquivo teste : ggggggg ffffff aaaaa bbbb ccc dd e
	arvore_frequencia = gera_monte(arvore_frequencia, qnt_caracteres);
	fechar_arquivo(fptr);
	return arvore_frequencia;
}

pHeap *gera_monte(pHeap *raiz, int qnt_caracteres){

	pHeap *no = raiz;

	pHeap *vetor[qnt_caracteres];
	pHeap *aux;
	int i;
	for(i = 0; i < qnt_caracteres; i++){
		aux = no->direita;
        no->direita = NULL;
		vetor[i] = no;
		no = aux;
	}
	
	for(i = 0; i < qnt_caracteres; i++){
		printf("%c - %d\n", vetor[i]->caractere, vetor[i]->frequencia);
	}
	
	printf("atribuicao de vetor FIM\n\n");

	int j; 
	bool troca; 
	int n = qnt_caracteres-1;
	for (i = 0; i < n; i++) { 
		troca = false;

		for (j = 0; j < n-i; j++){ 
			if (vetor[j]->frequencia > vetor[j+1]->frequencia){ 
				aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux; 
				troca = true; 	
			} 
		}
		if (troca == false){
			break; 
		} 
			
	}
			  
	for(i = 0; i < qnt_caracteres; i++){
		printf("%d - %c\n", vetor[i]->frequencia, vetor[i]->caractere);
	}
	printf("sort do vetor FIM\n\n");

	n = qnt_caracteres-1;
	for(i = 0; i < n; i++){
        vetor[i+1] = insere_no(vetor[i], vetor[i+1]);
		sort(vetor, n, i+1);

	}

	printf("vetor entregue : %d - %d\n\n", vetor[n]->frequencia, vetor[n]->caractere);
	return vetor[n];
}

pHeap *insere_no(pHeap *no1, pHeap *no2){
	pHeap *no;
	no = (pHeap*)malloc(sizeof(pHeap));

	no->esquerda = no1;
	no->direita = no2;
	no->frequencia = no1->frequencia + no2->frequencia;
	no->caractere = -1;
	no->caminho = (char*)malloc(sizeof(char));
	no->caminho[0] = '\0';
	//printf("no interno criado : %d - %c, a partir de : |%d - %c| e |%d - %c|\n",no->frequencia, no->caractere, no1->frequencia, no1->caractere, no2->frequencia, no2->caractere);

	return no;
}


//nao precisa passar j se tamanho 
void sort(pHeap *vetor[], int n, int i){

	pHeap *temp = vetor[i];
	
	int i1 = i;
	int k = i1;
	for(k; k <= n; k++){
		printf("%d ", vetor[k]->frequencia);	
	}
	printf("\nvetor nao ordenado FIM\n\n");


	int aux = temp->frequencia;
	while(i < n && aux >= vetor[i+1]->frequencia){
		vetor[i] = vetor[i+1];
		i++;
	}
	vetor[i] = temp;
	
	for(k = i1; k <= n; k++){
		printf("%d ", vetor[k]->frequencia);	
	}
	printf("\nvetor ordenado FIM\n\n");
	
}




//FILE *abrir_arquivo(char *endereco){
FILE *abrir_arquivo(){
	FILE *fptr;
    fptr = fopen("program.txt","r+");

   if (fptr == NULL){
       printf("Error! opening file");
       exit(1);
	}
   
   return fptr;
	//fseek(fptr, 0,SEEK_SET);
}

void fechar_arquivo(FILE *fptr){
	fclose(fptr);
}

void criar_vetor_frequencia(FILE *fptr){

	int i;
	//zerar vetor
	for(i = 0; i <= CHARSET_SIZE; i++){
		frequencia[i] = 0;
	}

	int ch;
	//calcular frequencia
	while(1){
		ch = fgetc(fptr);
		
		if(ch==EOF){
			break;
		}		
		frequencia[ch]++;	
	}
 
 	//print vetor frequencia
 
 	for(i = 0; i < CHARSET_SIZE; i++){
 		printf("%c - %d\n", i, frequencia[i]);
	 }
 	printf("criar_vetor_frequencia FIM\n\n");
}


void criar_binario(FILE *fptr){
	fseek(fptr, 0,SEEK_SET);
	
	int ch;
	int j = 0;
	char binario[50];
	binario[0] = '\0';
	char aux[50];
	aux[0] = '\0';
	//calcular frequencia
	while(1){
		ch = fgetc(fptr);
		
		
		if(ch == EOF){
			
			printf("\nULTIMA STRING :bin =%s, aux =%s\n", binario, aux);
			printf("fim do arquivo FIM\n\n");
			break;
		}
		
		TESTE:
		
		if(strlen(binario) < 8){
			if(j == 0){
				strcat(binario, tabela[ch].binario);
 				//binario = getBinario(ch);//strcat	
 				//break;		
			}else{
				strcpy(binario, aux);
				//bin = aux; //strcpy
				aux[0] = '\0';
				j = 0;
				//reduzir fptr 1 char
			//	fseek(fptr, -1,SEEK_CUR);
				goto TESTE;
				//break;
			}	
		}
		while(strlen(binario) > 8){
			aux[j] = binario[strlen(binario) - 1];
			binario[strlen(binario) - 1] = '\0';
			j++;
		}
		if(j > 0){
			aux[j] = '\0';
			//aux = reverse(&aux);
			
			//reverse string
			int length = strlen(aux);
		    int c, i, k;
		    for (i = 0, k = length - 1; i < k; i++, k--){
		        c = aux[i];
		        aux[i] = aux[k];
		        aux[k] = c;
		    }
			
		}
		
		//talvez colocar esse if dentro do if anterior j > 0
		if(strlen(binario) == 8){
			printf("%s\n", binario);
			
		//	printf("salvar string : %s\n", binario);
			binario[0] = '\0';
			//armazenar(binario); //salvar no arquivo?	
		}

			
	}
 
}


char *decimal_to_binary(int n)
{
   int c, d, count;
   char *pointer;
   
   count = 0;
   pointer = (char*)malloc(8+1);
   
   if (pointer == NULL)
      printf("error");
     
   for (c = 7 ; c >= 0 ; c--)
   {
      d = n >> c;
     
      if (d & 1)
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';
     
      count++;
   }
   *(pointer+count) = '\0';
   
   return  pointer;
}

