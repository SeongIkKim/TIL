#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(){
	FILE *input; 
	FILE *output;
	char buffer[100];
	int i,j;
	
	input = fopen("input.txt", "r");
	if (input == NULL){
		printf("error");
		return -1;
	}
	
	output = fopen("output.txt", "wt");
	
	fgets(buffer, sizeof(buffer), input);
	
	int vertices[15] = {0,};
	char *vertex = strtok(buffer, " ");
	
	for(i=0; vertex != NULL; i++){
		vertices[i] = atoi(vertex);
		vertex = strtok(NULL, " ");
	}
	vertices[i] = '\0';
	
	
}