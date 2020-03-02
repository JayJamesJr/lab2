#include"functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<string.h>
#define NUMPATHS 6

//method to determine if the path does indeed exist.
char * check_path(char *command){
	char *path = getenv("PATH");
	char **tokens = extract_tokens(path, ":");
	char filepath[256];
	char *file = NULL;
	for(int i = 0; i < NUMPATHS; i++){
		strcpy(filepath,tokens[i]);
		strcat(filepath,"/");
		if(file_exists(strcat(filepath,command)) == 1){
			printf("Command found in filepath: %s", filepath);
			file = filepath;
		}else{
			memset(filepath,0,256); //used to fill memory
		}
	}
	return file;
}

void combine_paths(char *path, char *cmd,char *command){
	strcpy(cmd,path);
	strcat(cmd,"/");
	strcat(cmd,command);
}

char ** extract_tokens(char *str, char* delim){
	
	char ** tokens = malloc(sizeof(char*) * 10);
	if(tokens == NULL)
		return NULL;
	
	int i = 0;
	char *token = strtok(str,delim);
	while(token != NULL)
	{
		tokens[i++] = token;
		token = strtok(NULL, delim);
		
	}
	return tokens;

}

//method to check that the path is valid
int file_exists(char* filepath){
	if (access(filepath, F_OK) != -1){ //F_OK looks for existence of file
		return 1;	
	}		
	return 0;
}

//checks for | symbol in user input
int has_pipe(char * input_line){
	if(strchr(input_line,'|') != NULL){
		return 1;
	}
	return 0;
}

//method for determining if user input has exit or cd
char * has_builtin(char* command){
	int num_builtins = 2;
	char * builtins[2] = {"exit","cd"};
	char ** command_tokens = extract_tokens(command, " ");
	for(int i = 0; i <num_builtins; i++){
		if(strstr(builtins[i],command_tokens[0]) != NULL){
			char *cmd = command_tokens[0];
			return cmd;
		}
	}
	return NULL;
}

//parses the tokens so we can get each individual input
char* parse_tokens(char cmd[], char *par[]){

	char input_line[1024];
	int count = 0;
	char *array[256], *pch;
	int i = 0;

	fgets(input_line,1024,stdin);
	pch = strtok(input_line," \",\n"); //breaks string into tokens
	while(pch != NULL){	
		array[i++] = strdup(pch);
		pch = strtok(NULL," \n");
	}

	for(int j = 0; j < i; j++){
		par[j] = array[j];
	}
	strcpy(cmd,array[0]);
	par[i] = NULL;
	char *line = input_line;
	return line;
}

void print_input_token(){
	char env[512];
	setenv("PS1","$",1);
	printf("%s@%s%s",getenv("USER"),getenv("PWD"),getenv("PS1")); //print $ as default prompt
}

void unix_shell(){
	char cmd[256], command[256], *parameters[20];
		char *envvar[] = {(char*) getenv("PATH"),0};
		char *bin = "/bin";
		while(1){
			print_input_token();
			char * input_line = parse_tokens(command,parameters);
			int has_pipe_char = has_pipe(input_line);
		if(has_pipe_char == 1){
			// 0 is read end, 1 is write end 
		    int pipefd[2];  
		    pid_t p1, p2; 

		    if (pipe(pipefd) < 0) { 
			printf("\nPipe could not be initialized"); 
			return; 
		    } 
		    p1 = fork(); 
		    if (p1 < 0) { 
			printf("\nCould not fork"); 
			return; 
		    } 

		    if (p1 == 0) { 
			// Child 1 executing.. 
			// It only needs to write at the write end 
			close(pipefd[0]); 
			dup2(pipefd[1], STDOUT_FILENO); 
			close(pipefd[1]);
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
		    } else { 
			// Parent executing 
			p2 = fork(); 

			if (p2 < 0) { 
			    printf("\nCould not fork"); 
			    return; 
			} 

			// Child 2 executing.. 
			// It only needs to read at the read end 
			if (p2 == 0) { 
			    close(pipefd[1]); 
			    dup2(pipefd[0], STDIN_FILENO); 
			    close(pipefd[0]);
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
			}} else { 
			    // parent executing, waiting for two children 
			    wait(NULL); 
			    wait(NULL); 
			} 
		    } 
		}else{
			//checks for exit/cd
			char* builtin = has_builtin(input_line);
			if(builtin != NULL){
				if(strstr(builtin,"exit") != NULL){ //if statement to initiate exit
					break;		
				}else if(builtin,"cd" != NULL){ //if statement to initiate cd
					char buf[1024];					
					chdir(parameters[1]);
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
}
