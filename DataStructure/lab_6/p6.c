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
		// NULL 노드일 경우에 높이를 -1로 표시하여 리프노드와 구별한다
		return -1;
	}
	else{
		return P->height;
	}
};

int Max(int a, int b){
	if (a>b){
		return a;
	}else{
		return b;
	}
};

// 회전
Position SingleRotateWithLeft(Position K2){
	printf("싱글로테이트 진입");
	Position K1 = K2->left;
	
	K2->left = K1->right; // K1의 오른쪽에 붙어있던 y자리를 K2의 왼쪽에 붙도록 옮긴다
	K1->right = K2; // K1을 루트로 바꾸고 K2를 K1의 오른쪽에 붙인다.
	
	K2->height = Max(Height(K2->left),Height(K2->right))+1;
	K1->height = Max(Height(K1->left),Height(K1->right))+1;
	
	printf("T:%d Height:%d\n    ",K1->data,K1->height);
	printf("left height: %d, right height: %d\n",Height(K1->left),Height(K1->right));
	
	printf("싱글로테이트 끝");
	return K1;
};

Position SingleRotateWithRight(Position K2){
	printf("싱글로테이트 진입");
	Position K1 = K2->right;
	
	K1->left = K2->right; // K1의 왼쪽에 붙어있던 y자리를 K2의 오른쪽에 붙도록 옮긴다
	K1->left = K2; // K1을 루트로 바꾸고 K2를 K1의 오른쪽에 붙인다.
	
	K2->height = Max(Height(K2->left),Height(K2->right))+1;
	K1->height = Max(Height(K1->left),Height(K1->right))+1;
	
	printf("T:%d Height:%d\n    ",K1->data,K1->height);
	printf("left height: %d, right height: %d\n",Height(K1->left),Height(K1->right));
	
	printf("싱글로테이트 끝");
	return K1;
};

Position DoubleRotateWithLeft(Position K3){
	Position K1 = K3->left;
	// Position K2 = K1->right; // K2는 명시적으로 K1->right이지만, 코드 내에서 사용하지는 않음
	
	K3->left = SingleRotateWithRight(K1); // K1과 K2 rotate하여 K3에 붙이기
	
	return SingleRotateWithLeft(K3);	// K3와 K2 rotate하여 K3대신 새 root가 된 K2 반환하기
};

Position DoubleRotateWithRight(Position K3){
	Position K1 = K3->right;
	// Position K2 = K1->left; // K2는 명시적으로 K1->left이지만, 코드 내에서 사용하지는 않음
	
	K3->right = SingleRotateWithLeft(K1); // K1과 K2 rotate하여 K3에 붙이기
	
	return SingleRotateWithRight(K3);	// K3와 K2 rotate하여 K3대신 새 root가 된 K2 반환하기
};

// Rotate를 이용하여 밸런스를 잡아주는 함수
AVLTree reballancing(int X, AVLTree T){
	printf("T:%d에 %d를 넣으려고 합니다 ////",T->data, X);
	if (Height(T->left) - Height(T->right) == 2){	// 왼쪽 subtree가 오른쪽 subtree보다 2만큼 더 높을 경우
		printf("1\n");
		if(X < T->left->data){
			// T기준 트리가 왼쪽-왼쪽 연결형태
			T = SingleRotateWithLeft(T);
		}else{
			// T기준 트리가 왼쪽-오른쪽 연결 형태
			T = DoubleRotateWithLeft(T);
		}
	}else if (Height(T->right) - Height(T->left) == 2){	// 오른쪽 subtree가 왼쪽 subtree보다 2만큼 더 높을 경우
		printf("2\n");
		if(X > T->right->data){
			// T기준 트리가 오른쪽-오른쪽 연결형태
			T = SingleRotateWithRight(T);
		}else{
			// T기준 트리가 오른쪽-왼쪽 연결 형태
			T = DoubleRotateWithRight(T);
		}
	}else{
		// 밸런싱이 필요없는 경우 아무 처리도 하지 않는다
		printf("3\n");
		printf("left:%d  right:%d\n",Height(T->left),Height(T->right));
	}
	T->height = Max(Height(T->left), Height(T->right))+1;
	printf("T:%d height:%d ////",T->data,Height(T));
	return T;
}

// 삽입
AVLTree Insert(int X, AVLTree T,FILE *fp){
	if (T == NULL){
		// 빈 트리일 경우 T를 루트로 만들어준다
		T = CreateNode(X);
	}
	else if(X < T->data){	
		T->left = Insert(X, T->left, fp);
		T = reballancing(X,T);
	}
	else if (X > T->data){
		T->right = Insert(X, T->right, fp);
		T = reballancing(X,T);
	}
	else {
		// X와 같은 T data가 있을경우
		fprintf(fp, "%d already in the tree!\n",X);
	}
	
	// printf("%d",T->height);
	return T;
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
	PrintInorder(root,fp2);
	fprintf(fp2,"\n");
	
	for (i=0; str_dataSet[i]!=NULL; i++){
		int data = atoi(str_dataSet[i]);
		if(i==0){
			continue;
		}
		else{
			printf("insert 한번 시작\n");
			root = Insert(data,root,fp2);
			printf("insert 한번 끝\n");
		}
		PrintInorder(root,fp2);
		fprintf(fp2,"\n");
	}

	
	
	
	
	fclose(fp1);
	fclose(fp2);
}