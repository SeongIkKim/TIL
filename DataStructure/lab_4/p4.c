#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct thr_tree *thr_ptr;

struct thr_tree {
	short int l_th;
	thr_ptr l_child;
	char data;
	thr_ptr r_child;
	short int r_th;
};

thr_ptr create_node(char c){
	thr_ptr new_node = malloc(sizeof(struct thr_tree));
	
	new_node->l_th = 1;
	new_node->r_th = 1;
	new_node->l_child = NULL;
	new_node->r_child = NULL;
	new_node->data = c;
	
	return new_node;
}

// 중위후속자를 찾아주는 함수
thr_ptr insucc(thr_ptr tree){
	thr_ptr temp;
	temp = tree->r_child;
	if(!tree->r_th){
		while(!temp->l_th){
			temp=temp->l_child;
		}
	}
	return temp;
};

// 순회하며 노드 내의 데이터를 출력하는 함수
void tinorder(thr_ptr tree, FILE *fp){
	thr_ptr temp = tree;
	for (int i=0;;i++){
		temp = insucc(temp);
		if (temp == tree){break;}
		printf("%c ",temp->data);
		
		// 파일 입출력
		fprintf(fp,"%c ",temp->data);
	}
};

int has_left_child(thr_ptr node){
	if (node->l_child != NULL){return 1;}
	else{return 0;}
}

int has_right_child(thr_ptr node){
	if (node->r_child != NULL){return 1;}
	else{return 0;}
}

void InsertNode(thr_ptr node, thr_ptr tree, thr_ptr *queue, int *q_info){
	//q_info[0] = rear, q_info[1] == front;
	int rear = q_info[0];
	int front = q_info[1];
		
	queue[++rear] = node;
	
	// if 조건문의 th==1 검사는 queue[front]가 첫번째 노드일 경우만 예외적으로 조건문을 만족시키게 해준다.
	if (!has_left_child(queue[front]) || queue[front]->l_th == 1){
		// 왼쪽 자손이 없을때(즉, 두 자손이 모두 없을때)
		node->l_child = queue[front]->l_child; // 새로 삽입될 노드의 왼쪽 스레드는 부모 노드의 왼쪽 스레드포인터에 담겨있던 곳과 같다
		node->r_child = queue[front]; // 새로 삽입될 노드의 오른쪽 스레드는 부모노드와 같다.
		
		queue[front]->l_child = node;
		queue[front]->l_th = 0;
		
		// printf("%c의 왼쪽자손 : %c\n",queue[front]->data,queue[front]->l_child->data);
	}
	else if (!has_right_child(queue[front]) || queue[front]->r_th == 1){
		// 오른쪽 자손이 없을때(즉, 왼쪽 자손만 있을때)
		node->l_child = queue[front]; // 새로 삽입될 노드의 왼쪽 스레드는 부모노드와 같다.
		node->r_child = queue[front]->r_child; // 새로 삽입될 노드의 오른쪽 스레드는 부모노드의 오른쪽 스레드포인터에 담겨있던 곳과 같다.
		
		// 이진트리의 left child와 right child가 채워졌으므로 queue에서 해당노드를 삭제한다.
		queue[front]->r_child = node;
		queue[front]->r_th = 0;
		// printf("%c의 오른쪽자손 : %c \n",queue[front]->data,queue[front]->r_child->data);
		front++;
	}
	else{printf("error");};
	
	q_info[0] = rear;
	q_info[1] = front;
}

int main(){
	char buffer[200];
	
	FILE *fp1; // input.txt 파일 포인터
	FILE *fp2; // ouput.txt 파일 포인터
	
	fp1= fopen("input.txt","r");
	fp2 = fopen("output.txt","a+");
	
	int node_num;
	
	// 라인 체크용 인덱스
	int line=0;
	
	// line 2의 node char들을 저장할 queue
	char node_data[100] = {0,};
	
	while(1){
		// I/O부
		line++;
		fgets(buffer, sizeof(buffer), fp1);
		
		if(feof(fp1) && line>2){
			break;
		}
		
		if(*(buffer+(strlen(buffer)-1)) == '\n'){
			*(buffer+(strlen(buffer)-1)) = '\0';
		}
		
		if(line==1){
			node_num = atoi(buffer);
		} 
		else if(line==2){
			
			int i=0;
			char *now_data = strtok(buffer, " ");
			
			while (now_data){
				node_data[i] = *now_data;
				i++;
				now_data = strtok(NULL, " ");
			}
			free(now_data);
		}
		
	}	
	
	
	// Insert할 노드들을 담아둘 큐 구현
	thr_ptr queue[MAX_SIZE] = {NULL,};
	
	int rear = -1;
	int front = 0;
	// rear,front를 담아두는 포인터 array
	int *q_info[2];
	q_info[0] = &rear;
	q_info[1] = &front;
	
	// 이제부터 Threaded tree 구성 시작
	
	// 헤더 노드 구현
	thr_ptr header = create_node(0);
	header->r_child = header;
	header->l_th = 0;  
	header->r_th = 0;
	
	
	for(int i=0; i<node_num; i++){
		// printf("\ni=%d\n",i);
		
		if(i != 0){
			// 두번째 노드부터는 queue의 front를 검사하여 넣을 위치를 선정한다.
			thr_ptr node = create_node(node_data[i]);
			InsertNode(node,header,queue,*q_info);
		}
		else{
			// i==0
			// 첫번째 노드는 header와 연결시켜준다.
			thr_ptr first_node = create_node(node_data[i]);
			queue[++rear] = first_node;
			first_node->l_child = header; // 트리의 좌하단 노드이므로 스레드로 header를 가리킨다.
			first_node->r_child = header; // 트리의 우하단 노드이므로 스레드로 header를 가리킨다.
			header->l_child = first_node;
		}
		
		//큐 내역을 보여준다//
		// printf("queue : ");
		// for(int j=front; queue[j]!=NULL;j++){
		// 	printf("%c ",queue[j]->data);
		// }
		// printf("\n");
	}
	fclose(fp1);
	
	tinorder(header,fp2);
	
	fclose(fp2);	
}