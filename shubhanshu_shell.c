#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>

#define TK_BUFF_SIZE 128
#define TOK_DELIM " \t\r\n"

int shell_exit(char **args);
int shell_pwd(char **args);
int shell_cd(char **args);
int shell_echo(char **args);

int run_command(char **args) {
	pid_t cpid;
	int status;
	
	char root_folder[200];
	getcwd(root_folder,sizeof(root_folder));

	if (strcmp(args[0], "exit") == 0) {
		//printf("I am called! \n");
		return shell_exit(args);
	}
	else if(strcmp(args[0], "pwd") == 0) {
		//printf("I am called! \n");
		return shell_pwd(args);	
	}
	else if(strcmp(args[0], "cd") == 0) {
		//printf("I am called! \n");
		return shell_cd(args);	
	}
	else if(strcmp(args[0], "echo") == 0) {
		//printf("I am called! \n");
		return shell_echo(args);	
	}

	cpid = fork();

	if (cpid == 0) {
		if(strcmp(args[0],"date")==0){
			//printf("I am called! \n");
			//char *date_path = "/home/shubhanshu/Desktop/final_Test/date";
			
			char *date_path = strcat(root_folder,"/date");
			
			execv(date_path,args);		
		}
		else if(strcmp(args[0],"cat")==0){
			//printf("I am called! \n");
			//char *cat_path = "/home/shubhanshu/Desktop/final_Test/cat";
			
			char *cat_path = strcat(root_folder,"/cat");
			
			execv(cat_path,args);
		}
		else if(strcmp(args[0],"mkdir")==0){
			//printf("I am called! \n");
			//char *mkdir_path = "/home/shubhanshu/Desktop/final_Test/mkdir";
			
			char *mkdir_path = strcat(root_folder,"/mkdir");
			
			execv(mkdir_path,args);
		}
		else if(strcmp(args[0],"ls")==0){
			//printf("I am called! \n");
			//char *ls_path = "/home/shubhanshu/Desktop/final_Test/ls";
			
			char *ls_path = strcat(root_folder,"/ls");
			
			execv(ls_path,args);	
		}
		else if(strcmp(args[0],"rm")==0){
			//printf("I am called! \n");
			//char *rm_path = "/home/shubhanshu/Desktop/final_Test/rm";
			
			char *rm_path = strcat(root_folder,"/rm");
			
			execv(rm_path,args);
		}
		else if (execvp(args[0], args) < 0)
			printf("Command not found: %s\n", args[0]);
	    		exit(EXIT_FAILURE);
	  	} 
	  	else if (cpid < 0)
	    		printf( "Error in forking \n");
	  	else {
	    		waitpid(cpid, &status, WUNTRACED);
	  	}
	  	
	return 1;
}

//EXIT COMMAND
int shell_exit(char **args) {
	return 0;
}

//PWD COMMAND
int shell_pwd(char **args) {
	
	char wd[1000];
	printf("Current working directory: %s \n", getcwd(wd,sizeof(wd)));
	
	return 1;
}

//CD COMMAND
int shell_cd(char **args) {
	
	if (args[1] == NULL) {
    		fprintf(stderr, "Give an argument to \"cd\"\n");
  	} else {
    		if (chdir(args[1]) != 0) {
      		perror("shell");
    		}
  	}
  	
	return 1;
}

//ECHO COMMAND
int shell_echo(char **args) {
	
	if(args[1]==NULL){
		printf("\n");
	}
	else{
		int i=1;
		
		while(args[i]!= NULL){
			printf("%s ",args[i] );
			i++;
		}
		printf("\n");		
	}	
	return 1;
}

char **split_input(char *line) {
	
	int buffsize = TK_BUFF_SIZE, position = 0;	
	char **tokens = malloc(buffsize * sizeof(char *));
  	char *token;

	if (!tokens) {
		fprintf(stderr, "Error \n");
		exit(EXIT_FAILURE);
	}
	
	token = strtok(line, TOK_DELIM);
	
	while (token != NULL) {
	tokens[position] = token;
        position++;

        if (position >= buffsize) {
      	buffsize += TK_BUFF_SIZE;
      	tokens = realloc(tokens, buffsize * sizeof(char * ));

	      	if (!tokens) {
			fprintf(stderr, "Error \n");
			exit(EXIT_FAILURE);
	      	}
    	}
    	
	token = strtok(NULL, TOK_DELIM);
  	}
	
	tokens[position] = NULL;

	return tokens;	
}

char *get_input() {

	int buffsize = 1024;
	int position = 0;
	char *buffer = malloc(sizeof(char) * buffsize);
	int c;
	
	if(!buffer){
		fprintf(stderr, "Error \n");
		exit(EXIT_FAILURE);
	}
	
	while(1){
		c = getchar();
		if(c == EOF || c == '\n'){
			buffer[position] = '\0';
			return buffer;
		}else{
			buffer[position] = c;
		}
		position++;
		
		if(position >= buffsize) {
			buffsize += 1024;
			buffer = realloc(buffer, buffsize);
			
			if(!buffer){
				fprintf(stderr, "Error \n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

void loop() {

	char *line;
	char **args;
	
	int status = 1;
	
	do{
		printf("shubhanshu_shell>>");
		line = get_input();
		args = split_input(line);
		status = run_command(args);
		free(line);
		free(args);
	}
	while(status);	
}

int main() {

	printf("This is a shell created by Shubhanshu \n");

	loop();

	return 0;
}
