#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct HashTbl *HashTable;

struct HashTbl{
	int TableSize;
	int* table;
};

// 해시 함수
int Hash(int value, int Size, int i, int solution){
	int hValue = value;
	
	switch(solution){
		case 1: // Linear
			hValue = (hValue + i) % Size ;
			break;
		case 2: // Quadratic
			hValue = (hValue + i*i) % Size;
			break;
		case 3: // Double
			hValue = (hValue + i*(7-(value % 7))) % Size;
			break;
		default:
			printf("solution number error : %d\n",solution);
	}
	return hValue;
};

// 해시 테이블에서 value 검색
int Find(HashTable H, int value, int solution){
	int hValue = Hash(value, H->TableSize, 0, solution); // 해시값
		
	if (H->table[hValue] == value) {
		// 1. Find 성공 시
		return hValue;
	}
	else if (H->table[hValue] == 0){
		// 2. Find 실패 - 해당 값이 애초에 존재하지 않음
		return -1;
	}
	else if (H->table[hValue] != 0) {
		// 3. Find 실패 - 그러나 다른 곳에 저장되었을지 모르므로 probing해서 찾아보기
		int i=0;
		while(i < H->TableSize){ // 최대 probing 횟수는 테이블 크기만큼
			hValue = Hash(value, H->TableSize, ++i, solution);
			if (H->table[hValue] == value){
				// 3-1. probing 했는데 해당 값이 존재할 때
				return hValue;
			}
			else if (H->table[hValue] == 0){
				// 3-2. probing이 끝났는데도 값을 못 찾았을 경우 해당 값은 존재 X
				return -1;
			}
		}	
	}
	
	// 3-3. 테이블 전체를 돌아도 못찾았을 경우 해당 값은 존재 X
	return -1;
};

// 해시 테이블에 value 삽입
void Insert(HashTable H, int value, int solution, FILE *output){
	int hValue = Hash(value, H->TableSize, 0, solution); // 해시값
		
	if (H->table[hValue] == value) {
		// 1. 해당 값이 이미 존재할 때
		fprintf(output,"Already exists");
		return;
	}
	else if (H->table[hValue] != 0) {
		// 2. 해당 값은 존재하지 않지만 다른 값이 있어 collision 발생 시
		int i=0;
		while(1){
			hValue = Hash(value, H->TableSize, ++i, solution);
			if (H->table[hValue] == value){
				// 2-1. probing 했는데 해당 값이 이미 존재할 때
				fprintf(output,"Already exists\n");
				return;
			}
			else if (i == H->TableSize){
				// 2-2. probing해봤는데 테이블이 꽉 차서 빈 공간이 없음
				fprintf(output,"HashTable is full\n");
				return;
			}
			else if (H->table[hValue] == 0){
				// 2-3. probing해보니 해당 값이 없고, 빈 공간을 찾음
				break;
			}
		}	
	}
	H->table[hValue] = value;
	fprintf(output,"Inserted %d\n",H->table[hValue]);
};

// 해시 테이블에서 value 삭제
void Delete(HashTable H, int value, int solution, FILE *output){
	int findResult = Find(H, value, solution);
	
	if (findResult == -1){
		fprintf(output,"%d not exists\n",value);
	}
	else{
		H->table[findResult] = 0;
		fprintf(output,"Deleted %d\n",value);
	}
};


// 해시 테이블 내의 값 프린트
void Print(HashTable H,FILE *output){
	int i;
	for (i=0; i<H->TableSize; i++){
		fprintf(output,"%d ",H->table[i]);
	}
	fprintf(output,"\n\n");
};




int main(){
	char *buffer;
	int fileSize;
	
	FILE *input; // input.txt
	FILE *output; // output.txx
	
	input = fopen("input.txt","r");
	if (input == NULL){
		fputs("FILE ERROR",stderr);
		exit(1);
	}
	output = fopen("output.txt","w");
	
	// 파일의 크기를 fileSize 에 저장한다.
	fseek(input, 0, SEEK_END); // fp1을 열어 스트림의 위치지정자를 0부터 파일끝까지 이동시킨다
	fileSize = ftell(input); // 파일끝의 스트림(즉, 파일의 문자열 크기)을 fileSize에 할당시킨다.
	rewind(input); // 다시 파일의 스트림의 위치지정자를 원래대로 돌려놓는다

	// 전체 파일의 내용을 받을 수 있을 정도의 크기로 메모리를 할당한다.
	buffer = (char*)malloc(sizeof(char) * fileSize);
	if (buffer == NULL) {
		fputs("Memory error", stderr);
		exit(2);
	}
	
	// 그 파일의 내용을 버퍼에 저장한다.
  	fread(buffer, 1, fileSize, input);
	
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
	
	HashTable H = (HashTable)malloc(sizeof(struct HashTbl));
	
	i=1; // caseNum 할당을 제외한 instruction index
	for(caseNum = atoi(instructionSet[0]); caseNum >0; caseNum--){
		
		// solution set
		fprintf(output,"%s\n",instructionSet[i]);
		if (strcmp(instructionSet[i],"Linear") == 0){solution=1;}
		else if (strcmp(instructionSet[i],"Quadratic") == 0){solution=2;}
		else if (strcmp(instructionSet[i],"Double") == 0){solution=3;}
		i++;
		
		// HashTable set
		H->TableSize = atoi(instructionSet[i++]);
		H->table = (int*)malloc(sizeof(int)*H->TableSize);
		for(j=0; j<H->TableSize; j++){
			H->table[j] = 0;
		}
		
		
		while(1){
			order = strtok(instructionSet[i]," ");
			valueStr = strtok(NULL, "\0");

			if (valueStr != NULL){
				value = atoi(valueStr);
			}

			if (strcmp(order,"i") == 0){
				Insert(H, value, solution,output);
			}
			else if (strcmp(order,"d") == 0){
				Delete(H, value, solution,output);
			}
			else if (strcmp(order,"f") == 0){
				int findResult = Find(H, value, solution);
				if (findResult == -1){fprintf(output,"Not found\n");}
				else {fprintf(output,"Find %d : index is %d\n",value, findResult);}
			}
			else if (strcmp(order,"p") == 0){
				Print(H,output);
			}
			else if (strcmp(order,"q") == 0){
				i++;
				free(H->table);
				break;
			}
			else{
				fprintf(output,"order: %s\n",order);
			}

			order[0] = '\0'; // order buffer 지우기
			i++;
		}
	}
	free(buffer);
	free(H);
	fclose(input);
	fclose(output);
}