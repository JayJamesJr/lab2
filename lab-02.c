#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include "print_input_token.c"
#include "parse_tokens.c"
#include "extract_tokens.c"
#define BUFSIZE 256
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
			for(int i = 0; i < 7; i++){
				printf("Command is: %s",command);
				strcpy(cmd,PATH[i]);
				strcat(cmd,"/");
				strcat(cmd,command);
				if (access(cmd, F_OK) != -1){
					execve(cmd,parameters,envvar);
				}else if(strstr(parameters[0],"exit")){
					exit(0);
				}
				else if(strstr(parameters[0],"cd")){
					chdir(command);
				}
				else
				{
					printf("Command %s not found",cmd);
				}	
			}	
		}
	
		}
		
		return 0;
	}
