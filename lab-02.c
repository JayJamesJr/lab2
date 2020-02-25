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
			
		//char *args[] = {"/bin/echo","Hello World",NULL};
		char cmd[256], command[256], *parameters[20];
		char *envvar[] = {(char*) getenv("PATH"),0};
		printf("%s",getenv("PATH"));
		char * path = getenv("PATH");
		char ** tokens = extract_tokens(path,":");
		while(1){	
		print_input_token();
		parse_tokens(command, parameters);
		printf("%s",parameters[1]);
		if(fork() != 0)
		{
			wait(NULL);
		
		}else{
			strcpy(cmd,"/bin/");
			strcat(cmd,command);
			//int status = execve(cmd,parameters,envvar);
			if(execve(cmd,parameters,envvar) < 0){
				memset(cmd,0,256);
				for(int i = 0; i < 7; i++){
					strcpy(cmd,tokens[i]);
					strcat(cmd,command);
					if(execve(cmd,parameters,envvar) > 0)
						break;
					else{
						memset(cmd,0,256);
					}
				}
			}
					
		}
		if(strcmp(command, "exit") == 0){
			break;
		}
	
		}
		return 0;
	}
