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
void salvar(FILE *fptr, char *binario);
void ler(FILE *fptr, pHeap *no);



int main(){

	int i;
	pHeap *arvore_frequencia = NULL;

	arvore_frequencia = gera_arvore_de_frequencia(arvore_frequencia);

	pHeap *aux = arvore_frequencia->direita;
	aux = aux->direita;
	aux = aux->direita;

	//printf("\nESPACO 111\n%d - %c\n", aux->frequencia, aux->caractere);


	percorre(arvore_frequencia);

	//printar_tabela(arvore_frequencia);
	FILE *fptr = abrir_arquivo();


	criar_binario(fptr);

	fechar_arquivo(fptr);	

	fptr = fopen("binario.huff", "r");
	
    if(fptr == NULL){
       printf("Error! opening file");
       exit(1);
	}
   
	ler(fptr, arvore_frequencia);
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

		aux = aux->direita;
	}

	
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
			  


	n = qnt_caracteres-1;
	for(i = 0; i < n; i++){
        vetor[i+1] = insere_no(vetor[i], vetor[i+1]);
		sort(vetor, n, i+1);

	}

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

	int aux = temp->frequencia;
	while(i < n && aux >= vetor[i+1]->frequencia){
		vetor[i] = vetor[i+1];
		i++;
	}
	vetor[i] = temp;
	
	
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
 /*
 	for(i = 0; i < CHARSET_SIZE; i++){
 		printf("%c - %d\n", i, frequencia[i]);
	 }
 	printf("criar_vetor_frequencia FIM\n\n");
*/
}


//problem is here
void criar_binario(FILE *fptr){
	fseek(fptr, 0,SEEK_SET);
	
	FILE *fptrDestino;
	fptrDestino = fopen("binario.huff", "w+");
	if (fptrDestino == NULL){
       printf("Error! opening file");
       exit(1);
	}
   
	int ch;
	int i;
	int j;
	int restante = 0;
	char binario[100];
	binario[0] = '\0';
	char aux[100];
	aux[0] = '\0';

	while(1){

		//printf("rodou");
		if(strlen(binario) < 8){
			/*
			verifica se aux esta vazio, se sim copia aux para o binario
			se aux estiver vazio, pega um novo char e concatena com o binario
			*/
	
			if(strlen(aux) > 0){
				//binario = aux;				
				strcat(binario, aux);
				aux[0] = '\0';
			}else{
				//novo char
				ch = fgetc(fptr);
				//printf("%c", ch);
				if(ch == EOF){
					
					if(strlen(binario) > 0){
						printf("Salvou bin antes - %s\n", binario);
						while(strlen(binario) < 8){

							binario[strlen(binario)+1] = '\0';							
							binario[strlen(binario)] = '0';
							restante++; 				
						}
						
		
						binario[strlen(binario)] = '\0';
						salvar(fptrDestino, binario);
						printf("Salvou bin dps- %s\n", binario);
						salvar(fptrDestino, decimal_to_binary(restante));
						printf("salvou restante - %s\n", decimal_to_binary(restante));
	
					}else{
						salvar(fptrDestino, decimal_to_binary(0));
						printf("salvou 0 %s\n", decimal_to_binary(0));
					}					
					

					break;
				}
				//printf("char %c\n", ch);
				//printf("%s + %s\n", binario, tabela[ch].binario);				
				strcat(binario, tabela[ch].binario);
				//printf(" = %s \n", binario);				
	
			}
		}else if(strlen(binario) > 8){

			/*
			copia td binario para aux, deixa binario com 8 char,
			desloca os char de aux excluindo 8 primeiros
			*/

			strcpy(aux, binario);
			while(strlen(binario) > 8){
				binario[strlen(binario)-1] = '\0';
			}
		
			for(i = 0, j = strlen(aux); i < j; i++){
				aux[i] = aux[i+8];
			}
			aux[j - 8] = '\0';


		}else if(strlen(binario) == 8){

			salvar(fptrDestino, binario);
			binario[0] = '\0';		
		}
	}

	fechar_arquivo(fptrDestino);

}

void salvar(FILE *fptr, char *binario){
	
	int temp = strtol(binario,0,2);
	//printf("salvou %d\n", temp);

	//printf("%s - %d - %c\n", binario, temp, temp);
	putc(temp, fptr);				

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

void ler(FILE *fptr, pHeap *no){
	
	int ch, ch1, ch2;

	FILE *fptrNovo;
	fptrNovo = fopen("descompactado.txt", "w");

	
	char *binario;
	binario = (char*)malloc(sizeof(char));	

	pHeap *aux;
	aux = (pHeap*)malloc(sizeof(pHeap));
	aux = no;
	int i, j;
	


	ch = fgetc(fptr);
	if(ch == EOF){
		printf("error");
		//break;
	}
	ch1 = fgetc(fptr);
	if(ch1 == EOF){
		printf("error");	
		//break;				
	}
	
	while(1){
			
		ch2 = fgetc(fptr);
		if(ch2 == EOF){

			//remover quantidade de chars sobressalente 
			binario = decimal_to_binary(ch);

			printf("ultimos valres %d %d \n", ch, ch1);
			printf("ultima string lida %s\n", binario);
			j = 9 - ch1;			
			while(ch1 > 0){
				binario[strlen(binario)-1] = '\0';
				ch1--;			
			}
			printf("string alterada %s\n", binario);
		
			i = 0;
			while(i < j){
				if(aux->caractere != -1 ){
					putc(aux->caractere, fptrNovo);	
					printf("ultimo char %d - %c\n", aux->caractere);	
					i++;		
				}else{
					if(binario[i] == '1'){
						aux = aux->direita;
					}else{
						aux = aux->esquerda;
					}
					i++;
				}				
			}		

			break;				
		}	

	
		binario = decimal_to_binary(ch);
		
	
		i = 0;
		while(i < 8){
			
			if(aux->caractere != -1 ){
				//printf(" achou : %c\n", aux->caractere);
				//printf("%c", aux->caractere);
				//salvarDescompactado(fptrNovo, aux->caractere);
				putc(aux->caractere, fptrNovo);				
				aux = no;
				//break;
			}else{
				if(binario[i] == '1'){
					//printf("1");
					aux = aux->direita;
				}else{
					//printf("0");
					aux = aux->esquerda;
				}
				i++;
			}				
		}
		ch = ch1;
		ch1 = ch2;
		
	}
	fechar_arquivo(fptrNovo);
	
}

//void salvarDescompactado(FILE *fptr, int ch){

	//putc(ch, fptr);

//}
