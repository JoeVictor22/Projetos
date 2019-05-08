#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


int *frequencia;

void *criar_vetor_frequencia(FILE *fptr, int tamanho);

FILE *abrir_arquivo();
void fechar_arquivo(FILE *fptr);

char *decimal_to_binary(int n);
char * reverse( char * s );
void printar_valores_arvore(pHeap *arvore_frequencia);

/*
- quando referenciar CHARSET_SIZE usar menor ou igual

*/
pHeap *gera_arvore_de_frequencia(pHeap *arvore_frequencia);

//------------FREQUENCE_HUFFMAN-----------//
pHeap *gera_monte(pHeap *no, int qnt_caracteres);
pHeap *insere_no(pHeap *no1, pHeap *no2);
void sort(pHeap *vetor[], int j, int i);
//------------FREQUENCE_HUFFMAN_FIM-------//

//------------CONVERSAO_HUFFMAN----------//
int converter(pHeap *no, char *binario, int *i);
//--------CONVERSAO_HUFFMAN_FIM----------//

int main(){

	//AAAAABBCCCCDEEEEEEE
	/*
	vai ter q receber o vetor de 255 com as frequencias e criar um vetor auxiliar sempre q existir algum valor
	*/
	
	//vetor text desnecessario
	int i;
	//qnt_caracteres usados




	pHeap *arvore_frequencia = NULL;
	
	//HEAP_MAX de fato o max do CHARSET
	arvore_frequencia = gera_arvore_de_frequencia(arvore_frequencia);

	em_ordem(arvore_frequencia);

	//printf("45 tem q ser A, logo : %d\n", arvore_frequencia->esquerda->caractere);

	char palavra[18] = "110011011001011110";
	printf("\n\nconversao\n");
	printf("string : %s", palavra);
	printf("\nSaida\n");
	i = 0;
	int letra;	
	// i < strlen
	while(i < 18){
		letra = converter(arvore_frequencia,palavra,&i);
		printf("%c ", letra);
		
	}
	
	printf("\n");
	printf("\n");
	printar_valores_arvore(arvore_frequencia);
	
	return 0;
}




pHeap *gera_arvore_de_frequencia(pHeap *arvore_frequencia){
	
	int i;
	int qnt_caracteres;
	FILE *fptr = abrir_arquivo();
	criar_vetor_frequencia(fptr, CHARSET_SIZE);
	printf("comecou\n");
	printf("vetor de frequencia\n");
	for(i = 0; i <= CHARSET_SIZE ; i++){
		printf("%d - %c\n",frequencia[i], i );
		
	}
	printf("fim");

	
	for(i = 0, qnt_caracteres = 0; i <= CHARSET_SIZE; i++){
		if(frequencia[i] > 0){
			
			//enviar o valor de I ao inves do text[i]
			arvore_frequencia = inserir(arvore_frequencia, i, frequencia[i]);
			qnt_caracteres++;	
		}else if(frequencia[i] == 0){
			printf("foi zero na posicao %d\n", i);
		}
		
	}
	
	arvore_frequencia = gera_monte(arvore_frequencia, qnt_caracteres);
	em_ordem(arvore_frequencia);
	printf("\n");
	fechar_arquivo(fptr);
	return arvore_frequencia;
}





/*
- A arvore a ser utilizada deve estar em ordem crescente de frequencias
- Cada n? criado, sendo ele a soma de duas folhas, deve possuir charater = NULL, indicando
que ele ? um n? interno
*/
//------------PRIORIDADE_HUFFMAN------------//


pHeap *gera_monte(pHeap *raiz, int qnt_caracteres){

	pHeap *no = raiz;

	/*INI
	- cria um vetor auxiliar para ser realizado as alteracoes na arvore
	*/
	
	//ao inves de HEAP_MAX, utilizar uma contagem referente ao tanto de caracteres existentes no texto
	pHeap *vetor[qnt_caracteres];
	pHeap *aux;
	int i;
	for(i = 0; i < qnt_caracteres; i++){
        aux = no->direita;
        no->direita = NULL;
		vetor[i] = no;
		no = aux;

	}

	/*
	//print
	printf("\nvetor incial: ");
	for(i = 0; i <  HEAP_MAX; i++){
		printf(" %d - %c,", vetor[i]->frequencia, vetor[i]->caractere);
	}

	printf("\n\n\n");
	*/

	/*insert
	- soma os nos ate que o vetor so contenha 1 unico no
	*/

	//ao inves de HEAP_MAX, utilizar uma contagem referente ao tanto de caracteres existentes no texto
	int j = qnt_caracteres-1;
	for(i = 0; i < j; i++){
        vetor[i+1] = insere_no(vetor[i], vetor[i+1]);
		sort(vetor, j, i+1);

	}
    em_ordem(vetor[j]);
	return vetor[j];
}

pHeap *insere_no(pHeap *no1, pHeap *no2){
	pHeap *no;
	no = (pHeap*)malloc(sizeof(pHeap));

	no->esquerda = no1;
	no->direita = no2;
	no->frequencia = no1->frequencia + no2->frequencia;
	no->caractere = -1;
	//printf("no interno criado : %d - %c, a partir de : |%d - %c| e |%d - %c|\n",no->frequencia, no->caractere, no1->frequencia, no1->caractere, no2->frequencia, no2->caractere);

	return no;
}


//nao precisa passar j se tamanho for definido em HEAP_MAX
void sort(pHeap *vetor[], int j, int i){
	//int aux = temp->frequencia;
	pHeap *temp = vetor[i];
	/*
	printf("\nvalor a ser ordenado : %d\n", temp->frequencia);
	int l;
	printf("vetor : nao ordenado");
	for(l = i; l <=  j; l++){
		printf(" %d - %c,", vetor[l]->frequencia, vetor[l]->caractere);
	}
	printf("\n");
	*/

	int aux = temp->frequencia;
	while(i < j && aux >= vetor[i+1]->frequencia){
		vetor[i] = vetor[i+1];
		i++;
	}
	vetor[i] = temp;

	//printf("valor a ser substittuido %d = %d\n", vetor[i]->frequencia, temp->frequencia);

	/*

	printf("vetor ordenado: ");
	for(l = i-2; l <=  j; l++){
		printf(" %d - %c,", vetor[l]->frequencia, vetor[l]->caractere);
	}
	printf("\n\n");

	*/

}


//------------PRIORIDADE_HUFFMAN_FIM--------//

//-------------CONVERSAO_HUFFMAN-----------//

int converter(pHeap *no, char *binario, int *i){
	//printf("comecou");
	if(no == NULL){
		printf("nao existe\n\n");
		return -1;
	}else{
		if(no->caractere == -1 ){
		//printf("foi s\n");
			if(binario[*i] == '0'){
				printf("esquerda, ");
				*i = *i+1;
				converter(no->esquerda, binario, i);
			}else{
				printf("direita, ");
				*i = *i+1;
				converter(no->direita, binario, i);
			}
		}else{
			//printf("achou\n");
			//printf("no acessado %d - %c\n", no->frequencia, no->caractere);
			return no->caractere;
		}
				
	}
	

}

//-----------CONVERSAO_HUFFMAN_FIM-----------//


//-------------FREQUENCIA_ARQUIVO-----------//

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

void *criar_vetor_frequencia(FILE *fptr, int tamanho){

	//inicializacao do vetor
	frequencia = malloc(tamanho * sizeof(int));
	
	int i;
	//zerar vetor
	for(i = 0; i <= tamanho; i++){
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
	
 
}

//----------FREQUENCIA_ARQUIVOFIM-----------//


///testes


char *decimal_to_binary(int n)
{
   int c, d, count;
   char *pointer;
   
   count = 0;
   pointer = (char*)malloc(8+1);
   
   if (pointer == NULL)
      printf("error");
     
   for (c = 6 ; c >= 0 ; c--)
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

char * reverse( char * s )
{
    int length = strlen(s) ;
    int c, i, j;

    for (i = 0, j = length - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }

    return s;
}

void printar_valores_arvore(pHeap *arvore_frequencia){
	
	char *bin;
	int i;
	int letra;
	int j = 0;
	for(i = 0; i < 10;i++){
		bin = decimal_to_binary(i);
		//printf("%s\n", bin);
		
		bin = reverse(bin);
		
		//printf("%s", bin);
		letra = converter(arvore_frequencia, bin, &j);
		if(letra > -1){
			printf("\n%c", letra);
		}else{
			printf("ERROR");
		}
		printf("\n");
	}
}
