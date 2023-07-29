#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void shell_mkdir(int argc, char *args[]){

	if(argc==1){
		printf("Give a name\n");
	}


	if(strcmp(args[1],"-v")==0){
		DIR* dir =opendir(args[2]);
		if(dir){
			printf("Directory available\n");
			closedir(dir);
		}
		else{
			mkdir((const char *)args[2], S_IRWXU);
			printf("Directory created \n" );
		}
	}
	else if(strcmp(args[1],"-m")==0){
		int mode =atoi(args[2]);

		DIR* dir =opendir(args[3]);
		if(dir){
			printf("Directory available\n");
			closedir(dir);
		}
		else{
			mkdir((const char *)args[3], mode);
			printf("Directory created \n" );
		}
	}
	else{
		DIR* dir =opendir(args[1]);
		if(dir){
			printf("Directory available\n");
			closedir(dir);
		}
		else{
			mkdir((const char *)args[1], S_IRWXU);
		}
	}
}

int main(int argc, char const *args[]){

	shell_mkdir(argc, args);
	
	return 0;
}
