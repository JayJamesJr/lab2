#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"extract_tokens.h"
void parse_tokens(char cmd[], char *par[]){

	char input_line[1024];
	for(int i = 0; i < 1024; i++){
		input_line[i] = 0;
	}

	
	int count = 0;
	char *array[256], *pch;
	int i = 0;


	fgets(input_line,1024,stdin);
	pch = strtok(input_line, " ");
	while ( pch != NULL){
		array[i++] = strdup(pch);
		pch = strtok(NULL, "\n");
	}

	strcpy(cmd, array[0]);
	cmd[strlen(cmd)] = '\0';
	for(int j = 0; j < i; j++){
		par[j] = array[j];
	}
	
	par[i] = NULL;
	

	

}
