#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode{
	int value;
	struct TreeNode *left;
	struct TreeNode *right;
}Node;

Node *root = NULL;

// 삽입
Node *InsertNode(int value, Node *root, FILE *fp){
	if (root==NULL){
		root = (Node*)malloc(sizeof(Node));
		root->left = root->right = NULL;
		root->value = value;
		// printf("insert %d\n",value);
		return root;
	}
	else{
		if(root->value > value){
			root->left = InsertNode(value, root->left,fp);
		}
		else if(root->value < value){
			root->right = InsertNode(value, root->right,fp);
		}
		else{
			fprintf(fp,"%d already exists.\n",value);
		}
	}
	return root;
};

// left subtree중 최댓값을 찾아주는 함수
Node *FindMax(Node *root){
	if (root==NULL){
		return NULL;
	}
	Node *tempNode = root->left;
	while(tempNode->right != NULL){
		tempNode = tempNode->right;
	}
	return tempNode;
};
	
// 삭제
Node *DeleteNode(int value, Node *root, FILE *fp){
	
	Node *tempNode = NULL;
	
	if (root == NULL){
		// 찾는 노드가 없을 때
		fprintf(fp,"Deletion failed. %d does not exist.\n",value);
		return NULL;
	}
	
	// 해당 value를 찾아 내려가기
	if (root->value > value){
		root->left = DeleteNode(value, root->left,fp);
	}
	else if (root->value < value){
		root->right = DeleteNode(value, root->right,fp);
	}
	else{	// root->value == value
		// 자식 노드가 두개 있을 때
		if (root->left != NULL && root->right != NULL){
			tempNode = FindMax(root);
			root->value = tempNode->value;	// 원래 root자리에 있던 value를 findMax value로 대체한다
			root->left = DeleteNode(tempNode->value,root->left,fp);	 // root의 left subtree에서 해당 값을 가진 원래의 노드를 삭제한 뒤, left subtree 전체를 반환하여 다시 root->left에 할당한다
			// root->left에 다시 재할당하는 이유를 명확히 이해하자.
		}
		else {
			// 자식노드가 한개 있을때
			if (root->left != NULL ){
				tempNode = root->left;
				free(root);
			}
			else if (root->right != NULL){
				tempNode = root->right;
				free(root);
			}
			else {
				// 자식노드가 없을 때 (리프노드일때)
				free(root);
				// tempNode == NULL
			}
			return tempNode;
		}
		
	}
};

// 탐색
Node *FindNode(int value, Node *root){
	Node *tempNode = root;
	while(tempNode != NULL){
		if (tempNode->value > value){
			tempNode = tempNode->left;
		}
		else if (tempNode->value < value){
			tempNode = tempNode->right;
		}
		else{
			return tempNode;
		}
	}
	return NULL;
};

// 중위순회
void PrintInorder(Node *root, FILE *fp){
	if (root != NULL){
		PrintInorder(root->left,fp);
		fprintf(fp,"%d ",root->value);
		PrintInorder(root->right,fp);
	}
};

// 전위순회
void PrintPreorder(Node *root, FILE *fp){
	if (root != NULL){
		fprintf(fp,"%d ",root->value);
		PrintPreorder(root->left,fp);
		PrintPreorder(root->right,fp);
	}
};

// 후위순회
void PrintPostorder(Node *root, FILE *fp){
	if (root != NULL){
		PrintPostorder(root->left,fp);
		PrintPostorder(root->right,fp);
		fprintf(fp,"%d ",root->value);
		
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
	
	// fprintf(fp2,"%s\n",buffer);
	// fprintf(fp2,"filesize = %d\n",fileSize);
	
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
	
    char *order;
    char *valueStr;
    int value;
	
	Node *result = NULL; // 함수 실행 결과 리턴받은 노드를 저장해두는 포인터

	i=0; // index
	for(i=0; i<k ; i++){
		order = strtok(instructionSet[i]," ");
		valueStr = strtok(NULL, "\0");
		
		if (valueStr != NULL){
			value = atoi(valueStr);
			// printf("%d\n",value);
		}
	
		
		if (strcmp(order,"i") == 0){
			root = InsertNode(value,root,fp2);
		}
		else if (strcmp(order,"d") == 0){
			result = DeleteNode(value,root,fp2);
		}
		else if (strcmp(order,"f") == 0){
			result = FindNode(value,root);
			if (result == NULL){
				fprintf(fp2,"%d is not in the tree.\n",value);
			}
			else{
				fprintf(fp2,"%d is in the tree.\n",result->value);
			}
		}
		else if (strcmp(order,"pi") == 0){
			fprintf(fp2,"pi - ");
			PrintInorder(root, fp2);
			fprintf(fp2,"\n");
		}
		else if (strcmp(order,"pr") == 0){
			fprintf(fp2,"pr - ");
			PrintPreorder(root, fp2);
			fprintf(fp2,"\n");
		}
		else if (strcmp(order,"po") == 0){
			fprintf(fp2,"po - ");
			PrintPostorder(root, fp2);
			fprintf(fp2,"\n");
		}
		else{
			fprintf(fp2,"order: %s\n",order);
		}
		
		order[0] = '\0'; // order buffer 지우기
	}
	fclose(fp1);
	fclose(fp2);
}