// selection_sort
#include <stdio.h>

int main(){
    int array[10] = {10,4,7,8,6,9,5,2,1,3};
    int i,j,min,minIndex,temp;

    for (i=0;i<10;i++){
        min = 99999;
        for(j=i;j<10;j++){
            if(min > array[j]){
                min = array[j];
                minIndex = j;
            }
        }
        temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }

    for(i=0;i<10;i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

//추가과제 파일입출력으로 만들기