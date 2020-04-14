#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode *treeptr;

typedef struct TreeNode{
	int value;
	treeptr *left, *right;
}TreeNode;

// 삽입
TreeNode *InsertNode(int value, TreeNode *root){
	
};

// left subtree중 최댓값을 찾아주는 함수
TreeNode *FindMax(TreeNode *tree){
	
};
	
// 삭제
TreeNode *DeleteNode(int value, TreeNode *root){
	
};

// 탐색
TreeNode *FindNode(int value, TreeNode *root){
	
};

// 중위순회
void PrintInorder(TreeNode *root){
	
};

// 전위순회
void PrintPreorder(TreeNode *root){
	
};

// 후위순회
void PrintPostorder(TreeNode *root){

};

int main(){
	char *buffer;
	int fileSize;
	
	FILE *fp1; // input.txt
	FILE *fp2; // output.txt
	
	fp1 = fopen("input.txt","r");
	if (fp1 == NULL){
		fputs("FILE ERROR",stderr);
		exit(1);
	}
	
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
	
	// printf("%s\n",buffer);
	// printf("filesize = %d\n",fileSize);
	
	char *instructionSet[30];
	
	char line[10] = {0,};
	
	int i=0; // buffer index
	int j=0; // line index;
	int k=0; // instructionSet index
	
	while(buffer[i] != '\0' || i==fileSize){	// i==fileSize인 경우는 버퍼의 마지막에 도달했을 경우
		if(buffer[i] == '\n' || i==fileSize){
			// 지금까지 들어온 것으로 한 instruction 구성
			line[j] = '\0'; // 이전 instruction의 찌꺼기 buffer를 비우기
			
			// printf("지금라인:%s\n",line);
			
			// line을 instructionSet으로 동적할당
			instructionSet[k] = (char*)malloc(sizeof(char)*(j-1));
			strcpy(instructionSet[k],line); 
			
			// printf("%s\n",instructionSet[k]);
			
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

	i=0; // index
	for(i=0; i<k ; i++){
		order = strtok(instructionSet[i]," ");
		valueStr = strtok(NULL, "\0");
		
		if (valueStr != NULL){
			value = atoi(valueStr);
			printf("%d\n",value);
		}
		
	}
}