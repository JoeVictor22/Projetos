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
		
	printf("strlen : %d\n", strlen(test->caminho));
	test->caminho = realloc(test->caminho, (char*)((strlen(test->caminho) + 2 ) * sizeof(char)));
	

	printf("%s\n", test->caminho);
	printf("%c\n", test->caminho[0]);

	

	strcat(test->caminho, "0");

	test->caminho[3] = '\0';

	
	printf("STRLEN 2 :%d\n", strlen(test->caminho));	
	

	printf("%s\n", test->caminho);
	printf("%c\n", *test->caminho);



	return 0;
}
