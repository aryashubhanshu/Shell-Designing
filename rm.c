#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void rem(int argc, char *args[]){

	if(argc==1){
		printf("Give a name\n");
	}

	if(strcmp(args[1],"-v")==0){
		DIR *dir =opendir(args[2]);
		if(dir){
			printf("This is a directory\n");
			closedir(dir);
		}
		else{
			int result=remove(args[2]);
			if(result == 0){
				printf("File deleted \n" );
			}
			else{
				printf("Error: File not deleted ");

			}
		}
	}
	else if(strcmp(args[1],"-i")==0){
		printf("Continue to delete the file?\n");
		char ans[10];
		gets(ans);
		char *temp;
		temp=strtok(ans," ");
		printf("%stemp\n",temp );
		if (strcmp(temp,"no")==0 ||strcmp(temp,"No")==0 )
		{
			printf("++++\n");
		}
		else{
			printf("\n");
			DIR *dir =opendir(args[2]);
			if(dir){
				printf("This is a directory\n");
				closedir(dir);
			}
			else{
				int result=remove(args[2]);
				if(result == 0){
					printf("File deleted \n" );
				}
				else{
					printf("Error: File not deleted ");

				}
			}
		}
	}
	else{
		DIR *dir =opendir(args[1]);
		if(dir){
			printf("This is a Directory\n");
			closedir(dir);
		}
		else{
			int result = remove(args[1]);
			if(result == 0){
				printf("File deleted \n" );
			}
			else{
				printf("Error: File not deleted");
			}
		}
	}
}

int main(int argc, char const *args[]){

	rem(argc, args);
	
	return 0;
}
