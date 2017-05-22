//Brendan Burke
//dataFiller.c, which was given in the instructions, opens files to read in values.
#include "helpfulVariables.h"

void *dataFiller(void * sourceIn) //given in instructions
{
	sourceData *source = (sourceData*) sourceIn; // to access struct
	FILE* myfile = fopen(source->srcFileName,"r"); //open file as read only
	for (int i=0; i<source->num_Objs; i++){
		fscanf(myfile, "%lf", source->values++); //scan in values for each shop
	}
	fclose(myfile); //close file
	return 0;
}



