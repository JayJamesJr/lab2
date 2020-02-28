#include"functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<string.h>
#define NUMPATHS 6

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
			memset(filepath,0,256);
		}
	}
	return file;

}

void combine_paths(char *path, char *cmd,char *command){
	strcpy(cmd,path);
	strcat(cmd,"/");
	strcat(cmd,command);

}
// void catCommand(char userInput) {

//     int size = strlen(userInput - 1);

//     char skippedUserInput[size];

//     char delimiter[] = " ";

//     char finalString[100];



//     for(int i = 1; i < strlen(userInput); i++) {

//         skippedUserInput[i] = userInput[i];

//     }



//     char *ptr = strtok(skippedUserInput, delimiter);



//     while(ptr != NULL) {

//         strcat(finalString, ptr);

//         ptr = strtok(NULL, delimiter);

//     }



//     printf("Concatonated string: %s\n", ptr); 

// }



int executeCMD(char* userInput) {
    int numCommands = 5;
    int switching = 0;
    char* listOfCommands[numCommands];

    //array for available commands in the shell
    listOfCommands[0] = "exit";
    listOfCommands[1] = "cd";
    listOfCommands[2] = "cat";
    listOfCommands[3] = "bash";
    listOfCommands[4] = "uname";

    //iterating through the commands to see if there is a match

    for(int i = 0; i < numCommands; i++) {
        if(strcmp(userInput, listOfCommands[i]) == 0) {
           switching = i+1;
            break;
        }

        // else if(listOfCommands[4] != 0) {
        //     printf("\nCommand not found\n");
        //     break;
        // }

        else {
            printf("Program terminated with exit code N");
        }
    }
    switch(switching) {
        //case for exiting the shell
        case 1:
            printf("\nTerminating shell\n");
            return(0);
            exit(1);

        //case for changing directory
        case 2:
            //chdir(userInput[1]);
            return 1;
        //case for concatonation
        case 3:
            // printf("\n");
            // catCommand(userInput[1]);
            // exit(0);

        //case for bash command

        case 4:

        case 5:

            printf("Linux");

        default:
            break;

    }

    return 0;

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

int file_exists(char* filepath){
	if (access(filepath, F_OK) != -1){
		return 1;	
	}		
	return 0;
}

int has_pipe(char * input_line){
	if(strchr(input_line,'|') != NULL){
		return 1;
	}
	return 0;
}

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

char* parse_tokens(char cmd[], char *par[]){

	char input_line[1024];

	int count = 0;
	char *array[256], *pch;
	int i = 0;


	fgets(input_line,1024,stdin);
	pch = strtok(input_line," \",\n");
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
	printf("$");
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
			//handle_fork();
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
			execve(cmd,parameters,envvar);
			    
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
				if(strstr(builtin,"exit") != NULL){ //if statement to initiate exit
					printf("Shell terminating\n");
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



