//Brendan Burke
/*testspeed.c writes to and reads from a large 2 GB file using varying buffer sizes (64 bytes
 *to 64 KB, doubling size at each step).The function uses the clock (clock()) and
 *time (time(NULL)) timing measurement routines to measure time of execution
 *and wall clock time, respectively, for each of the read
 *and write operations. Timing information for each of the buffers is written to
 *a (output) text file "mydata.txt".
*/

#include "P4Header.h"

//size of file
#define filesize 2259156992 //2.1 GB is size of input file

void testspeed (){

	int i;

	//buffer pointer
	char *buffer;
	//variables for start and end CPU execution times...
	clock_t start_read, end_read, start_write, end_write;
	//variables for calculating wall clock times...
	time_t a, b, a2, b2;

	//variables for CPU execution times
	double cpu_time_used_r, cpu_time_used_w;

	//file vars
	FILE *myfile;
	FILE *myfile2;
	FILE *putResultsHere;

	//open and set up file where timing results will be written
	putResultsHere = fopen("mydata.txt","w");
	//set up results file
	fprintf(putResultsHere,"File Size (Bytes) : %ld\n",filesize);
	fprintf(putResultsHere,"Buffer Size (Bytes), CPU Write Time, Write Time, CPU Read Time, Read Time...\n");


	int buffersize = 64; //min buffer size is 64 bytes
	int maxbuffersize = 65536; //max buffer size is 64 KB

	//# buffers to read and write to get desired file size
	int how_many;

	//perform read and writes for varying buffer sizes of 64 bytes to 64 KD, doubling at each step
	for(buffersize=64; buffersize <= maxbuffersize; buffersize= buffersize *2){

		buffer = (char*) malloc(buffersize*sizeof(char)); //create buffer of proper size

		//check that the buffer was actually created
		if (buffer == NULL){
			printf("Memory not allocated");
			return;
		}

		//calculate how many read and write loops needed for file size
		how_many = filesize/buffersize;

		//helpful info goes to terminal...buffer size and corresponding # of loops
		printf("Buffer Size: %i \t # R/W Loops: %i \t",buffersize,how_many);

		//print buffer size to line in the results file
		fprintf(putResultsHere, "%d ,",buffersize);

		//perform and measure time to write
		a = time(NULL); //start wall clock
		start_write = clock(); //start cpu time
		myfile = fopen("RWme.txt", "w"); //open file to be written to
		//write buffer however many times needed for file size
		for(i = 0;i<how_many;i++)
		{
		fwrite(buffer,buffersize,1,myfile);
		}
		fclose(myfile); //close file for writing
		b = time(NULL); //end wall clock
		end_write = clock(); //end cpu time

		//calculate execution time for the write...
		cpu_time_used_w = ((double) (end_write - start_write)) / CLOCKS_PER_SEC;

		//print wall clock write time (b-a) to screen
		printf("Write: %ld \t",(b-a));

		//write the write time results to results file

		fprintf(putResultsHere,"%g, %ld, ",cpu_time_used_w, (b-a));


		//read the file and measure time to read
		a2 = time(NULL); //start wall clock time
		start_read = clock(); //start cpu time
		myfile2 = fopen("InputHP.txt", "r"); //open input file to be read
		//read buffer however many times needed for file size
		for(i=0; i<how_many; i++){

			fread(buffer, buffersize, 1, myfile2);
		}
		fclose(myfile2); //close file for reading

		b2 = time(NULL); //end wall clock time
		end_read = clock(); //end cpu time

		//calculate execution time for the read...
		cpu_time_used_r = ((double) (end_read - start_read)) / CLOCKS_PER_SEC;

		//print read wall clock time (b2-a2) to screen
		printf("Read: %ld \n",(b2-a2));

		//write read time results to results file
		fprintf(putResultsHere,"%g, %ld\n",cpu_time_used_r,(b2-a2));

		//printf("%f \n %f",cpu_time_used_r,cpu_time_used_w); //debugging
		//printf("%f, %f\n",end_read,end_write); //debugging

		//free current buffer so new buffer can be allocated
		free(buffer);
	}
	printf("done"); //done with the loop
	fclose(putResultsHere); //close the file with info on R/W times

	return;

}

