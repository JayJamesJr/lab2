#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include"functions.c"
#define BUFSIZE 256

int main(int argc, char *argv[]){
			
		char cmd[256], command[256], *parameters[20];
		char *envvar[] = {(char*) getenv("PATH"),0};
		char *bin = "/bin";
		while(1){
			print_input_token();
			char * input_line = parse_tokens(command,parameters);
			int has_pipe_char = has_pipe(input_line);
		if(has_pipe_char == 1){
			//handle_fork();
		}else{
			char* builtin = has_builtin(input_line);
			if(builtin != NULL){
				if(strstr(builtin,"exit") != NULL){
					break;		
				}else if(builtin,"cd" != NULL){
					char buf[1024];
					chdir(strcat(getcwd(buf,1024),parameters[0]));
				}	
			}else{ 
				if (fork() == 0){
					combine_paths(bin,cmd,command);
					if(file_exists(cmd) == 1){
					
						execve(cmd,parameters,envvar);
					}else{
						char*path = check_path(command);
						if(path != NULL){
							execve(path,parameters,envvar);
						}else{
						perror("Command not found");
					}
		
					}	
				}else{
					wait(NULL);
				}
			
			}
		}
			
	}
		
		return 0;
	}
