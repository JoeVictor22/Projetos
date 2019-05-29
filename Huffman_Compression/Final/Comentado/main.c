#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

/*
	arquivo de entrada = "arquivo.txt"
	arquivo compactado = "binario.huff"
	arquivo descompactado = "descompactado.txt"
*/


int frequencia[CHARSET_SIZE+10];
int qnt_caracteres;

//---------------FREQUENCIA---------------//
void criar_vetor_frequencia(FILE *fptr);
pHeap *gera_arvore_unidirecional(pHeap *arvore_frequencia);

//-----------------HUFFMAN---------------//
pHeap *gera_nos_internos(pHeap *no, int qnt_caracteres);
pHeap *insere_no_interno(pHeap *no1, pHeap *no2);
void sort(pHeap *vetor[], int n, int i);

//----------------ARQUIVO----------------//
void criar_binario(FILE *fptr);
char *decimal_to_binary(int n);
void salvar(FILE *fptr, char *binario);
void descompactar(FILE *fptr, pHeap *no);
FILE *abrir_arquivo();
void fechar_arquivo(FILE *fptr);


/*
*/


int main(){

	pHeap *arvore_frequencia = NULL;
	//cria arvore unidirecional
	arvore_frequencia = gera_arvore_unidirecional(arvore_frequencia);
	//cria os nós internos
	arvore_frequencia = gera_nos_internos(arvore_frequencia, qnt_caracteres);
	//cria as strings para a tabela
	percorre(arvore_frequencia);

	FILE *fptr = abrir_arquivo();
	//cria o arquivo binario
	criar_binario(fptr);
	fechar_arquivo(fptr);	

	fptr = fopen("binario.huff", "r");
    if(fptr == NULL){
       printf("Error! opening file");
       exit(1);
	}
   	//le o arquivo binario e o descompacta
	descompactar(fptr, arvore_frequencia);
	fechar_arquivo(fptr);

	deleta_arvore(arvore_frequencia);

	return 0;
}


////////////////////////////////////////////
//---------------FREQUENCIA---------------//
////////////////////////////////////////////
/*
	gera arvore com nos apenas para direita
*/
pHeap *gera_arvore_unidirecional(pHeap *arvore_frequencia){
	
	int i;
	FILE *fptr = abrir_arquivo();

	criar_vetor_frequencia(fptr);

	/*
		Se existe um char 'i' no arquivo, insere ele e sua frequencia na arvore
	*/
	for(i = 0, qnt_caracteres = 0; i <= CHARSET_SIZE; i++){
		if(frequencia[i] > 0){
			arvore_frequencia = inserirNaDireita(arvore_frequencia, i, frequencia[i]);
			qnt_caracteres++;	
		}
		
	}
	
	fechar_arquivo(fptr);
	return arvore_frequencia;
}

void criar_vetor_frequencia(FILE *fptr){

	int i;
	//zera vetor
	for(i = 0; i <= CHARSET_SIZE; i++){
		frequencia[i] = 0;
	}

	int ch;
	while(1){
		ch = fgetc(fptr);
		
		if(ch==EOF){
			break;
		}		
		frequencia[ch]++;	
	}
}


///////////////////////////////////////////
//-----------------HUFFMAN---------------//
///////////////////////////////////////////
/*
	armazena tds os nós em um vetor e faz a criacao dos nos internos
*/
pHeap *gera_nos_internos(pHeap *raiz, int qnt_caracteres){

	pHeap *no = raiz;

	pHeap *vetor[qnt_caracteres];
	pHeap *aux;
	int i;

	//salva tds os nos em um vetor e quebra a relacao entre eles
	for(i = 0; i < qnt_caracteres; i++){
		aux = no->direita;
        no->direita = NULL;
		vetor[i] = no;
		no = aux;
	}
	
	
	int j; 
	bool troca; 
	int n = qnt_caracteres-1;

	//bubble sort no vetor, ordenando em ordem de frequencia
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

	//realiza as somas de frequencia e cria os nos internos
	for(i = 0; i < n; i++){
        vetor[i+1] = insere_no_interno(vetor[i], vetor[i+1]);
		sort(vetor, n, i+1);
	}

	return vetor[n];
}

/*
	insertion sort auxiliar a funcao gera_nos_internos()
*/
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

/*
	cria um nó interno, que é a soma de dois nós raizes
*/
pHeap *insere_no_interno(pHeap *no1, pHeap *no2){
	pHeap *no;
	no = (pHeap*)malloc(sizeof(pHeap));

	no->esquerda = no1;
	no->direita = no2;
	no->frequencia = no1->frequencia + no2->frequencia;
	no->caractere = -1;
	no->caminho = (char*)malloc(sizeof(char));
	no->caminho[0] = '\0';

	return no;
}


///////////////////////////////////////////
//----------------ARQUIVO----------------//
///////////////////////////////////////////
FILE *abrir_arquivo(){
	FILE *fptr;
    fptr = fopen("arquivo.txt","r+");

   if (fptr == NULL){
       printf("Error! opening file");
       exit(1);
	}
   
   return fptr;
}

void fechar_arquivo(FILE *fptr){
	fclose(fptr);
}

/*
	cria 'binario' usando um metodo de serializacao de dados
*/
void criar_binario(FILE *fptr){
	fseek(fptr, 0,SEEK_SET);
	
	FILE *fptrDestino;
	//TODO usar funcao abrir_arquivo()
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

		if(strlen(binario) < 8){
			/*
			verifica se aux esta vazio, se sim copia aux para o binario
			se aux estiver vazio, pega um novo char e concatena com o binario
			*/
	
			if(strlen(aux) > 0){
				//concatena aux em binario
				strcat(binario, aux);
				aux[0] = '\0';
			}else{
				//novo char
				ch = fgetc(fptr);
				
				//se chegar ao fim do arquivo executa instrucao especifica
				if(ch == EOF){	
					if(strlen(binario) > 0){
						//se houver caracteres restantes em binario, tratar eles e salvar 2 bytes correspentes ao restante e quanto sera eliminado
						while(strlen(binario) < 8){
							//preenche com '0' enquanto binario tiver menos q 8 caracteres
							binario[strlen(binario)+1] = '\0';							
							binario[strlen(binario)] = '0';
							restante++; 				
						}
						binario[strlen(binario)] = '\0';
												
						salvar(fptrDestino, binario);
						salvar(fptrDestino, decimal_to_binary(restante));

					}else{
						//se nao houver caracteres restantes, salvar '0000 0000' no arquivo
						salvar(fptrDestino, decimal_to_binary(0));
					}					
					break;
				}
		
				//concatena representacao do char em binario
				strcat(binario, tabela[ch].binario);
	
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
			/*
			se pudermos salvar o binario, salvar e resetar a string
			*/
			salvar(fptrDestino, binario);
			binario[0] = '\0';		
		}
	}

	fechar_arquivo(fptrDestino);
}

/*
	auxiliar a funcao de criar_binario(), converte uma string binario pra int e salva no arquivo
*/
void salvar(FILE *fptr, char *binario){
	int temp = strtol(binario,0,2);
	putc(temp, fptr);				
}


/*
	le o arquivo binario e o salva como txt
*/
void descompactar(FILE *fptr, pHeap *no){
	
	int ch, ch1, ch2;

	FILE *fptrNovo;
	//TODO utilizar abrir_arquivo() ??
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
	}
	ch1 = fgetc(fptr);
	if(ch1 == EOF){
		printf("error");	
	}
	while(1){
			
		/*
			ler sempre 2 CHARs a frente para garantir q ira realizar a leitura do ultimo byte corretamente
		*/

		ch2 = fgetc(fptr);

		//se EOF realizar instrucao especifica
		if(ch2 == EOF){
			/*
			remove quantidade de CHARs de 'ch' sobressalentes com base no valor de 'ch1'
			*/ 
			binario = decimal_to_binary(ch);
			j = 9 - ch1;			
			while(ch1 > 0){
				binario[strlen(binario)-1] = '\0';
				ch1--;			
			}
			i = 0;
			while(i < j){
				//percorre a arvore com o restante de 'ch'
				if(aux->caractere != -1 ){
					putc(aux->caractere, fptrNovo);	
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

		//converte o char lido para uma string binaria
		binario = decimal_to_binary(ch);	
		i = 0;
		while(i < 8){
			/*
				le os 8 caracteres da string e os utiliza pra percorrer a arvore
			*/			
			if(aux->caractere != -1 ){
				putc(aux->caractere, fptrNovo);				
				aux = no;
			}else{
				if(binario[i] == '1'){
					aux = aux->direita;
				}else{
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


/*
	funcao auxiliar para fazer a conversao de decimal pra binario
*/
char *decimal_to_binary(int n){
   int c, d, count;
   char *pointer;
   
   count = 0;
   pointer = (char*)malloc(8+1);
   
   if (pointer == NULL)
      printf("error");
     
   for (c = 7 ; c >= 0 ; c--){
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
