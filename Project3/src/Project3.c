//Brendan Burke
/*Project 3 involves modifying Project 2 to calculate page numbers referenced by the code.
PAGESIZE must be set to 4096. Groups Numbers (region, district, and section) are varied
as well as the number of shops per group. Lists of the page references in the loop in the threads that
read the data, the loop that calculates the overheads, and the loop in the accounting function executed
in the threads must all be calculated and saved. Pages references are written to file
in the order in which they occurred. The quickLRU() function then calculates fault rate as a function
of the number of frames and output is written to an excel file.
Project3.c directs performance and is an entry point for the program*/
#include "helpfulVariables.h"

int main(int argc, char *argv[]) {
	setbuf(stdout,NULL);

	//starts the project
	int num_Regs = 125; //5 regions, or  25 districts, or 125 sections (change for each run)
	int num_Objs = 40; /*number of shops in each region is; 1000 per region,
	200 per district, 125 per section*/


	ThreadSupervisor(num_Objs,num_Regs,false); //calls ThreadSupervisor
	quickLRU(); //call quickLRU function
	return (0);
}
