#include"file_exists.h"
#define NUM_PATHS 6
int file_exists(char* filepath){
	if (access(filepath, F_OK) != -1){
		return 1;	
	}		
	return 0;
}
