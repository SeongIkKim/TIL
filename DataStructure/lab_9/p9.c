#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define order 3

typedef struct Node *nodePointer;
typedef struct B_node{
	int n_keys; /* 키 갯수(최대 2개) */
	struct B_node *child[order]; /* 자식노드 포인터들의 배열 (최대 3개) */
	int key[order-1]; /* 해당 노드가 가지고 있는 key (최대 2개) */
}Node;

Node *root = NULL;

// Key 상황에 따른 ENUM 형 자료형 - Success는 키배열 공간이 남는 노드가 있어 집어넣었다, InsertIt은 node split 개념
enum KeyStatus { Success, InsertIt };

void insert(int key);
int searchPos(int key, int *key_arr, int n);
enum KeyStatus ins(Node *ptr, int key, int *upKey, Node **newnode);


// 삽입
void insert(int key){
	Node *newNode;
    int upKey;
    enum KeyStatus value;
 
	// value가 InsertIt이면 아래에서 처리 또는 ins에서 node Split, Success면 ins 호출시에 이미 처리되었다(남는 키 공간에 key 할당)
    value = ins(root, key, &upKey, &newNode);
 
    if (value == InsertIt){
        // 새노드 할당 후 값 넣기
        Node *uproot = root; // 기존의 root를 uproot에 옮겨놓는다
        root = calloc(1, sizeof(Node)); // 기존의 root 재할당
        root->n_keys = 1; // overflow가 일어나서 올라온 key이므로 새로 들어올 값은 1개
        root->key[0] = upKey; // ins에서 key로 초기화(insert함수에서 파라미터로 받은 key값)
        root->child[0] = uproot; // 기존의 root를 재할당한 새 root의 첫번째 자식노드로 받는다 
        root->child[1] = newNode; // ins에서 NULL로 초기화(새로 만들어진 노드는 key값이 하나밖에 없으므로)
    }
}

// 삽입 처리(상태 파악)
enum KeyStatus ins(Node *ptr, int key, int *upKey, Node **newnode){
    Node *newPtr;
	Node *lastPtr;
    int pos, i, n, splitPos;
    int newKey, lastKey;
    enum KeyStatus value;
    
    // root가 없을경우(트리가 비었을 경우) 최초의 root를 만들도록 새 노드만들기(InsertIt)
    if (ptr == NULL){
        *newnode = NULL;
        *upKey = key;
        return InsertIt;
    }
    // n = 해당 노드의 키 갯수
    n = ptr->n_keys;
 
    // 삽입하려는 키가 해당 노드의 키들 사이에서 어느 위치인지 찾기
    pos = searchPos(key, ptr->key, n);
 
    // 자식노드 재귀호출
    value = ins(ptr->child[pos], key, &newKey, &newPtr);
	
    // 삽입 아닐 경우 단순 반환(탈출용)
    if (value != InsertIt)
        return value; // 이때 value는 Success
		
	
    // 해당 node의 key가 order-1, 즉 최대 키 갯수보다 작을 경우
    if (n < order - 1){
        // 새 노드의 해당 위치를 가지고 온다
        pos = searchPos(newKey, ptr->key, n);
        
        // 삽입할 key값보다 더 큰 key값들을 한 칸씩 뒤로 민다. 동시에, child도 한칸씩 민다
        for (i = n; i>pos; i--){
            ptr->key[i] = ptr->key[i - 1];
            ptr->child[i + 1] = ptr->child[i];
        }
 
        // 해당 위치에 데이터 추가
        ptr->key[pos] = newKey;
        ptr->child[pos + 1] = newPtr;
        ++ptr->n_keys; // 개수 1개 증가
        return Success; // 성공 반환
    }
 
    // 들어갈 키가 해당 노드의 키들 중 가장 클 경우 그대로 뒷자리에 집어넣고, child도 연결시켜준다.
    if (pos == order-1){
        lastKey = newKey; 
        lastPtr = newPtr;
    }
 	
	// key가 다 찼고(2개) 새로 들어갈 키의 위치가 마지막이 아닌경우
    else {
        // 키가 들어가려면 마지막 키값(가장 큰 키값)을 밀어내야 하니까, 일단 따로 빼둔다
        lastKey = ptr->key[order - 2]; // 두 키 중 더 큰 키값
        lastPtr = ptr->child[order - 1]; // 자식 노드들 중 마지막 자식노드
 
        // 가운데 기준으로 한칸씩 밀어 가운데에 새 키를 위한 자리를 만들어준다
        for (i = order - 2; i > pos; i--)
        {
            ptr->key[i] = ptr->key[i - 1];
            ptr->child[i + 1] = ptr->child[i];
        }
        // 해당 위치(가운데)에 새로운 키 할당
        ptr->key[pos] = newKey;
        ptr->child[pos + 1] = newPtr;
    }
	
 	/* Node Split부분 (overflow 해결) */
	
    // split할 위치(즉, 중간 키의 index)
    splitPos = (order - 1) / 2; //
 
    // parent로 올려보낼 중간 키
    (*upKey) = ptr->key[splitPos];
 
    // 원래 노드를 반으로 갈라 오른쪽 sibling으로 사용할 노드를 할당해둔다
    (*newnode) = calloc(1,sizeof(Node));
 
    // 원래 있던 노드는 반이 잘렸으므로 key 개수가 반으로 줄었다(splitPos) - 왼쪽 sibling이 된다
    ptr->n_keys = splitPos; 
 
    // 오른쪽 sibling 노드의 키 갯수는 전체 키 갯수 - 왼쪽 sibling의 키 갯수
    (*newnode)->n_keys = (order-1)-(splitPos);
 
    // 반복문을 통해 자식 관계 처리 
    for (i = 0; i < (*newnode)->n_keys; i++)
    {
        // 새로 만들어질 오른쪽 sibling 노드의 자식노드들을 기존 ptr에서 가져와 할당
        (*newnode)->child[i] = ptr->child[i + splitPos + 1];
 
        // 키도 옮기기
        if (i < (*newnode)->n_keys - 1)
            (*newnode)->key[i] = ptr->key[i + splitPos + 1];
        
        // 따로 빼두었던 마지막 키 값 넣기
        else
            (*newnode)->key[i] = lastKey;
    }
 
    // 개수값 할당 및 상태값 반환(재귀적으로 계속 체크)
    (*newnode)->child[(*newnode)->n_keys] = lastPtr;
    return InsertIt;
}

// 해당 노드에서 찾는 값의 위치 찾기 
int searchPos(int key, int *key_arr, int n)
{
    int pos = 0;
    while (pos < n && key > key_arr[pos])
        pos++;
    return pos;
}

// 중위순회
void Inorder(Node *root, FILE *fp){
	if (root != NULL) {
		if (root->n_keys >= 1){
			// fprintf(fp,"키 1개짜리 노드 진입\n");
			Inorder(root->child[0],fp);
			fprintf(fp, "%d ", root->key[0]);
			Inorder(root->child[1],fp);
			if (root->n_keys == 2) {
				// fprintf(fp,"키 2개짜리 노드 진입\n");
				fprintf(fp,"%d ", root->key[1]);
				Inorder(root->child[2],fp);
			}
		}
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
			insert(value);
		}
		else if (strcmp(instruction,"p") == 0){
			Inorder(root,fp2);
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