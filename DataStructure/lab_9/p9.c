#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define order 3

typedef struct B_node{
	int n_keys; /*number of keys*/
	struct B_node *child[order];
	int key[order-1];
}Node;

void Insert(int key){
	
};

// 중위순회
void Inorder(Node *root, FILE *fp){
	// if (root != NULL){
		// Inorder(root->child[order],fp);
		// fprintf(fp,"%d ",root->child[0]);
		// Inorder(root->right,fp);
	// }
};

int main(){
	char *buffer;
	int fileSize;
	
	FILE *fp1; // input.txt
	FILE *fp2; // output.txx
	
	fp1 = fopen("input.txt","r");
	if (fp1 == NULL){
		fputs("FILE ERROR",stderr);
		exit(1);
	}
	fp2 = fopen("output.txt","w");
	
	// 파일의 크기를 fileSize 에 저장한다.
	fseek(fp1, 0, SEEK_END); // fp1을 열어 스트림의 위치지정자를 0부터 파일끝까지 이동시킨다
	fileSize = ftell(fp1); // 파일끝의 스트림(즉, 파일의 문자열 크기)을 fileSize에 할당시킨다.
	rewind(fp1); // 다시 파일의 스트림의 위치지정자를 원래대로 돌려놓는다

	// 전체 파일의 내용을 받을 수 있을 정도의 크기로 메모리를 할당한다.
	buffer = (char*)malloc(sizeof(char) * fileSize);
	if (buffer == NULL) {
		fputs("Memory error", stderr);
		exit(2);
	}
	
	// 그 파일의 내용을 버퍼에 저장한다.
  	fread(buffer, 1, fileSize, fp1);
	
	char *instructionSet[30];
	
	char line[10] = {0,};
	
	int i=0; // buffer index
	int j=0; // line index;
	int k=0; // instructionSet index
	
	while(buffer[i] != '\0' || i==fileSize){	// i==fileSize인 경우는 버퍼의 마지막에 도달했을 경우
		if(buffer[i] == '\n' || i==fileSize){
			// 지금까지 들어온 것으로 한 instruction 구성
			line[j] = '\0'; // 이전 instruction의 찌꺼기 buffer를 비우기
			
			// fprintf(fp2,"지금라인:%s\n",line);
			
			// line을 instructionSet으로 동적할당
			instructionSet[k] = (char*)malloc(sizeof(char)*(j-1));
			strcpy(instructionSet[k],line); 
			
			// fprintf(fp2,"%s\n",instructionSet[k]);
			
			k++;
			line[0] = '\0'; // 이번 line의 버퍼를 비우기
			j=0;
		}
		else{
			line[j++] = buffer[i];
		}
		i++;
	}
	
    char *instruction;
    char *valueStr;
    int value;
	
	i=0; // index
	for(i=0; i<k ; i++){
		instruction = strtok(instructionSet[i]," ");
		valueStr = strtok(NULL, "\0");
		
		if (valueStr != NULL){
			value = atoi(valueStr);
		}
		
		if (strcmp(instruction,"i") == 0){
			fprintf(fp2,"insert %d\n",value);
		}
		else if (strcmp(instruction,"p") == 0){
			fprintf(fp2,"print \n");
			fprintf(fp2,"\n");
		}
		else{
			fprintf(fp2,"instruction: %s\n",instruction);
		}
		
		instruction[0] = '\0'; // order buffer 지우기
	}
	fclose(fp1);
	fclose(fp2);
}