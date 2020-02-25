#include<stdlib.h>
#include<stdio.h>
#define BUFSIZE 256
#include<string.h>
#include "extract_tokens.c"
int main(){
	char path[BUFSIZE];
	char *envvar = "PATH";

	if(!getenv(envvar)){
		fprintf(stderr,"The environment variable %s was not found\n",envvar);
		exit(1);
	}

	if(snprintf(path, BUFSIZE, "%s", getenv(envvar)) >= BUFSIZE){
		fprintf(stderr,"BUFSIZE OF %d was too small. Aborting\n",BUFSIZE);
		exit(1);
	}
	printf("PATH: %s\n",path);
        char ** tokens = extract_tokens(path,":");
	for(int i = 0; i < 7; i++){
		printf("%s\n",tokens[i]);
	}
	return 0;





}
