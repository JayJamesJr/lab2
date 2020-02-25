#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include "print_input_token.c"
#include "parse_tokens.c"
#include "extract_tokens.c"
#define BUFSIZE 256
#define NUM_PATHS 6
	int main(int argc, char *argv[]){
			
		char cmd[256], command[256], *parameters[20];
		char *envvar[] = {(char*) getenv("PATH"),0};
		char * path = getenv("PATH");
		char ** PATH = extract_tokens(path,":");
		while(1){	
		print_input_token();
		parse_tokens(command, parameters);
		if(fork() != 0)
		{
			wait(NULL);
		
		}else{
			for(int i = 0; i < NUM_PATHS; i++){
				strcpy(cmd,PATH[i]);
				strcat(cmd,"/");
				strcat(cmd,command);
				if (access(cmd, F_OK) != -1){
					execve(cmd,parameters,envvar);
				}else if(strstr(parameters[0],"exit")){
					exit(0);
				}
				else if(strstr(parameters[0],"cd")){
					chdir(parameters[0]);
				}
				else
				{

				}	
			}	
		}
	
		}
		
		return 0;
	}
