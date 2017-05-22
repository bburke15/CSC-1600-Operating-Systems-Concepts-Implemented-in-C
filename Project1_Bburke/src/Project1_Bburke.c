/*
 ============================================================================
 Name        : Project1_Bburke.c
 Author      : Brendan Burke
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
//Brendan Burke
/*Introduction: Project 1 involves building a command processor, popularly called a "shell."
 * The project must run an infinite loop to prompt the user and respond to the user,
 * read the user's response (fgets or scanf), extract (strtok) the command to be executed,
 * respond to the command quit by exiting the shell program (strncmp to do the needed comparison,
 * respond to legal Unix commands by using the shell program to execute them,
 * and respond to illegal commands with "Command not found."
 * Several related files should be created for the project: Project1_Bburke.c to direct performance
 * of the above six items, type_prompt.c with a function to write a prompt message to the user,
 * read_command.c with a function to read user input and convert it into an array suitable for passing
 * to the execvp function, and a header file (Fig10-7.h) to contain include statements.
*/

//Project1_Bburke.c directs performance (of the 6 items mentioned in the intro)
#include "Fig10-7.h"
int main(int argc, char *argv[]) {
	setbuf(stdout,NULL);
	char* command[MAX_CMD];
	char* params[MAX_ARGS];
	int status;
	pid_t pid;
	int count=0;
	while(1){ //runs an infinite loop to prompt the user and respond to the user
		type_prompt(); //display prompt on screen; asks user for command
		read_command(command, params); //read input line from keyboard
		//printf("read_cmd returned %s, count is %d",command,count); //for debugging purposes
		pid = fork(); //fork off a child process
		if(pid<0){
			printf("Unable to fork"); //error condition
			if(count>0) exit(0);
			continue;//repeat loop
		}
		else if(pid!=0){
			waitpid(pid,&status,0); //parent waits for child
			//printf("finished pid=%d when status=%d", pid, status); //for debugging purposes
		}
		else{
			int value = execvp(command,params); //child does work
			printf("Command not found. execvp failed and returned %d\n",value);
			exit(value);
		}
	}
	printf("termination with count = %d\n",count);
	return 0;
}

