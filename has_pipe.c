int has_pipe(char * input_line){
	if(strstr(input_line,"|") == 1){
		return 1;
	}
	return 0;
}
