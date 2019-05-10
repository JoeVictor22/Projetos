#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void escrever(unsigned char valor, FILE *fptr);
unsigned char ler(FILE *fptr);

int main(){

   FILE *fptr;
   fptr = fopen("saida.huff","wb+");

   if (fptr == NULL){
       printf("Error! opening file");
       exit(1);
	}
   
	

	int i;
	

	printf("\n");

	char data[16] = "0001010110100011";
	
	char aux[8];
	int j = 0;

	int k;
	for(k = 0; k < strlen(data)/8; k++){		
		for(i = 0; i < 8; i++){
			printf("q");		
			aux[i] = data[j++];		
		}
		
		printf("\naux :%s \ni = %d\n", aux, k);

		unsigned char temp = strtol(aux,0,2);
		escrever(temp, fptr);

		printf("temp = %c, %d\n", temp, temp);	
	
	}

	fseek(fptr, 0,SEEK_SET);


	printf("\nfim\n\n");
	for(i = 0; i < 2; i++){
		printf("%d - %c, ",ler(fptr));
	}

	printf("\n");



	
    fclose(fptr);
	

	return 0;
}


void escrever(unsigned char valor, FILE *fptr){

	fwrite(&valor, sizeof(unsigned char), 1, fptr);

}

unsigned char ler(FILE *fptr){
	unsigned char aux;	
	fread(&aux, sizeof(unsigned char), 1, fptr);	
	return aux;	
}

