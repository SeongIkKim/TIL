#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EmptyTOS -1
#define MAX_ELEMENTS 100

typedef struct StackRecord *Stack;

struct StackRecord {
	int Capacity;
	int TopOfStack;
	char *Array;
	int ExistLP;
};


Stack CreateStack(){
	Stack S;
	
	S = malloc(sizeof(struct StackRecord));
	if(S == NULL){
		printf("Stack - out of space.\n");
	}
	
	S->Array = malloc(sizeof(char)*MAX_ELEMENTS);
	if(S->Array == NULL){
		printf("Stack Array - out of space.\n");
	}
	
	S->Capacity = MAX_ELEMENTS;
	S->TopOfStack = EmptyTOS;
	
	return S;
}

int IsFull(Stack S){
	if (S->TopOfStack == S->Capacity-1){
		return 1;
	}
	else {
		return 0;
	}
}

int IsEmpty(Stack S){
	if (S->TopOfStack == -1){
		return 1;
	}
	else {
		return 0;
	}
}


void Push(char X, Stack S){
	if(IsFull(S)){
		printf("Full\n");
	}
	else{
		S->Array[++S->TopOfStack] = X;
		// printf("pushed %d\n",S->Array[S->TopOfStack]);
	}
}

char Pop(Stack S){
	if(IsEmpty(S)){
		printf("Empty\n");
	}
	else{
		char token = S->Array[S->TopOfStack];
		S->TopOfStack--;
		return token;
	}
}


int isDigit(char c){
	if (49<=c && c<=57){
		return 1;
	}
	else{
		return 0;
	}
}

// operator가 +나 -인지 체크하여 반환
int isP1(char c){
	if (c == 43 || c == 45){
		return 1;
	}
	else{
		return 0;
	}
}

// operator가 %나 *나 /인지 확인
int isP2(char c){
	if (c == 37 || c == 42 || c == 47){
		return 1;
	}
	else{
		return 0;
	}
}

// operator가 (,)인지 확인
int isP(char c){
	if (c == 40 || c == 41){
		return 1;
	}
	else{
		return 0;
	}
}

// operator가 (인지 확인
int isLP(char c){
	if (c == 40){
		return 1;
	}
	else {
		return 0;
	}
}

// operator가 )인지 확인
int isRP(char c){
	if (c == 41){
		return 1;
	}
	else {
		return 0;
	}
}

int checkOperator(char c){
	switch(c){
		case 43:
			return 1;
			break;
		case 45:
			return 2;
			break;
		case 37:
			return 3;
			break;
		case 42:
			return 4;
			break;
		case 47:
			return 5;
			break;
		default:
			return -1;
			break;
	}
}

int main(){
	char buffer[100];
	
	FILE* fp;
	fp = fopen("input3-3.txt","r");
	
	fread(&buffer, sizeof(buffer), 1, fp);
	
	// expression이 끝났는지 check용 index
	int i=0;
	
	while(buffer[i] != '#'){
		i++;
	}
	buffer[i] = '\0';
	
	// Evaluation용 Stack;
	Stack E = CreateStack();
	
	// 1.infix form 출력
	printf("Infix Form : %s\n",buffer);
	
	// 2.postfix form 출력
	Stack S = CreateStack();
	S->ExistLP = 0;
	i = 0;
	printf("Postfix Form : ");
	while (buffer[i] != '\0'){
		// printf("\n");
		// printf("%c",buffer[i]);
		int X = buffer[i];
		if (isDigit(X)){
			// printf("숫자입니다\n");
			printf("%c",X);
			Push(X,E);
		}
		else{
			// 괄호인지 확인
			if (isP(X)){
				// 왼쪽 괄호일때
				if (isLP(X)){
					// printf("왼쪽 괄호입니다\n");
					Push(X,S);
					S->ExistLP = 1;
				}
				else{
					// 오른쪽 괄호일때
					// printf("오른쪽 괄호입니다\n");
					while(1){
						char token = Pop(S);
						// 왼쪽 괄호를 만나야만 빠져나온다
						if (isLP(token)){
							// printf("왼쪽 괄호를 만났습니다.\n");
							S->ExistLP = 0;
							break;
						}
						else{
							printf("%c",token);
							Push(token,E);
						}
					}
				}
				
			}
			// %,*,/인지 확인
			else if (isP2(X)){
				// printf("모듈로*/입니다\n");
				if (isP1(S->Array[S->TopOfStack]) || S->TopOfStack == -1){
					// stack의 top이 우선순위가 더 낮을 때
					Push(X,S);
				}
				else{
					// 왼쪽 괄호가 존재할때(계속 넣는다)
					if(S->ExistLP){
						Push(X,S);
					}
					else{
						// stack의 top과 우선순위가 같거나 top이 더 높을 때
						char token = Pop(S); 
						printf("%c",token);	
						Push(token,E);
					}
				}
			}
			else if (isP1(X)){
				// printf("+-입니다\n");
				if (S->ExistLP){
					// 괄호안에서 +나 -를 만났을 때(계속 넣는다)
					Push(X,S);
				}
				else{
					// 괄호 밖에서 +나 -를 만났을 때
					if(isP1(S->Array[S->TopOfStack]) || isP2(S->Array[S->TopOfStack])){
						char token = Pop(S);
						printf("%c",token); 
						Push(X,S);
						Push(token,E);
					}
				}
				
			}
			else {
				printf("Wrong Order\n");
			}
		}
	i++;
	}
	if (S->TopOfStack != -1){
		char token = Pop(S);
		printf("%c",token);
		Push(token,E);
	}
	printf("\n");
	free(S);
	
	// 3. evaluation 출력
	int j =0;
	int value = 0;
	
	Stack Calc = CreateStack();
	
	while (E->Array[j] != '\0'){
		char c = E->Array[j];
		if (isDigit(c)){
			// 숫자일때
			Push(atoi(&c),Calc);
		}
		else{
			// 연산자일때
			int op2 = Pop(Calc);
			int op1 = Pop(Calc);
			
			switch(checkOperator(c)){
				case 1:
					// plus
					value = op1+op2;
					Push(value,Calc);
					break;
				case 2:
					// minus
					value = op1-op2;
					Push(value,Calc);
					break;
				case 3:
					// modulo
					value = op1%op2;
					Push(value,Calc);
					break;
				case 4:
					// multiply
					value = op1*op2;
					Push(value,Calc);
					break;
				case 5:
					// divide
					value = op1/op2;
					Push(value,Calc);
					break;
				case -1:
					printf("error\n");
			}
			
		}
		j++;
	}
	
	printf("Evaluation : %d\n",value);
	
	free(E);
	free(Calc);
	
	fclose(fp);
}