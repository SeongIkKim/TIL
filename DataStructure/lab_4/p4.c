#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct thr_tree *thr_ptr;

struct thr_tree {
	short int l_th;
	thr_ptr l_child;
	char data;
	thr_ptr r_child;
	short int r_th;
};

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

int main(){
	char buffer[100];
	
	FILE *fp;
	fp= fopen("input.txt","r");
	
	int node_num;
	
	// 라인 체크용 인덱스
	int line=0;
	
	while(1){
		line++;
		fgets(buffer, sizeof(buffer), fp);
		
		if(line==1){
			node_num = atoi(buffer);
		}
		
		if(feof(fp) & line>2){
			break;
		}
		
		if(*(buffer+(strlen(buffer)-1)) == '\n'){
			*(buffer+(strlen(buffer)-1)) = '\0';
		}
		
		printf("line %d : %s\n",line,buffer);
	}
}