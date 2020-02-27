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
	
	char ** tokens = malloc(sizeof(char*) * 6);
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
	if(strstr(input_line,"|") == 1){
		return 1;
	}
	return 0;
}

int is_builtin(char* command){
	int num_builtins = 2;
	char * builtins = {"exit","cd"};
	for(int i = 0; i <num_builtins; i++){
		if(strstr(builtins,command) == 0){
			return 1;
		}
	}
	return 0;
}

void parse_tokens(char cmd[], char *par[]){

	char input_line[1024];
	for(int i = 0; i < 1024; i++){
		input_line[i] = 0;
	}

	
	int count = 0;
	char *array[256], *pch;
	int i = 0;


	fgets(input_line,1024,stdin);
	pch = strtok(input_line, " ");
	while ( pch != NULL){
		array[i++] = strdup(pch);
		pch = strtok(NULL, "\n");
	}

	strcpy(cmd, array[0]);
	cmd[strlen(cmd)] = '\0';
	for(int j = 0; j < i; j++){
		par[j] = array[j];
	}
	par[i] = NULL;
}

void print_input_token(){
	printf("$");
}



