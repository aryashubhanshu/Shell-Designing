#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cat(int argc, char *args[]){

	FILE *file_p;

	if(argc == 1){
		printf("Give file name\n");
	}

	if(strcmp(args[1],"-n")==0){
		file_p =fopen(args[2],"r");
		if( file_p == NULL){
			perror("Error: ");
		}
		else{
			char * buffer=NULL;
			size_t l=0;
			ssize_t read;
			int count=1;
			while ((read= getline(&buffer,&l,file_p)) != -1){
				printf("%d %s",count++,buffer );
			}
			fclose(file_p);
		}
	}

	else if(strcmp(args[1],"-E")==0){
		file_p =fopen(args[2],"r");
		if( file_p == NULL){
			perror("Error: ");
		}
		else{
			char * buffer=NULL;
			size_t l=0;
			ssize_t read;
			
			while ((read= getline(&buffer,&l,file_p)) != -1){
				strtok(buffer, "\n");
				printf("%s$ \n",buffer );
			}
			fclose(file_p);
		}
	}
	
	else{
		file_p =fopen(args[1],"r");
		if( file_p == NULL){
			perror("Error: ");
		}
		else{
			char * buffer=NULL;
			size_t l=0;
			ssize_t read;
			
			while ((read= getline(&buffer,&l,file_p)) != -1){
				printf("%s ",buffer );
			}
			fclose(file_p);
		}
	}
}

int main(int argc, char const *args[]){

	cat(argc, args);
	
	return 0;
}
