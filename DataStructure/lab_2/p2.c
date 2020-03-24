#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* PtrToNode; // 학생구조체(data)와 다음노드의 주소(link)를 가지고있는 노드구조체
typedef PtrToNode List;
typedef PtrToNode Position;

typedef struct {
    char* studentID;
    char* studentName;
} StudentNode;

// 노드 형태 선언
struct Node {
    StudentNode st; // data part
    PtrToNode next; // link part
};

//리스트를 만드는 함수
List MakeList(){
    List L = malloc(sizeof(struct Node));
    L->next = NULL;
    return L;
};

void Insert(StudentNode X, List L, Position P);
void Delete(StudentNode X, List L);
Position Find(StudentNode X, List L);
void PrintList(List L);


void Insert(StudentNode X, List L, Position P){
    Position Tmp;
    Tmp = malloc(sizeof(struct Node));

    Tmp ->st = X;  // Tmp를 새로 넣을 Student로 설정
    Tmp ->next = P ->next; // 새로 들어온 node의 next를 기존 node의 next로 설정
    P ->next = Tmp; // 기존 node의 next가 Tmp를 바라보게 만듬
};

void Delete(StudentNode X, List L){

};

Position Find(StudentNode X, List L){
    return 0;
};

void PrintList(List L){

};

int main(){ 
    char buffer[100];
    
    /* 1.input 입력 부분 */
    FILE* fp;
    fp =fopen("insert.txt","r"); //초기에는 insert로 넣어놨다가 나머지 기능 구현후 input으로 바꾸자
    // fgets는 줄바꿈(\n)이 있을때까지만 읽는다
    // fgets(buffer, sizeof(buffer), fp);
    // fread는 줄바꿈이 있든 없든 정해진 크기만큼 읽는다(단, buffer를 {0,}으로 초기화해야한다)
    // fread(buffer, sizeof(buffer), 1, fp);

    List StudentList;
    
    
    while(!feof(fp)){   // feof는 파일 끝에 도달했을경우에만 0을 반환한다.
        fgets(buffer, sizeof(buffer), fp);

        char *sArr[4] = {NULL,}; // 자른 문자열의 포인터들을 저장해두는 배열
        int i = 0; // sArr용 인덱스
        char *nowStr = strtok(buffer, " "); // 공백 기준으로 첫번째 문자열을 자른다.
        
        // while문으로 line by line 문자열 분리하여 저장하기
        while (nowStr != NULL){
            sArr[i] = nowStr;
            i++;
            nowStr = strtok(NULL, " "); // nowStr을 다음 문자열(토큰)으로 재할당;
        }
        

        // switch(*nowStr){
        //     case 'i' :
                
        //         break;
        //     default :
        //         printf("다른문자입니다.\n");
        // }
    }
    fclose(fp);

    /* 2.insert 입력 부분 */
    return 0;
};