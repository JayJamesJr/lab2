#include<string.h>
#include"combine_paths.h"
void combine_paths(char *path, char *cmd,char *command){
	strcpy(cmd,path);
	strcat(cmd,"/");
	strcat(cmd,command);
}
