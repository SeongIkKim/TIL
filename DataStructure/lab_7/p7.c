#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// 해당 집합의 원소들을 각기 다른 집합으로 초기화한다(0은 루트노드임을 나타낸다)
void Init(int *DS, int n){
	int i;
	for(i = 1; i<=n; i++){
		DS[i] = 0;
	}
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


int main(){
	char buffer[5];
	
	FILE *input;
	FILE *output;
	
	input = fopen("input.txt","r");
	
	fgets(buffer, sizeof(buffer), input);
	
	int size = atoi(buffer);
	
	printf("%d\n",size);
}