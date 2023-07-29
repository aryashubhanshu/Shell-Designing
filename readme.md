This is a shell created by Shubhanshu, the shell can handle three internal commands 'cd', 'echo' and 'pwd'. It can also handle 'exit' command.
These commands would by directly handled by the shell.

The shell can also able to handle five external commands 'ls', 'cat', 'date', 'rm', and 'mkdir'.
For these commands, the shell creates a new process using the fork() system call and we have called using execv() system call to run the individual program.


INTERNAL COMMANDS 

1. pwd -> This command will print the current working directory.

2. cd -> This command helps to traverse through directories with this command. 

3. echo -> This command will print the rest of the arguements that are given after the echo command.

4. exit -> This command will exit the shell.


EXTERNAL COMMANDS (with their respective methods)

1. DATE
date -> This command displays the current time in the given FORMAT, or the system date.
	(i) date -I -> It outputs date/time in ISO 8601 format. For example:2022-11-14T02:34:56-0600
	(ii) date -R ->  It outputs date and time in RFC 5322 format. For example: Mon, 14 Aug 2022 02:34:56 -0600

2. CAT
cat filename -> This command will print the file on the shell window.
	(i) cat -n filename -> It will number all output lines.
	(ii) cat -E filename -> It will display a dollar sign ($) at the end of each line.

3. MKDIR
mkdir filename -> This command will create a new directory.
	(i) mkdir -v filename -> THis will create a new file directory and give a message on successful creation.
	(ii) mkdir -m mode filename -> This will create a file directory with the given mode. 

4.LS
ls -> This command will lists all the files in the current directory.
	(i) ls -m -> This will fill width with a comma seperated list of entries.
	(ii) ls -1 -> This will list one file per line.

5. RM
rm filename -> This will delete the file with that name if it exists else gives an error.
	(i) rm -i filename -> This will give a prompt before every removal.
	(ii) rm -v filename -> This will delete the file give a message if it is deleted or not.
	


BRIEF EXPLANATION 

Shell Designing:
I have seperated the whole problem in 4 smaller parts -> loop, getting the input, splitting the input in different arguements, and finally running the command.


The first part -> loop()
This part is basically a do while loop which will terminates when the status will give false or 0, or in this case when the shell will gets the exit command, which turns the status to 0.

The loop takes the input using get_input function and then we will seperate the input into arguements using the split_input function and finally the command will be executed using the run_command function.


The second part -> get_input()
This part will take the input using the getchar function till it will encounter EOF or the line break and finally the function will return a char pointer which was allocated during the run time using the malloc function.


The third part -> split_input()
The function takes the input from previous function as arguement and then it  creates a double pointer of type char which stores all the arguments passed after the command and finally it will return the seperated arguements as tokens.


The forth part -> run_command()
The function will take the output from the previous function and then we will assign a cpid. 

For a continuous flow, firstly before running any command we will store the address of our current directory or the directory in which all the output files are stored in a root_folder char.


For the internal commands, we compare the 0th argument to command using strcmp and we call the function accordingly, all these commands return a non-zero value so that the status will be true and the loop will run infinitely:

(i) for pwd -> we simply again run the getcwd command, that will print the present working directory in which we are currently in.

(ii) for cd -> if we don't pass any arguement after cd, the function will print that we should give an arguement to cd. Otherwise simply it will run the command as usual.

(iii) for echo command -> if we don't pass any arguement after echo command, the function will simply give a line break. Otherwise the echo command will print all the arguements given after writing echo.

(iv) for exit command -> it will simply makes the status 0 or we can say it will return 0 which takes us outside the loop terminating the shell.


For the external commands, we first creates a new process using the fork function and then if cpid==0 then we will again check the 0th arguement to the command and will pass the path to that command output file and the arguements passed after that using the execv function:

(i) date -> This file includes the time.h header file by which we can print the desired result using the strftime function.
Created two methods -I and -R, functions are told above.

(ii) cat -> We must have to give another arguement after cat, otherwise it will give an error saying Give file name. We just have to read the line using getline function and print the desired result.
Created two methods -E and -n, functions are told above.

(iii) mkdir -> Again we must have to give another arguement after mkdir, otherwise it will give an error saying Give a name. The header files to be included are sys/types.h, dirent.h, sys/stat.h. We first have to get the mode and then check if the directory is available or not if it is available we will print direcory available or we create a directory with the name passed as an arguement. We traverse the directory using opendir function and will check and create.
Created two methods -m and -v, functions are told above.

(iv) ls -> The header files to be included are sys.types.h, sys/stat.h, dirent.h. The same way as mkdir we traverse through the direcory and we just have to print the name of all the directories and files in the directory.
Created two methods -m and -1, functions are told above.

(v) rm -> Again the same header files as ls and mkdir are used and we have to traverse and find the name of the directory passed as an arguement and if we find the same name file not the directory we have to remove or delete the file using the remove function.
Created two methods -v and -i, functions are told above.

If we type anything except these 9 commands the shell will throw an error saying Command not found or if there is error in forking it will say Error in forking.


