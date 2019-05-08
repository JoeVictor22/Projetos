#include <stdio.h>
#include <stdlib.h>
#define CHARSET_SIZE 255

int *vetor;

void *vetor_frequencia(FILE *fptr, int tamanho);




int main(){
   int num;
   FILE *fptr;
   fptr = fopen("program.txt","r+");

   long int count=0;
   if (fptr == NULL){
       printf("Error! opening file");
       exit(1);
	}
   
	fseek(fptr, 0,SEEK_SET);

    int i;
	//texto = vetor_frequencia(fptr, CHARSET_SIZE); 
  	vetor_frequencia(fptr, CHARSET_SIZE);
	

	 //PRINT DO VETOR FREQUENCIA
    for(i = 0; i <= CHARSET_SIZE; i++){
    	printf("%d - %c\n", vetor[i], i);
	}
	

	fseek(fptr, 0,SEEK_SET);

    fclose(fptr);
       
   return 0;
}



void *vetor_frequencia(FILE *fptr, int tamanho){

	//inicializacao do vetor
	vetor = malloc(tamanho * sizeof(int));
	
	int i;
	//zerar vetor
	for(i = 0; i <= tamanho; i++){
		vetor[i] = 0;
	}

	int ch;
	//calcular frequencia
	while(1){
		ch = fgetc(fptr);
		
		if(ch==EOF){
			break;
		}		
		vetor[ch]++;	
	}
	
 
}
