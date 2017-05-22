/*
 ============================================================================
 Name  Brendan Burke      : Project0_bburke15.c
 ============================================================================
 */
/*
 * Introduction: Project 0 involves building a program to prompt for a user ID and password.
 * The program must be in the C programming language.
 * The correspondences between user names and passwords must reside in a separate file called "passwrd."
 */
#include <stdio.h>
#include <stdlib.h>
int main(void) {
	FILE *secret;
	secret = fopen("passwrd.txt","r");
	//Open the file passwrd.txt to be read
	int wrong=1;
	char username[20]; //array for actual user name
	char pass[200]; //array for actual password
	char testname[20]; //array for entered user name
	char testpass[200]; //array for entered password
	setbuf(stdout,NULL);
	//prompt user for user name and password
	printf("Enter User name:");
	scanf("%s",testname);
	printf("Enter Password:");
	scanf("%s",testpass);
	/*assigning strings in passwrd.txt to the corresp vars, while loop continues so long as there
	 * is a user name and password to be read.
	 */
	while (fscanf(secret, "%s %s", &username, &pass) == 2){
		if (strcmp(username, testname)==0 && strcmp(pass,testpass)==0){
			//if it's a match, give pos feedback and exit loop
			printf("Correct. Welcome.\n");
			wrong=0;
			break;
		}
	}
	if(wrong==1){
		//if no match, give neg feedback
		printf("Sorry. Password for %s is not %s\n", testname, testpass);
	}
	fclose(secret); //close file
	return EXIT_SUCCESS;
}
