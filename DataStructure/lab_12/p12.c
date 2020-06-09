#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListNode *Position;
typedef Position List;
typedef struct HashTbl *HashTable;

struct ListNode{
	int Element;
};

struct HashTbl{
	int TableSize;
	List* TheLists;
};

// 해시 테이블에 value 삽입
void Insert(HashTable H, int value, int solution){
	
};

// 해시 테이블에서 value 삭제
void Delete(HashTable H, int value, int solution){
	
};

// 해시 테이블에서 value 검색
int Find(HashTable H, int value, int solution){
	
};

// 해시 테이블 내의 값 프린트
void Print(HashTable H){
	
};

// 해시 함수
int Hash(int value, int Size, int i, int solution){
	
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
	
	char *instructionSet[100];
	
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
	
	int caseNum;
	int solution;
	int tableSize;
	
	i=1; // caseNum 할당을 제외한 instruction index
	for(caseNum = atoi(instructionSet[0]); caseNum >0; caseNum--){
		
		// solution set
		if (strcmp(instructionSet[i],"Linear") == 0){solution=1;}
		else if (strcmp(instructionSet[i],"Quadratic") == 0){solution=2;}
		else if (strcmp(instructionSet[i],"Double") == 0){solution=3;}
		i++;
		
		// tableSize set
		tableSize = atoi(instructionSet[i++]);
		
		printf("CaseNum : %d, solution: %d, tableSize: %d\n",caseNum,solution,tableSize);
		
		while(1){
			order = strtok(instructionSet[i]," ");
			valueStr = strtok(NULL, "\0");

			if (valueStr != NULL){
				value = atoi(valueStr);
				// printf("%d\n",value);
			}

			if (strcmp(order,"i") == 0){
				printf("insert %d\n",value);
				// Insert();
			}
			else if (strcmp(order,"d") == 0){
				printf("delete %d\n", value);
				// Delete();
			}
			else if (strcmp(order,"f") == 0){
				printf("find %d\n", value);
				// Find();
			}
			else if (strcmp(order,"p") == 0){
				printf("print Hash table\n");
				// Print();
			}
			else if (strcmp(order,"q") == 0){
				printf("finish test case\n");
				i++;
				break;
			}
			else{
				fprintf(fp2,"order: %s\n",order);
			}

			order[0] = '\0'; // order buffer 지우기
			i++;
		}
	}
	fclose(fp1);
	fclose(fp2);
}