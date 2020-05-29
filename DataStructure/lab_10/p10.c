#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Graph{
	int size;
	int* node;
	int** matrix;
}Graph;

typedef struct Queue{
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
}Queue;


// 노드 이용하여 그래프 만들기
Graph CreateGraph(int *nodes, int size){
	Graph G;
	
	G.node = nodes;
	G.size = size;
	G.matrix = (int**)malloc(sizeof(int*)*G.size);
	int i,j;
	for (i=0; i<G.size; i++){
		G.matrix[i] = (int*)malloc(sizeof(int)*G.size);
	}
	
	for (i=0; i<G.size; i++){
		for (j=0; j<G.size; j++){
			G.matrix[i][j] = 0;	
		}
	}
	
	return G;
};

// 그래프에 엣지추가
void InsertEdge(Graph G, int a, int b){
	int i;
	int from, to;
	
	for (i=0;i<G.size;i++){
		if (G.node[i] == a){from = i;}
		if (G.node[i] == b){to = i;}
	}
	
	// printf("%d:%d, %d:%d\n",a,from,b,to);
	
	G.matrix[from][to] = 1;
};

// 위상 정렬 후 프린트
void TopSort(Graph G){
	
};

// X사이즈의 Queue 생성
Queue MakeNewQueue(int X){
	Queue Q;
	Q.first = 0;
	Q.rear = -1;
	Q.qsize = 0;
	Q.max_queue_size = X;
	Q.key = (int*)malloc(sizeof(int)*Q.max_queue_size);
	
	return Q;
};

// Queue의 rear에 새로운 element 추가
void Enqueue(Queue *Q, int X){
	Q->key[++(Q->rear)] = X;
	Q->qsize++;
	
	// int i;
	// printf("now queue ");
	// for(i=Q->first;Q->key[i];i++){
	// 	printf("%d ",Q->key[i]);
	// }
	// printf("\n");
};

// Queue의 front에 node를 빼낸다
void Dequeue(Queue *Q){
	int pop = Q->key[Q->first++];
	Q->qsize--;
	
	// printf("pop %d \n",pop);
	
	// int i;
	// printf("now queue ");
	// for(i=Q->first; Q->key[i] ;i++){
	// 	printf("%d ",Q->key[i]);
	// }
	// printf("\n");
};

void PrintMatrix(Graph G,FILE *fp){
	int i,j;
	fprintf(fp,"  ");
	for(i=0;i<G.size;i++){
		fprintf(fp,"%d ",G.node[i]);
	};
	fprintf(fp,"\n");
	for(i=0; i<G.size ; i++){
		fprintf(fp,"%d ",G.node[i]);
		for (j=0; j<G.size; j++){
			fprintf(fp,"%d ",G.matrix[i][j]);
		}
		fprintf(fp,"\n");
	}

};

int main(){
	FILE *input; 
	FILE *output;
	char buffer[100];
	int i,j,k;
	
	input = fopen("input.txt", "r");
	if (input == NULL){
		printf("error");
		return -1;
	}
	
	output = fopen("output.txt", "wt");
	
	/* 그래프 생성 */
	fgets(buffer, sizeof(buffer), input);
	
	int vertices[15] = {0,};
	char *vertex = strtok(buffer, " ");
	
	for(i=0; vertex != NULL; i++){
		vertices[i] = atoi(vertex);
		vertex = strtok(NULL, " ");
	}
	vertices[i] = '\0';
	
	Graph G = CreateGraph(vertices, i);
	
	
	/* 엣지 삽입 */
	
	fgets(buffer, sizeof(buffer), input);
	
	char *edge = strtok(buffer, " ");
	char *edges[225] = {NULL,};
	
	for(i=0; edge != NULL; i++){
		edges[i] = edge;
		// printf("%s ",edges[i]);
		edge = strtok(NULL, " ");
	}
	printf("\n");
	
	for(i=0; edges[i] != NULL; i++){
		int from = atoi(strtok(edges[i],"-"));
		int to = atoi(strtok(NULL," "));
		InsertEdge(G,from,to);
	}
	
	Queue Q = MakeNewQueue(G.size);
	
	Enqueue(&Q,3);
	Enqueue(&Q,4);
	
	Dequeue(&Q);
	Dequeue(&Q);
	
	

	
	
	
	
	PrintMatrix(G,output);
	
	
	fclose(input);
	fclose(output);
}



