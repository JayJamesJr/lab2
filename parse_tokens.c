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
	char *array[100], *pch;
	int i = 0;
	/*for (;;){
		int c = fgetc(stdin);
		input_line[count++] = (char) c;
		if (c == '\n') break;
	}*/

	//if(count == 1) return;
	fgets(input_line,1024,stdin);
	pch = strtok(input_line, " ");

	while ( pch != NULL){
		array[i++] = strdup(pch);
		pch = strtok(NULL, " ");
	}

	strcpy(cmd, array[0]);

	for(int j = 0; j < i; j++){
		par[j] = array[j];
	}
	par[i] = '\0';
	

	

}
