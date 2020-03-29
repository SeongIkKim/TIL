#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *PtrToNode; // 학생구조체(data)와 다음노드(link)를 가지고있는 노드구조체
typedef PtrToNode List;
typedef PtrToNode Position;

// 학번과 이름을 저장하는 구조체
typedef struct {
    int studentID;
    char* studentName;
} StudentData;

// 노드 형태 선언
struct Node {
    StudentData st; // data part
    PtrToNode next; // link part
};

// 최초의 리스트(노드 1개)를 만드는 함수
List MakeList(){
    List L = malloc(sizeof(struct Node));
    L->next = NULL;
    return L;
};

void Insert(StudentData X, List L, Position P);
void Delete(StudentData X, List L);
void Find(StudentData X, List L);
void PrintList(List L);
void CurrentList(List L);

int isLast(Position P){
	
	if (P->next == NULL){
		return 1;
	}
	else {
		return 0;
	}
}

void Insert(StudentData X, List L, Position P){
    Position tmp;
    tmp = malloc(sizeof(struct Node));

    tmp ->st = X;  // tmp의 data파트를 새로 넣을 StudentData X로 설정
    tmp ->next = P ->next; // 새로 들어온 node의 next를 기존 node의 next로 설정
    P ->next = tmp; // 기존 node의 next가 tmp를 바라보게 만듬
	
	
	// printf("%s", tmp->st.studentID);
	
	// printf("Insertion Success : %s\n",);
	// CurrentList(L);
};

void Delete(StudentData X, List L){
	Position target,tmp;
	
	tmp = L;
	
	
	while(1){
		if(!isLast(tmp)){
			// 다음 노드가 있을 때
			if(tmp->next->st.studentID == X.studentID){
				// tmp 다음 노드가 찾고있던 노드일때
				target = tmp->next;
				tmp->next = target->next;
				free(target);
				printf("Deletion Success : %d\n",X.studentID);
				CurrentList(L);
				break;
			}
			else{
				tmp = tmp->next;
			}
		}
		else {
			// 다음 노드가 없을 때 (마지막 노드일때) --> 즉, 찾는 노드가 없을 때
			printf("Deletion Failed : student ID %d is not in the list.\n",X.studentID);
			break;
		}
	}
	
	
};

void Find(StudentData X, List L){
    Position target = L;
	
	while(1){
		if(!isLast(target)){
			// 다음 노드가 있을 때
			if(target->next->st.studentID == X.studentID){
				// tmp 다음 노드가 찾고있던 노드일때
				printf("Find Success : %d %s\n",target->next->st.studentID,target->next->st.studentName);
				return;
			}
			else{
				target = target->next;
			}
		}
		else {
			// 다음 노드가 없을 때 (마지막 노드일때) --> 즉, 찾는 노드가 없을 때
			printf("Find %d Failed. There is no student ID\n",X.studentID);
			return;
		}
	}
	
};

void PrintList(List L){
	PtrToNode tmp = L->next;
	printf("-----LIST-----\n");
	while (1){
		if (tmp->next != NULL){
			printf("%d %s\n",tmp->st.studentID, tmp->st.studentName);	
			tmp = tmp->next;
		}
		else {
			printf("%d %s\n",tmp->st.studentID, tmp->st.studentName);	
			break;
		}
	}
	printf("--------------\n");
};

void CurrentList(List L){
	Position tmp = L->next;
	
	printf("Current List > ");
	while(1){
		if(!isLast(tmp)){
			printf("%d %s-",tmp->st.studentID, tmp->st.studentName);
			tmp = tmp->next;
		}
		else{
			printf("%d %s\n",tmp->st.studentID, tmp->st.studentName);
			break;
		}
	}
	
}

int main(){ 
    char buffer[100];
    /* input 입력 부분 */
    FILE* fp;
    fp =fopen("input.txt","r"); //초기에는 insert로 넣어놨다가 나머지 기능 구현후 input으로 바꾸자
    // fgets는 줄바꿈(\n)이 있을때까지만 읽는다
    // fgets(buffer, sizeof(buffer), fp);
    // fread는 줄바꿈이 있든 없든 정해진 크기만큼 읽는다(단, buffer를 {0,}으로 초기화해야한다)
    // fread(buffer, sizeof(buffer), 1, fp);

    List L = MakeList();
    // L은 next = NULL인 노드 하나만 있는 상태
    
    while(!feof(fp)){   // feof는 파일 끝에 도달했을경우에만 0을 반환한다. 단, 마지막 줄을 중복출력하므로 fgets 이후에 한번 더 검사해준다
		
        fgets(buffer, sizeof(buffer), fp);
		
		if (feof(fp)){	// 파일이 끝났는지 중복검사
			break;
		}
		
		// fgets의 개행문자 제거
		if(*(buffer+(strlen(buffer)-1)) == '\n'){
			*(buffer+(strlen(buffer)-1))= 0;	
		}

        char *sArr[4]; // 자른 문자열의 포인터들을 저장해두는 배열
        int i = 0; // sArr용 인덱스
        char *nowStr = strtok(buffer, " "); // 공백 기준으로 첫번째 문자열을 자른다.
        
        // while문으로 한 라인(buffer)에서 문자열 분리하여 저장하기
        while (nowStr != NULL){
            sArr[i] = nowStr;
            i++;
            nowStr = strtok(NULL, " "); // nowStr을 다음 문자열(토큰)으로 재할당;
        }
		
		free(nowStr);

        char operation = *sArr[0]; // sArr[0]은 포인터형이고, *sArr[0]은 char형이다
		
	
		// StudentData X 생성(Id만 입력, name은 insertion에서 입력)
		int IdToInt = atoi(sArr[1]);
		StudentData X = {IdToInt,NULL};
        
		// operation에 따라 연산처리
		
		if(operation == 'i'){
			// input으로 StudentData X의 name 채워넣기
				
			char* fullName = malloc(sizeof(char) * 65);
			char* firstName = sArr[2];
			char* lastName = sArr[3];
			strcat(fullName, firstName);
			strcat(fullName, " ");
			strcat(fullName, lastName);
			
			X.studentName = fullName;
			// StudentData X 생성 끝
			

			// 현재노드를 가리키는 포인터
			PtrToNode crnt = malloc(sizeof(struct Node));
			crnt = L;

			while (crnt->next != NULL){
			crnt = crnt->next;
			}
			// while문이 끝나고 나면 crnt는 List의 tail를 가리킨다.
			if (crnt==L){
				// Head만 있는 리스트에 최초의 노드를 삽입할 때;
				PtrToNode N = malloc(sizeof(struct Node));
				N->st = X;
				N->next = NULL;
				L->next = N;

				printf("Insertion Success : %d\n",X.studentID);
			}
			else{
				crnt = L;
				while (crnt->next != NULL){
					if (X.studentID > crnt->next->st.studentID){
						// 노드가 들어갈 위치 탐색중
						crnt = crnt->next;	
					}
					else if(X.studentID == crnt->next->st.studentID){
						// 같은 학번의 노드가 존재할 때
						printf("Insertion Failed. ID %d already exists.\n",X.studentID);
						break;
					}
					else {
						// 리스트의 중간에 노드를 삽입할 때
						Insert(X, L, crnt);
						printf("Insertion Success : %d\n",X.studentID);
						break;
					}
				}
				if (crnt->next == NULL & X.studentID > crnt->st.studentID){
					// 리스트의 tail부분에 노드를 삽입할 때
					PtrToNode N = malloc(sizeof(struct Node));
					N->st = X;
					N->next = NULL;
					crnt->next = N;
					printf("Insertion Success : %d\n",X.studentID);
				}
				
			}
			CurrentList(L);
		}
		else if(operation == 'd'){
			Delete(X,L);
		}
		else if(operation == 'f'){
			Find(X,L);
		}
		else if(operation == 'p'){
			PrintList(L);
		}
		else {
			("There is no such order.\n", &operation);
		}
		
    }
	
    fclose(fp);
	
    return 0;
};