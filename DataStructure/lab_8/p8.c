#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct HeapStruct{
	int Capacity;
	int Size;
	int *Elements;
}PriorityQueue;

int isFull(PriorityQueue *H){
	int result = H->Capacity == H->Size ? 1 : 0;
	return result;
}

int Find(int X,PriorityQueue *H){
	int result=0;
	int i =0;
	for (i=1; i<=H->Size; i++){
		if (H->Elements[i] == X){
			result = 1;
			return result;
		}
	}
	return result;
}

void Insert(int X,PriorityQueue *H,FILE *fp){
	int i;
	if (isFull(H)){
		fprintf(fp,"heap is full.\n");
		return;
	}
	
	if (Find(X,H)){
		fprintf(fp,"%d is already in the tree.\n",X);
		return;
	}
	
	// percolating up
	for (i=++H->Size; i/2 != 0 && H->Elements[i/2] < X ; i /= 2){
		H->Elements[i] = H->Elements[i/2];
	}
	H->Elements[i] = X;
	fprintf(fp,"insert %d\n",H->Elements[i]);
	
	return;
}


void Print(PriorityQueue *H,FILE *fp){
	int i;
	for (i=1; i<= H->Size; i++){
		fprintf(fp, "%d ",H->Elements[i]);
	}
}


int main(){
	char *buffer;
	int fileSize;
	
	FILE *input; // input.txt
	FILE *output; // output.txx
	
	input = fopen("input.txt","r");
	if (input == NULL){
		fputs("FILE ERROR",stderr);
		exit(1);
	}
	output = fopen("output.txt","w");
	
	// 파일의 크기를 fileSize 에 저장한다.
	fseek(input, 0, SEEK_END); // input을 열어 스트림의 위치지정자를 0부터 파일끝까지 이동시킨다
	fileSize = ftell(input); // 파일끝의 스트림(즉, 파일의 문자열 크기)을 fileSize에 할당시킨다.
	rewind(input); // 다시 파일의 스트림의 위치지정자를 원래대로 돌려놓는다

	// 전체 파일의 내용을 받을 수 있을 정도의 크기로 메모리를 할당한다.
	buffer = (char*)malloc(sizeof(char) * fileSize);
	if (buffer == NULL) {
		fputs("Memory error", stderr);
		exit(2);
	}
	
	// 그 파일의 내용을 버퍼에 저장한다.
  	fread(buffer, 1, fileSize, input);
	
	// fprintf(output,"%s\n",buffer);
	// fprintf(output,"filesize = %d\n",fileSize);
	
	char *instructionSet[30];
	
	char line[10] = {0,};
	
	int i=0; // buffer index
	int j=0; // line index;
	int k=0; // instructionSet index
	
	while(buffer[i] != '\0' || i==fileSize){	// i==fileSize인 경우는 버퍼의 마지막에 도달했을 경우
		if(buffer[i] == '\n' || i==fileSize){
			// 지금까지 들어온 것으로 한 instruction 구성
			line[j] = '\0'; // 이전 instruction의 찌꺼기 buffer를 비우기
			
			// fprintf(output,"지금라인:%s\n",line);
			
			// line을 instructionSet으로 동적할당
			instructionSet[k] = (char*)malloc(sizeof(char)*(j-1));
			strcpy(instructionSet[k],line); 
			
			// fprintf(output,"%s\n",instructionSet[k]);
			
			k++;
			line[0] = '\0'; // 이번 line의 버퍼를 비우기
			j=0;
		}
		else{
			line[j++] = buffer[i];
		}
		i++;
	}
	
    char *order;
    char *valueStr;
    int value;
	
	
	
	int result;
	
	PriorityQueue *p_Queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	int initSize = atoi(instructionSet[0])+1;
	p_Queue->Capacity = initSize-1;
	p_Queue->Size = 0;
	p_Queue->Elements = (int*)malloc(sizeof(int)*initSize);
	
	
	for(i=1; i<k ; i++){
		order = strtok(instructionSet[i]," ");
		valueStr = strtok(NULL, "\0");
		
		
		if (valueStr != NULL){
			value = atoi(valueStr);
		}
	
		
		if (strcmp(order,"i") == 0){
			Insert(value,p_Queue,output);
		}
		else if (strcmp(order,"f") == 0){
			result = Find(value,p_Queue);
			if (!result){
				fprintf(output,"%d is not in the heap.\n",value);
			}
			else{
				fprintf(output,"%d is in the heap.\n",value);
			}
		}
		else if (strcmp(order,"p") == 0){
			Print(p_Queue,output);
		}
		else{
			fprintf(output,"order: %s\n",order);
		}
		
		order[0] = '\0'; // order buffer 지우기
	}
	fclose(input);
	fclose(output);
}