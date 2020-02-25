#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

