#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct teste{
	char *caminho;	
}teste;

int main(){
	
	teste *test = (teste*)malloc(sizeof(teste));
	
	test->caminho = (char*)malloc(3 * sizeof(char));
	
	test->caminho[0] = '0';
	test->caminho[1] = '1';
	test->caminho[2] = '\0';
	test->caminho[3] = 'a';
		

	printf("%s\n", test->caminho);
	printf("%c\n", test->caminho[0]);

	

	printf("eoq :%d\n", strlen(test->caminho));	
	
	strcat(test->caminho, "0");

	printf("%s\n", test->caminho);
	printf("%c\n", *test->caminho);



	return 0;
}
