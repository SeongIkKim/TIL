//structure

#include <stdio.h>
#include <string.h>

typedef struct student{
    char name[20];
    int studentID;
    char major[20];
}STUDENT;
// typedef를 이용하면 struct에 별명을 붙여(STUDENT) 사용할 수 있다.

int main(){
    struct student s1;
    strcpy(s1.name, "seongik");
    s1.studentID=8886;
    strcpy(s1.major, "Information System");

    printf("name: %s\n", s1.name);
    printf("studentID: %d\n", s1.studentID);
    printf("major: %s\n", s1.major);

    return 0;
}

//추가과제 파일입출력으로 만들기
