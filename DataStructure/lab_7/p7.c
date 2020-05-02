#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


// 해당 집합의 원소들을 각기 다른 집합으로 초기화한다(0은 루트노드임을 나타낸다)
void Init(int *DS, int n){
	int i;
	for(i = 1; i<=n; i++){
		DS[i] = 0;
	}
}

// random으로 edge를 고르고, 해당 edge를 remove
int *Pick(int edgeSize, int E[edgeSize][2]){
	int x = rand()%edgeSize;
	int arr[2] = {0,0};
	
	while(E[x][0] == 0){
		x = rand()%edgeSize;
	}
	
	// printf("x = %d\n E[x]={%d,%d}\n",x,E[x][0],E[x][1]);
	
	static int choice[2]; // 랜덤 엣지를 뽑아 choice에 저장해둠
	memcpy(choice,E[x],sizeof(E[x]));
	memcpy(E[x],arr,sizeof(arr));
	
	// printf("이건 지워진거 %d,%d\n",E[x][0],E[x][1]);
	
	return choice;
}

// 해당 원소가 속한 집합의 루트노드를 반환하는 함수
int Find(int x,int *DS){
	while(DS[x]>0){
		x = DS[x];
	}
	return x;
}

// 두 집합의 root노드를 받아서 합쳐준다.
void Union(int r1, int r2, int *DS){
	if (DS[r2] < DS[r1]){ // r1집합보다 r2집합의 높이가 더 크다면(높이는 음수이다) r2집합을 베이스로 합친다
		DS[r1] = r2;
	}
	else{
		if (DS[r2] == DS[r1]){ // r1집합과 r2집합의 높이가 같다면, r1집합을 베이스로 합쳤을때 높이가 하나 늘어날 것이다.
			DS[r1]--;
		}
		DS[r2] = r1; // r1집합을 베이스로 합친다
	}
}

void printS(int setSize, int *DS){
	int i;
	for(i=1; i<=setSize;i++){
		printf("%d ",DS[i]);
		// if (i%size == 0){
		// 	printf("\n");
		// }
	}
	printf("\n");
}


int main(){
	char buffer[5];
	
	FILE *input;
	FILE *output;
	
	input = fopen("input.txt","r");
	
	fgets(buffer, sizeof(buffer), input);
	
	int size = atoi(buffer); // Maze 사이즈
	
	// Disjoint Set 구성
	int setSize = size*size;
	int S[setSize+1];  // 0번 인덱스는 사용하지 않으므로 1부터 setSize까지 사용하려면 +1해준다.
	Init(S,setSize);
	
	// 미로의 edge Set 구성
	int edgeSize = 2*size*(size-1);
	int E[edgeSize][2];
	
	int i;
	int count=0; // 마지막칸의 edge를 안넣기 위해 뒷 edge의 index를 당겨오기 위한 변수
	for(i=1;i<=(size*size);i++){ // 세로 edge 추가
		if (i%size != 0){
			E[i-1-count][0] = i ;
			E[i-1-count][1] = i+1;	
		}
		else{
			count++;
		}
	}
	for(i=1; i<=size*(size-1); i++){ // 가로 edge 추가
		E[i+29][0] = i;
		E[i+29][1] = i+size;
	}
	for (i=0; i<edgeSize;i++){
		printf("(%d,%d) ",E[i][0],E[i][1]);
		if (i%size==size-1){
			printf("\n");
		}
	}
	
	srand((unsigned int)time(NULL)); // 난수 seed 생성
	
	int *choice = Pick(edgeSize,E);
	// printf("이건 choice %d,%d\n",choice[0],choice[1]);
	
	
	
	
	
	fclose(input);
}