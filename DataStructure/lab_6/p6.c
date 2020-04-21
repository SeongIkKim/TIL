#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;

typedef struct AVLNode{
	int data;
	AVLTree left;
	AVLTree right;
	int height;
}Node;

AVLTree CreateNode(int X){
	Node *N = (Node*)malloc(sizeof(Node));
	N->data = X;
	N->left = N->right = NULL;
	N->height = 0;
	
	return N;
}

// 높이를 구하는 함수
int Height(Position P){
	if(P==NULL){
		return -1;
	}
	else{
		return P->height;
	}
};

// 회전
Position SingleRotateWithLeft(Position K){
	
};

Position SingleRotateWithRight(Position K){
	
};

Position DoubleRotateWithLeft(Position K){
	
};

Position DoubleRotateWithRight(Position K){
	
};

// 삽입
AVLTree Insert(int X, AVLTree T){
	
};

// 중위순회
void PrintInorder(AVLTree T, FILE *fp){
	if (T != NULL){
		PrintInorder(T->left,fp);
		fprintf(fp,"%d(%d) ",T->data,Height(T));
		PrintInorder(T->right,fp);
	}
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
	
	// fprintf(fp2,"%s",buffer);
	
	char *str_dataSet[100] = {NULL,};
	
		
	int i=0;
	char *str_data = strtok(buffer, " ");
	
	while (str_data){
		str_dataSet[i] = str_data;
		i++;
		str_data = strtok(NULL, " ");
	}
	
	AVLTree root = CreateNode(atoi(str_dataSet[0]));
	
	for (i=0; str_dataSet[i]!=NULL; i++){
		int data = atoi(str_dataSet[i]);
		if(i==0){
			continue;
		}
		else{
			Insert(data,root);
		}
		PrintInorder(root,fp2);
		fprintf(fp2,"\n");
	}

	
	
	
	
	fclose(fp1);
	fclose(fp2);
}