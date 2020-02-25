#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#include "print_input_token.c"
#include "parse_tokens.c"
#include "extract_tokens.c"
#include "executeCMD.h"
#include "pipe.c"
#define BUFSIZE 256
<<<<<<< HEAD
#define NUM_PATHS 6
=======

>>>>>>> 743469cb64a600996bc1b30add91d4baec782399
	int main(int argc, char *argv[]){
			
		char cmd[256], command[256], *parameters[20];
		char *envvar[] = {(char*) getenv("PATH"),0};
		char * path = getenv("PATH");
		char ** PATH = extract_tokens(path,":");
		int status = 1;
		while(status != 0){	
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
					status = 0;
					executeCMD("exit");
					exit(0);
				}
				else if(strstr(parameters[0],"cd")){
					chdir(parameters[0]);
				}
				else if(strstr(parameters[0], "ls")) {
					OSpipe();
				}
				else
				{

				}	
			}	
		}
	
		}
		
		return 0;
	}
