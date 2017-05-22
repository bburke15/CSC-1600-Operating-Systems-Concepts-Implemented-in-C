//Brendan Burke
//dataFiller.c, which was given in the instructions, opens files to read in values.
#include "helpfulVariables.h"

void *dataFiller(void * sourceIn) //given in instructions
{
	sourceData *source = (sourceData*) sourceIn; // to access struct
	FILE* myfile = fopen(source->srcFileName,"r"); //open file as read only
	int i=0;

	long pageA, pageX; //paging vars
	FILE* pagesOut = source -> outfile;
	setbuf(pagesOut,NULL);
	pageA = ((long) &i)/PAGESIZE; //page for argument A

	for (i=0; i<source->num_Objs; i++){
		//record page references
		fprintf(pagesOut," %ld \n",pageA);
		pageX = ((long) source->values)/PAGESIZE; //page for argument X
		fprintf(pagesOut," %ld \n",pageX);
		fscanf(myfile, "%lf", source->values++); //scan in values for each shop
	}
	fclose(myfile); //close file
	return 0;
}



