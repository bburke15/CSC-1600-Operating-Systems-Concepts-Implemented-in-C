//Brendan Burke
/*Project 4 involves implementing a program to measure the impact of application-level
 * buffer sizes on file read and write times. To do so, a large 2 GB file is written to and read
 * from with varying buffer sizes (64 bytes to 64 KB, doubling the buffer size each
 * step of the way). Timing measurement routines clock and time are used to measure the
 * execution time (CPU time) and wall clock time, respectively, for each read and write.
 *  Project 4.c directs performance of the program and is an entry point for the program.
 *  Main calls the testspeed() function which performs the reads and writes at
 *  different buffer sizes (and does the timing).
*/
#include "P4Header.h"

int main(void) {

	testspeed(); //call testspeed function

	return (0);
}
