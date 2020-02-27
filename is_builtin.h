#include"functions.h"
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
