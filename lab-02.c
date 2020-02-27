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
			// 0 is read end, 1 is write end 
		    int pipefd[2];  
		    pid_t p1, p2; 

		    if (pipe(pipefd) < 0) { 
			printf("\nPipe could not be initialized"); 
			return -1; 
		    } 
		    p1 = fork(); 
		    if (p1 < 0) { 
			printf("\nCould not fork"); 
			return -1; 
		    } 

		    if (p1 == 0) { 
			// Child 1 executing.. 
			// It only needs to write at the write end 
			close(pipefd[0]); 
			dup2(pipefd[1], STDOUT_FILENO); 
			close(pipefd[1]); 
			execve(cmd,parameters,envvar);
			    
		    } else { 
			// Parent executing 
			p2 = fork(); 

			if (p2 < 0) { 
			    printf("\nCould not fork"); 
			    return -1; 
			} 

			// Child 2 executing.. 
			// It only needs to read at the read end 
			if (p2 == 0) { 
			    close(pipefd[1]); 
			    dup2(pipefd[0], STDIN_FILENO); 
			    close(pipefd[0]); 
			    execve(cmd,parameters,envvar);
			     
			} else { 
			    // parent executing, waiting for two children 
			    wait(NULL); 
			    wait(NULL); 
			} 
		    } 
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
