#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#include "print_input_token.c"
#include "parse_tokens.c"
#include "extract_tokens.c"
#include "executeCMD.c"
#include "pipe.c"
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
				
				}
				else if(strstr(command, "ls")) {
					//OSpipe();
				}
			
			}
				
		}
		if(strcmp(command,"exit") == 0){
			exit(0);
		}
	
		
		else if(strcmp(command,"cd") == 0){
			char buffer[1024];
			char* dir = getcwd(buffer,1024);
			strcat(dir,"/");
			strcat(dir,parameters[0]);
			chdir(dir);
		}
		}
		
		return 0;
	}
