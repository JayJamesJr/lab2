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
		unix_shell();
		return 0;
	}
