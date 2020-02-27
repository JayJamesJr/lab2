#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include "print_input_token.c"
#include "parse_tokens.c"
#include "extract_tokens.c"
#include "executeCMD.c"
#include "pipe.c"
#include "combine_paths.c"
#include "file_exists.c"
#define BUFSIZE 256

int main(int argc, char *argv[]){
			
		char cmd[256], command[256], *parameters[20];
		char *envvar[] = {(char*) getenv("PATH"),0};
		int pipefd[2];
		pipe(pipefd);
		
		while(1){
			print_input_token();
			parse_tokens(command, parameters);
		if(fork() != 0)
		{
			//wait(NULL);
			// printf("in parent\n");
			//dup2(pipefd[1],1);
			// close(pipefd[0]);
			parse_tokens(command, parameters);
			execve(cmd, parameters, envvar);

		}else{
			memset(command, 0, 256);
			memset(cmd, 0, 256);
			memset(parameters, 0, sizeof(char *) *20);
			parse_tokens(command,parameters);
			combine_paths("/bin",cmd,command);
			dup2(pipefd[0], 0);
			if(file_exists(cmd) == 1){
				// close(pipefd[1]);
				execve(cmd,parameters,envvar);
			
			}else{
				// close(pipefd[1]);
				perror("Command not found");
			}	
		}
		if(strcmp(command,"cd") == 0){
			char buffer[1024];
			char* dir = getcwd(buffer,1024);
			strcat(dir,"/");
			strcat(dir,parameters[0]);
			chdir(parameters[0]);
			//chdir(dir);
		}
		if(strcmp(command,"exit") == 0){
			printf("Terminating shell\n");
			exit(0);
		}
						}
		
		return 0;
	}