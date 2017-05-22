//Brendan Burke
//LRU function provided on blackboard is implementation of LRU page replacement algorithm.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helpfulVariables.h"


void quickLRU() //modify so no parameters taken
{
	long numberOfFrames=1000;
	FILE* putResultsHere = fopen("plotthisfinal3.csv","w"); //output will go to excel file

	int fframe[numberOfFrames],used[numberOfFrames],index;
	long frameSize = 4096;
	//do calculations for # of frames values between 8 and 100 frames
for(numberOfFrames=8;numberOfFrames<101;numberOfFrames++){
	int count=0,n1=0,np=0,tmp;
	int flag=0,pf=0;
	int slotsFilled = 0;
	int numRead = 0;

	printf("\n LRU Page Replacement Algorithm \n");fflush(stdout);
	FILE* getPagesHere = fopen("LongSkinny.txt","r");

	for(count=0;count<numberOfFrames;count++)
	{
		fframe[count]=-1;
		used[count]=1<<22;
	}

	count = 0;
	while(true)
	{
		numRead = fscanf(getPagesHere,"%d", &tmp);
		if(numRead==EOF)
			{
				count--;
				break;
			}
		count++;
		np++;

		flag=0;
		for(n1=0;n1<numberOfFrames;n1++)        // is that page/frame in here?
		{
			if(fframe[n1]==tmp)
			{
				used[n1] = count;
				flag=1;
				break;         // this is a hit
			}
		}

		if(flag==0)  // this is a page fault
		{
			if( slotsFilled < numberOfFrames) // first set of misses are just added
				{
					fframe[slotsFilled] = tmp;//page[count];
					used[slotsFilled] = count;
					slotsFilled++;
				}
			else
				{
					// all numberOfFrames used have been set.  find minimum.
					index = 0;
					for (n1=0; n1 < numberOfFrames; n1++)
					{
						if(used[n1] < used[index])
							{
								index = n1;
							}
					}
					fframe[index] = tmp;
					used[index] = count;
				}
			pf++;
		}
	} // end of lru algorithm in c

	printf("\nTotal number of page faults is %d in %d pages.\n",pf,count);
	double numerator, denomenator, percentage;
	numerator = (double) pf;
	denomenator = (double) count;
	percentage = 100.0 * numerator / denomenator;
	printf(" for a Page Fault Rate of %5.2f%%\n",percentage);
	long memory = numberOfFrames * frameSize;

	printf(" for a memory allocation of %ld bytes. (%ld frames at %ld bytes each)\n\n",
			memory,numberOfFrames,frameSize);
	fclose(getPagesHere); //close file
	fflush(stdout);
	//fprintf prints results to file (# of frames, fault rate, and # of faults)
	fprintf(putResultsHere,"%li, %5.2f%%, %d\n", numberOfFrames, percentage, pf);
}
fclose(putResultsHere); //close file
}
