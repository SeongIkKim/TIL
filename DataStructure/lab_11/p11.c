#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INF 99999

typedef struct Node{
	int key; // 해당 노드의 데이터 값 
	int isPerm; // 확정된 노드값인지에 대한 상태
}Node;

// typedef struct Edge{
// 	int from;
// 	int to;
// 	int weight;
// }Edge;

typedef struct Heap{
	int capacity;
	int size;
	Node* element;
}Heap;

/* specifications */

// 최소힙 만들기
Heap* createMinHeap(int heapSize){
	
};

// 힙에 vertex 삽입
void insert(Heap *minHeap, int vertex, int distance){
	
};

// 힙에서 가장 작은 거리를 가진 노드를 빼낸다.
int deleteMin(Heap *minHeap){
	
};

// 최단경로 프린트
void printShortestPath(int *pred){
	
};

int** createAdjMat(int vSize){
	int i,j;
	int **AdjMatrix = malloc(sizeof(int*)*vSize);
	for(i=0;i<vSize;i++){
		AdjMatrix[i] = (int*)malloc(sizeof(int)*vSize);
	}
	
	for(i=0;i<vSize;i++){
		for(j=0;j<vSize;j++){
			AdjMatrix[i][j] = INF;
			// printf("%d ",AdjMatrix[i][j]);
		}
		// printf("\n");
	}
	
	return AdjMatrix;
};

/* 추가 함수 */

// 인접행렬에 edge 추가
void insertEdge(int** adjMat, Node* V, int vSize, int from, int to, int weight){
	int i;
	int u,v;
	
	for (i=0; i<vSize; i++){
		if (V[i].key == from){u = i;}
		if (V[i].key == to){v = i;}
	}
	
	adjMat[u][v] = weight;
	
	return;
};

// 인접행렬 프린트
void printAdjMat(int** w, int vSize){
	int i,j;
	
	for (j=0;j<vSize;j++){
		printf("%d ",j);
	}
	printf("\n");
	for(i=0;i<vSize;i++){
		
		printf("%d ",i);
		for(j=0;j<vSize;j++){
			printf("%d ",w[i][j]);
		}
		printf("\n");
	}
};

// 다익스트라 알고리즘
int** Dijkstra(Node* s, Node* goal, int vSize, int** adjMat){
	int* d = (int*)malloc(sizeof(int)*vSize);
	Node* pred = (Node*)malloc(sizeof(Node)*vSize);
	int** w = adjMat;
	
	
	
};


	
int main(){
	FILE *input; 
	FILE *output;
	char buffer[500];
	int i,j;
	
	input = fopen("input.txt", "r");
	if (input == NULL){
		printf("error");
		return -1;
	}
	
	output = fopen("output.txt", "wt");
	
	/* Line 1 처리 - vertices 만들기 */ 
	fgets(buffer, sizeof(buffer), input);
	
	Node* vertices = (Node*)malloc(sizeof(Node)*100);
	char *vertex = strtok(buffer, " ");
	
	for(i=0; vertex != NULL; i++){
		vertices[i].key = atoi(vertex);
		vertices[i].isPerm = 0;
		vertex = strtok(NULL, " ");
	}
	int vSize = i;
	
	int* V = (int*)malloc(sizeof(int)*vSize); // 노드들의 키만 따로 저장해두는 배열
	for (i=0; i<vSize; i++){
		V[i] = vertices[i].key;
	}
	
	// for(i=0; i<vSize; i++){
	// 	printf("%d ",vertices[i].key);
	// }
	// printf("%d",vSize);
	
	
	
	/* Line 2 처리 - edges 만들기 */
	fgets(buffer, sizeof(buffer), input);
	
	int** w = createAdjMat(vSize);
	
	// Edge* edges = (Edge*)malloc(sizeof(Edge)*300);
	char* charEdges[300] = {NULL,};
	char* edge = strtok(buffer, " ");
	
	for (i=0; edge != NULL; i++){
		charEdges[i] = edge;
		edge = strtok(NULL, " ");
	}
	int eSize = i;
	
	for (i=0; i<eSize; i++){
		int from = atoi(strtok(charEdges[i],"-"));
		int to = atoi(strtok(NULL,"-"));
		int weight = atoi(strtok(NULL," "));
		
		insertEdge(w,vertices,vSize,from,to,weight);
	}
	
	/* Line 3 처리 - start와 end 정보 가져오기 */
	fgets(buffer, sizeof(buffer), input);
	
	int start = atoi(strtok(buffer, " "));
	int end = atoi(strtok(NULL," "));
	
	int a,b;
	for (i=0;i<vSize; i++){
		if (V[i] == start){a = i;}
		if (V[i] == end){b = i;}
	}
	
	// Dijkstra(vertices[a],vertices[b], )
	
}