/*
Algoritmo de Kruskal com Union-find simples
*/


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 


/*casos de teste
4 5
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4
 = 19

7 12
1 3 6 
1 4 9 
2 3 17 
2 5 32 
2 7 27 
3 4 11 
3 5 4 
4 5 3 
4 6 19 
5 6 13 
5 7 15 
6 7 5
 = 48

3 3
0 1 2 
1 2 1 
2 0 3
 = 3
*/

struct Aresta{ 
    int origem, destino, distancia; 
}; 
  
struct Grafo{ 
    // V-> numero de vertices, A-> numero de arestas 
    int V, A; 
    struct Aresta* aresta; 
}; 
  
//aloca memoria para o grafo e tds as arestas necessarias
struct Grafo* criarGrafo(int V, int A) { 
    struct Grafo* grafo = (struct Grafo*)malloc(sizeof(struct Grafo));
    grafo->V = V; 
    grafo->A = A; 
	grafo->aresta = (struct Aresta*)malloc(A*sizeof(struct Aresta));
     
    return grafo; 
} 
  

int find(int parent[], int i) { 
    //procura raiz
    if (parent[i] == -1) 
        return i; 
    return find(parent, parent[i]); 

} 
void Union(int parent[], int x, int y){
	//define uma relacao entre dois pontos
   	int xset = find(parent, x); 
    int yset = find(parent, y); 
    if(xset!=yset){ 
       parent[xset] = yset; 
    } 
    
} 

//funcao para auxiliar o quicksort nativo de C
int Compara(const void* a, const void* b) {     
    struct Aresta* a1 = (struct Aresta*)a; 
    struct Aresta* b1 = (struct Aresta*)b; 
    return a1->distancia > b1->distancia; 
} 
  


void Kruskal(struct Grafo* grafo) { 
    int V = grafo->V; 
	//aresta inicial que ira armazenar a MST do grafo original
    struct Aresta* resultado = (struct Aresta*)malloc(V*sizeof(struct Aresta)); 
  	// e = indexacao para o grafo resultado
	int e = 0; 
	// i = indexacao para o grafo original ordenado
    int i = 0;   
  	int soma = 0;
  
	//ordena em ordem crescente
    qsort(grafo->aresta, grafo->A, sizeof(grafo->aresta[0]), Compara); 
  
	//alocacao de memoria para o union find e memset para indicar q tds as arestas sao inicialmente, arestas raizes
    int *parent = (int*) malloc( grafo->V * sizeof(int) ); 
    memset(parent, -1, sizeof(int) * grafo->V); 



	//v - 1 é o numero de arestas a serem encontradas    
    while (e < V - 1) { 
        //pega a menor aresta, ja que esta ordenado
        struct Aresta prox_aresta = grafo->aresta[i++]; 

        int x = find(parent, prox_aresta.origem); 
        int y = find(parent, prox_aresta.destino); 
  
		//se nao houver ciclo, acrescenta ao grafo final, e aumenta e
        if (x != y){ 
            resultado[e++] = prox_aresta; 
            Union(parent, x, y); 
        } 
		//se houver ciclo incrementa i, e descarta essa aresta da grafo original
    } 
   

	printf("orig, \tdest, \tdist\n");
    for (i = 0; i < e; ++i){ 
    	soma = soma + resultado[i].distancia;
		printf("%d, \t%d, \t%d\n", resultado[i].origem,resultado[i].destino,resultado[i].distancia );		
	}    	
	printf("distancia total : %d\n",soma); 
	 
} 



int main(){ 

	int V, A, orig, dest, dist, cont=0;
	scanf("%d %d", &V, &A);
	struct Grafo* grafo = criarGrafo(V, A);

	//entrada do grafo
	while(A--){
		scanf("%d %d %d", &orig, &dest, &dist);
		grafo->aresta[cont].origem = dest; 
		grafo->aresta[cont].destino = orig; 
		grafo->aresta[cont].distancia = dist; 
		cont++;
	}


	Kruskal(grafo); 
	free(grafo);
	free(aresta);

	return 0; 
} 
