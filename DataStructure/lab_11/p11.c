#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INF 99999

typedef struct Node{
	int key; // 해당 노드의 데이터 값 
	int weight; // source에서 해당 노드까지의 거리(distance)
}Node;

typedef struct Heap{
	int capacity;
	int size;
	Node* elements;
}Heap;

int keyToIndex(int key, Node* vertices, int vSize);

/* specifications */

// 최소힙 만들기
Heap* createMinHeap(int heapSize){
	Heap* minHeap = (Heap*)malloc(sizeof(Heap));
	minHeap->capacity = heapSize;
	minHeap->size = 0;
	minHeap->elements = (Node*)malloc(sizeof(Node)*heapSize);
	
	return minHeap;
};

// 힙에 vertex 삽입
void insert(Heap *H, int vertex, int distance){
	int i;
	
	Node newVertex;
	newVertex.key = vertex;
	newVertex.weight = distance; 
	
	// percolate up
	for (i=++H->size; i/2 != 0 && H->elements[i/2].weight > newVertex.weight ; i /= 2){
		H->elements[i] = H->elements[i/2];
	}
	H->elements[i] = newVertex;
	// printf("new vertex inserted : key(%d), distance(%d)\n",H->elements[i].key ,H->elements[i].weight);
	
	return;
};



// 힙에서 가장 작은 거리를 가진 노드를 빼낸다.
int deleteMin(Heap *H){
	Node result = H->elements[1]; // min을 빼둔다
	H->elements[1] = H->elements[H->size--]; // 가장 아래쪽에 있는놈을 루트자리로 올린다
	Node temp = H->elements[1];
	
	int i;
	
	int child;
	// percolate down
	for (i=1; i*2 <= H->size ; i = child){
		child = i*2;
		// 두 children(leftchild(i*2), rightchild(i*2+1)) 중 더 작은녀석을 child로 할당하기
		if (child != H->size && H->elements[child+1].weight < H->elements[child].weight){
			child++;
		}
		if(temp.weight > H->elements[child].weight){ // percolate down할 노드와 후손노드들을 비교하여 percolate down할 노드가 들어갈 위치(i)를 찾기
			H->elements[i] = H->elements[child];
		}
		else{
			break;
		}
	}
	H->elements[i] = temp; // 빼놓았던 root를 percolate down하여 찾은 위치에 넣어놓는다.
	
	// printf("Delete min : key(%d) weight(%d)\n",result.key,result.weight);
	
	return result.key;
};

// 최단경로 프린트(재귀)
void printShortestPath(int *pred, int target,Node* vertices, int vSize, FILE* output){
	int target_index = keyToIndex(target,vertices,vSize);
	if (target != -1){
		printShortestPath(pred, pred[target_index],vertices,vSize,output);
		fprintf(output,"%d ",target); // 재귀로 가장 마지막 pred(즉, source 노드)부터 출력
	}
	else{}
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

int keyToIndex(int key, Node* vertices, int vSize){
	int i;
	
	for (i=0;i<vSize;i++){
		if (vertices[i].key == key){break;}
	}
	
	return i;
}

// 인접행렬에 edge 추가
void insertEdge(int** adjMat, Node* vertices, int vSize, int from, int to, int weight){
	int i;
	int u = keyToIndex(from,vertices,vSize);
	int v = keyToIndex(to,vertices,vSize);
	
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
void Dijkstra(int start,int end, Node* vertices, int vSize, int** w, FILE* output){
	int* d = (int*)malloc(sizeof(int)*vSize);
	int* pred = (int*)malloc(sizeof(int)*vSize);
	
	int s_index = keyToIndex(start,vertices,vSize);
	int e_index = keyToIndex(end,vertices,vSize);
	
	int i,j;
	
	for (i=0;i<vSize;i++){
		d[i] = INF;
		pred[i] = -1;
	}
	d[s_index] = 0;
	
	for (i=0;i<vSize ; i++){
		if (w[s_index][i] != INF){
			d[i] = w[s_index][i];
			pred[i] = start;
		}
	}
	
	Heap* H = createMinHeap(vSize*vSize);
	for (i=0;i<vSize; i++){
		insert(H,vertices[i].key,d[i]);
	}
	
	int pop;
	
	while (H->size != 0){
		pop = deleteMin(H);
		
		int p_index = keyToIndex(pop,vertices,vSize);
		
		// printf("pop : (%d) pop_index : (%d)\n",pop,p_index);
		
		for (i=0;i<vSize; i++){
			if (d[p_index]+w[p_index][i] < d[i]){
				d[i] = d[p_index]+w[p_index][i];
				pred[i] = pop;
				insert(H,vertices[i].key,d[i]);
				// printf("d[v] : ");
				// for(j=0; j<vSize; j++){
				// 	printf("%d ",d[j]);
				// }
				// printf("\n");
			}
		}
	}
	
	printShortestPath(pred,end,vertices,vSize,output);
	
	free(d);
	free(pred);
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
		vertex = strtok(NULL, " ");
	}
	int vSize = i;
	
	
	/* Line 2 처리 - edges 만들기 */
	fgets(buffer, sizeof(buffer), input);
	
	int** w = createAdjMat(vSize);
	
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
	
	/* Dijkstra 수행 */
	
	Dijkstra(start,end,vertices, vSize,w,output);
	
	free(vertices);
}