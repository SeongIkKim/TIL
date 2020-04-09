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
	
	new_node->l_th = 0;
	new_node->r_th = 0;
	new_node->l_child = NULL;
	new_node->r_child = NULL;
	new_node->data = c;
	
	return new_node;
}

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

void tinorder(thr_ptr tree){
	thr_ptr temp = tree;
	for (;;){
		temp = insucc(temp);
		if (temp == tree){break;}
		printf("%c ",temp->data);
	}
};

int has_left_child(thr_ptr node){
	if (node->l_child){return 1;}
	else{return 0;}
}

int has_right_child(thr_ptr node){
	if (node->r_child){return 1;}
	else{return 0;}
}

void InsertNode(thr_ptr node, thr_ptr tree, thr_ptr *queue, int front, int rear){
	queue[++rear] = node;
	
	// thr_ptr temp = tree; 굳이 tree필요없을듯
	
	if (queue[front]->l_child == NULL){
		// 왼쪽 자손이 없을때(즉, 두 자손이 모두 없을때)
		queue[front]->l_child = node;
		printf("%c의 왼쪽자손 : %c\n",queue[front]->data,queue[front]->l_child->data);
	}
	else if (queue[front]->r_child == NULL){
		// 오른쪽 자손이 없을때(즉, 왼쪽 자손만 있을때)
		// 이진트리의 left child와 right child가 채워졌으므로 queue에서 해당노드를 삭제한다.
		queue[front]->r_child = node;
		printf("%c의 오른쪽자손 : %c  ",queue[front]->data,queue[front]->r_child->data);
		front++;
		printf("now front = %d\n",front);
	}
	else{
		
	};
	
}

int main(){
	char buffer[200];
	
	FILE *fp;
	fp= fopen("input.txt","r");
	
	int node_num;
	
	// 라인 체크용 인덱스
	int line=0;
	
	// line 2의 node char들을 저장할 queue
	char node_data[100] = {0,};
	
	while(1){
		// I/O부
		line++;
		fgets(buffer, sizeof(buffer), fp);
		
		if(feof(fp) & line>2){
			break;
		}
		
		if(*(buffer+(strlen(buffer)-1)) == '\n'){
			*(buffer+(strlen(buffer)-1)) = '\0';
		}
		
		if(line==1){
			node_num = atoi(buffer);
			printf("line 1 처리완료\n");
		} 
		else if(line==2){
			
			int i=0;
			char *now_data = strtok(buffer, " ");
			
			while (now_data){
				node_data[i] = *now_data;
				i++;
				now_data = strtok(NULL, " ");
			}
			printf("line 2 처리완료\n");
			free(now_data);
		}
		
	}	
	
	printf("11");
	
	// Insert할 노드들을 담아둘 큐 구현
	thr_ptr queue[MAX_SIZE] = {NULL,};
	int rear = -1;
	int front = 0;
		
	// 이제부터 Threaded tree 구성 시작
	
	// 헤더 노드 구현
	thr_ptr header = create_node(0);
	header->r_child = header;
	
	printf("22\n");
	
	for(int i=0; i<node_num; i++){
		printf("i=%d\n",i);
		if(i != 0){
			// 두번째 노드부터는 queue의 front를 검사하여 넣을 위치를 선정한다.
			thr_ptr node = create_node(node_data[i]);
			InsertNode(node,header,queue,front,rear);
		}
		else{
			// i==0
			// 첫번째 노드는 header와 연결시켜준다.
			thr_ptr first_node = create_node(node_data[i]);
			queue[++rear] = first_node;
			header->l_child = first_node;
			printf("inserted : %c\n",first_node->data);
		}
	}
	
	
	
	
		
		
		
}