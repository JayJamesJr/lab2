#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"extract_tokens.h"
char ** extract_tokens(char *str, char* delim){
	
	char ** tokens = malloc(sizeof(char*) * 7);
	if(tokens == NULL)
		return NULL;
	
	int i = 0;
	char *token = strtok(str,delim);
	while(token != NULL)
	{
		tokens[i++] = token;
		token = strtok(NULL, delim);
	
	}
	return tokens;

}
