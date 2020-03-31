#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EmptyTOS -1
#define MAX_ELEMENTS 100

typedef struct StackRecord *Stack;

struct StackRecord {
	int Capacity;
	int TopOfStack;
	int *Array;
};


Stack CreateStack(){
	Stack S;
	
	S = malloc(sizeof(struct StackRecord));
	if(S == NULL){
		printf("Stack - out of space.\n");
	}
	
	S->Array = malloc(sizeof(int)*MAX_ELEMENTS);
	if(S->Array == NULL){
		printf("Stack Array - out of space.\n");
	}
	
	S->Capacity = MAX_ELEMENTS;
	S->TopOfStack = EmptyTOS;
	
	return S;
}

int IsFull(Stack S){
	if (S->TopOfStack == S->Capacity-1){
		printf("IsFull-->return 1\n");
		return 1;
	}
	else {
		printf("IsFull-->return 0\n");
		printf("TopOfStack: %d, Capacity: %d\n",S->TopOfStack, S->Capacity);
		return 0;
	}
}

int IsEmpty(Stack S){
	if (S->TopOfStack == -1){
		printf("IsEmpty-->return 1\n");
		return 1;
	}
	else {
		printf("IsEmpty-->return 0\n");
		return 0;
	}
}


void Push(int X, Stack S){
	if(IsFull(S)){
		printf("Full\n");
	}
	else{
		S->Array[++(S->TopOfStack)];
	}
}

void Pop(Stack S){
	if(IsEmpty(S)){
		printf("Empty\n");
	}
	else{
		printf("%d\n",S->Array[S->TopOfStack]);
		S->TopOfStack--;
	}
}

int main(){
	char buffer[30];
	
	FILE* fp;
	fp = fopen("input3-1.txt","r");
	
	// 파일 라인 체크용 인덱스
	int line= 0;
	
	Stack S = CreateStack();
	
	while(1){
		line++;
		fgets(buffer, sizeof(buffer), fp);
		
		if(feof(fp)){
			break;
		}
		
		if(*(buffer+(strlen(buffer)-1)) == '\n'){
			*(buffer+(strlen(buffer)-1)) == 0;
		}
		
		if(line==1){
			// 몇 번의 push와 pop이 수행될 건지
			int NumOfInst = atoi(buffer);
		}
		else{
			// push or pop용 명령 처리
			char *sArr[2];
			int i = 0;
			char *nowStr = strtok(buffer, " ");
			
			while(nowStr != NULL){
				sArr[i] = nowStr;
				i++;
				nowStr = strtok(NULL, " ");
			}
			
			free(nowStr);
			
			printf("sArr[0] : %s\n",sArr[0]);			

			if(!strcmp(sArr[0],"push")){
				int X = atoi(sArr[1]);
				Push(X, S);
			}
			else if(!strcmp(sArr[0],"pop")){
				Pop(S);
			}
			else{
				printf("Wrong Order.\n");
			}
		}
		
	}
	
	fclose(fp);
		
	return 0;
}