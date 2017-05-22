//Brendan Burke
/*read_command.c contains a function to read input from the user and
 * convert into array suitable to passing to execvp function
*/
#include "Fig10-7.h"

void read_command(char* command, char* params[]){
	char com[200]; //array to hold user input
	fgets(com,MAX_CMD,stdin); //read user's response with fgets (whole command line)
	char* token; //to parse line into a list of arguments, will need to "tokenize"
	char const delimeters[4] = " \n\r";
	//on Windows, strtok delim include all three of space, newline, and carriage return.

	int num_args=0;
	//tokenizing is destructive, so make a copy
	char* commandcopy=(char *)malloc (strlen(com)+2);
	strcpy(commandcopy,com);//copy user input string over to commandcopy

	int comLength = (int) strlen(com)-2; //length of com (command); -2 for Windows
//if the input is "quit" (same # of char, not including space, etc.) then exit the shell
	if((comLength==4)&&(strncmp(com, "quit",4)==0)){
		printf("\nExiting shell. Bye!\n");
		exit(0);
	}

	token = strtok(commandcopy,delimeters); //"tokenize" command using whitespace, \n,\r as delimiters
	//invoke strtok so that we can extract the command to be executed
	strcpy(command, token);
	//printf("Requested cmd = %s",command); //for debugging purposes
	params[0] = token;

	//tokenize the arguments
	//loop checks that, one, the size isn't too large and, two, that haven't reached end of loop
	token = strtok(NULL,delimeters);
	while((num_args<MAX_ARGS)&&(token != NULL)){
		//printf(" %s ", token); //for debugging purposes
		num_args++;
		params[num_args] = token; //initialize params with whatever token's pointing to
		token = strtok(NULL,delimeters);
	}
	num_args++;
	params[num_args]= NULL;
	return;
}

