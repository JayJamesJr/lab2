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
#include "check_path.c"
#define BUFSIZE 256

int main(int argc, char *argv[]){
			
		char cmd[256], command[256], *parameters[20];

		char *envvar[] = {(char*) getenv("PATH"),0};
		char *bin = "/bin";
		int pipefd[2];
		pipe(pipefd);
		while(1){
			print_input_token();
			//parse_tokens(command, parameters);
		if(fork() != 0)
		{
			//wait(NULL);
			//printf("in parent\n");
			//print_input_token();
			parse_tokens(command,parameters);
			combine_paths(bin,cmd,command);
			if(file_exists(cmd) == 1){
				dup2(pipefd[1], 1);
				close(pipefd[0]);
				execve(cmd,parameters,envvar);
			
			}else{
				char*path = check_path(command);
				if(path != NULL){
					dup2(pipefd[1],1);
					close(pipefd[0]);
					execve(path,parameters,envvar);
				}else{
					perror("Command not found");
				}
			}
		}else{
			
			//printf("%s\n","In child");
			parse_tokens(command,parameters);
			combine_paths(bin,cmd,command);
			if(file_exists(cmd) == 1){
				dup2(pipefd[0], 0);
				close(pipefd[1]);
				execve(cmd,parameters,envvar);
			
			}else{
				char*path = check_path(command);
				if(path != NULL){
					dup2(pipefd[0],0);
					close(pipefd[1]);
					execve(path,parameters,envvar);
				}else{
					perror("Command not found");
				}
				// close(pipefd[1]);
				
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
