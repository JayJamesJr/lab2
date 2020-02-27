char * check_path(char *command);
void combine_paths(char * path, char *cmd, char *command);
int executeCMD(char* userInput);
char ** extract_tokens(char * str, char * delim);
int file_exists(char* filepath);
int has_pipe(char * input_line);
void parse_tokens(char cmd[], char *par[]);
void print_input_token();
