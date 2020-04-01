#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100


int queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = 0;

void Enqueue(int item, int *queue){
	if(rear==MAX_QUEUE_SIZE -1){
		printf("Full\n");
	}
	else{
		queue[++rear]=item;
	}
}

int Dequeue(int *queue){
	if(front > rear){
		printf("Empty\n");
		return -1;
	}
	else{
		return queue[front++];
	}
}

int main(){
	char buffer[30];
	
	FILE* fp;
	fp = fopen("input3-2.txt","r");
	
	// 파일 라인 체크용 인덱스
	int line= 0;
	
	int Q[MAX_QUEUE_SIZE]={'\n',};
	int rear = -1;
	int front = 0;
	
	int NumOfInst;
	
	while(1){
		line++;
		fgets(buffer, sizeof(buffer), fp);
		
		
	
		if(feof(fp) & line>NumOfInst+1){
			break;
		}
		
		if(*(buffer+(strlen(buffer)-1)) == '\n'){
			*(buffer+(strlen(buffer)-1)) = '\0';
		}
		
		
		
		if(line==1){
			// 몇 번의 enQ와 deQ가 수행될 건지
			NumOfInst = atoi(buffer);
		}
		
		else{
			// enqueue or dequeue용 명령 처리
			char *sArr[2];
			int i = 0;
			char *nowStr = strtok(buffer, " ");
			
			while(nowStr != NULL){
				sArr[i] = nowStr;
				i++;
				nowStr = strtok(NULL, " ");
			}
			
			

			if(!strcmp(sArr[0],"enQ")){
				int X = atoi(sArr[1]);
				Enqueue(X,Q);
			}
			else if(!strcmp(sArr[0],"deQ")){
				int deQ = Dequeue(Q);
				if (deQ != -1){
					printf("%d\n",deQ);	
				}
			}
			else{
				printf("Wrong Order.\n");
			}
		}
	}
	
	fclose(fp);
	
	return 0;
}