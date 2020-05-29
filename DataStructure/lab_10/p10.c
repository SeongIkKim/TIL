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

Queue MakeNewQueue(int X);
void Enqueue(Queue *Q, int X);
int Dequeue(Queue *Q);


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
	
	return;
};

void checkIndegree(Graph G,int *inDegree){
	int sum,i,j;
	
	for(i=0;i<G.size;i++){
		sum=0;
		for(j=0;j<G.size;j++){
			sum += G.matrix[j][i];
		}
		inDegree[i] = sum;
	}
};

int *returnAdjacent(Graph G, int X){
	int i,j;
	int *adjacent = malloc(sizeof(int)*G.size);
	
	j=0;
	for(i=0;i<G.size;i++){
		if (G.matrix[X][i] == 1){
			adjacent[j++] = i;
		}
	}
	adjacent[j]='\0';
	
	return adjacent;
}

void bubbleSort(int *number, Graph G){
	int i,j,temp;
	int num = sizeof(number)/sizeof(int);
	for(i = 0 ; i < num ; i ++) {
    	for(j = 0 ; j < num -i -1 ; j ++) {
            if(G.node[number[j]]>G.node[number[j+1]]) {
                temp = number[j];
                number[j] = number[j+1];
                number[j+1] = temp;
         	}
    	}
	}
};

// 위상 정렬 후 프린트

void TopSort(Graph G,FILE *output){
	Queue Q;
	int *inDegree =malloc(sizeof(int)*G.size); // 각 vertex의 inDegree를 담아두는 배열
	int *adjacent; // 인접 노드를 담아두는 포인터
	
	int i,j;
	
	Q = MakeNewQueue(G.size);
	checkIndegree(G,inDegree);
	
	
	// inDegree가 0인 노드들을 array에 넣어놓는다.
	int *array = malloc(sizeof(int)*G.size);
	memset(array, -1, sizeof(int)*G.size);
	j=0;
	for(i=0; i<G.size ; i++){ 
		if (inDegree[i] == 0){
			array[j++] = i;
		}
	}
	
	// array를 sort해서 노드 크기가 작은 순서대로 정렬시킨다
	bubbleSort(array,G);
	
	// 같은 레벨이라면 노드 크기가 작은 순서대로 집어넣는다
	for(i=0; i<G.size;i++){
		if(array[i] != -1){
			Enqueue(&Q,array[i]);
		}
	}
	
	
	fprintf(output,"\n\nTopSort Result: ");
	
	// Queue가 비어있지 않는 한 인접 노드를 계속 넣어준다.
	int pop;
	while(Q.first<Q.max_queue_size){
		pop = Dequeue(&Q);
		// printf("pop: %d \n",G.node[pop]);
		fprintf(output,"%d ",G.node[pop]);
		
		adjacent = returnAdjacent(G,pop);
		memset(array, -1, sizeof(int)*G.size);
		j=0;
		for (i=0; adjacent[i] ; i++){
			inDegree[adjacent[i]]--;
			if (inDegree[adjacent[i]] ==0){
				array[j++] = adjacent[i];	
			}
		}
		bubbleSort(array,G);
		for(i=0; i<G.size;i++){
			if(array[i] != -1){
				Enqueue(&Q,array[i]);
			}
		}
	}

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
	
	// printf("enqueue %d ",X);
	
	// int i;
	// printf("now queue ");
	// for(i=Q->first;Q->key[i];i++){
	// 	printf("%d ",Q->key[i]);
	// }
	// printf("\n");
};

// Queue의 front에 node를 빼낸다
int Dequeue(Queue *Q){
	int pop = Q->key[Q->first++];
	Q->qsize--;
	
	// printf("pop %d ",pop);
	
	// int i;
	// printf("now queue ");
	// for(i=Q->first; Q->key[i] ;i++){
	// 	printf("%d ",Q->key[i]);
	// }
	// printf("\n");
	
	return pop;
};

void PrintMatrix(Graph G,FILE *fp){
	fprintf(fp,"Adjacency matrix\n");
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
	int i,j;
	
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
	
	for(i=0; edges[i] != NULL; i++){
		int from = atoi(strtok(edges[i],"-"));
		int to = atoi(strtok(NULL," "));
		InsertEdge(G,from,to);
	}
	
	PrintMatrix(G,output);
	
	TopSort(G,output);
	
	fclose(input);
	fclose(output);
}



