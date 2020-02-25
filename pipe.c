#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 
#include<string.h>
#include <dirent.h>

void OSpipe() {
    int pipeA[2];
    pipe(pipeA);
    int p = fork();
    char* path = getenv("PWD");
    char buffer[20];

    if (p > 0) {
        //writing to child pipe 
        write(pipeA[1], path, sizeof(path));
        close(pipeA[1]);

        //Waiting for child to write
        wait(NULL);
        read(pipeA[0], buffer, sizeof(buffer));
        close(pipeA[0]);
    }

    else {
        char buffer[20];
        struct dirent *directory;
        read(pipeA[1], buffer, sizeof(buffer));
        DIR *dr = opendir(buffer);
        if (dr == NULL) {
            printf("unable to open directory");
            exit(0);
        }

        while((directory = readdir(dr)) != NULL) {
            printf("%s\n", directory->d_name);
        }

        closedir(dr);
        write(pipeA[0], buffer, sizeof(buffer));
        close(pipeA[0]);

        exit(0);
    }
}