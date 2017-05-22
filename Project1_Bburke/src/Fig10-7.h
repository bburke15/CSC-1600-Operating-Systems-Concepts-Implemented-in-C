//Brendan Burke
//Header file Fig10-7.h contains include statements, constant definitions, and function prototypes.
#ifndef FIG10_7_H_
#define FIG10_7_H_

//include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef enum {FALSE, TRUE} boolean;

#define MAX_CMD 256
#define MAX_ARGS 128

//function prototypes
void type_prompt();
void read_command(char* command, char* params[]);

#endif
