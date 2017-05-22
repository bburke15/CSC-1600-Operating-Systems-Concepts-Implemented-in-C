/*
 ============================================================================
 Name        : Project2.c

 Author      : Brendan Burke
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
//Brendan Burke
/*Introduction: Project 2 involves using threads to process large quantities of data (big data).
The two sets of data are "Revenue," which contains the set of money collected at each of the
firm's shops, and "Expenses," which contains the set of measures of the expenses incurred at
each of the firm's shops. Altogether, Project 2 must read the data, compute an estimate
of net profits for each of the 5000 shops (5000 observations of each variable), and then
summarize profits for each of the 5 regions (each with 1000 shops). To obtain net profits
for each shop, expenses and overhead (assessed proportional share of corporate HQ expenses, equal
to that shops' percentage of total corporate revenue) must be subtracted
from the revenue of each shop. The program must use two concurrent threads
to read data and fill the data structures, and five concurrent threads must be used to
compute profits for the five regions.
Several related files should be created for the project: Project2.c to direct performance
(calls ThreadSupervisor.c) and serve as an entry point, a header file (helpfulVariables.h)
to contain include statements, constant definitions, function prototypes,
and data structure definitions, ThreadSupervisor.c to handle thread operations and output results to screen,
accountingFunction.c to perform profit calculations, and dataFiller.c to read values in from file.*/

//Project2.c directs performance and is an entry point for the program.

#include "helpfulVariables.h"

int main(int argc, char *argv[]) {
	setbuf(stdout,NULL); //to ensure that program works on Cygwin

	//starts the project
	int num_Regs = 5; //5 regions
	int num_Objs = 1000; //number of shops in each region is; 1000 per region


	ThreadSupervisor(num_Objs,num_Regs,false); //calls ThreadSupervisor

	return (0);
}
