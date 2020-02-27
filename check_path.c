#include"check_path.h"
#include"extract_tokens.h"
#include"file_exists.h"
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
