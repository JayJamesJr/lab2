#include"file_exists.h"
#define NUM_PATHS 6
int file_exists(char* filepath){
	char * path = getenv("PATH");
	char ** PATH = extract_tokens(path,":");
	for(int i = 0; i < NUM_PATHS; i++){
		if (access(filepath, F_OK) != -1){
			return 1;	
		}	
	}
	return 0;
}
