//Brendan Burke

//Ensures proper opening of LongSkinny.txt
//Page references (in the order in which they occur) are written to this file.
#include "helpfulVariables.h"

FILE* saveData (char* fileName){

	FILE *myfile;
	printf("opening for output file %s\n",fileName); fflush(stdout);
	myfile = fopen(fileName, "w+");
	if(myfile == NULL){
		printf("error in opening. errno = %d\n",errno); fflush(stdout);
		exit(-1); //file didn't open correctly
	}
	else{
		printf("opened for output file %s\n",fileName); fflush(stdout);
		printf("no error in opening. errno = %d\n",errno); fflush(stdout);
		//file opened without issue
	}
	return myfile;

}

