//Brendan Burke
/*Header file helpfulVariables.h contains include statements, constant definitions,
function prototypes, and data structure definitions.*/
#ifndef HELPFULVARIABLES_H_
#define HELPFULVARIABLES_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*function prototypes for functions required by project: ThreadSupervisor, dataFiller,
and the accounting function*/
int ThreadSupervisor(int num_Objs, int num_Regs, bool Valid);
void *dataFiller(void *sourceData);
void *accountingFunction(void *currVar);
/*create a data structure containing four variables (Revenue, Expenses, Overhead, Profits),
each of which should be an array of 5000 elements*/
typedef struct currentVariables //provided data structure for variables
{
	double *Revenue;
	double *Expenses;
	double *Overhead;
	double *Profit;
	double RegionProfit;
	bool beChatty;
	int reg_Num;
	int start_reg;
	int number_shops;
} currVar;
typedef struct input_data //provided data structure for input data
{
	char* srcFileName;
	double *values;
	int num_Objs;
	bool beChatty;
} sourceData;

//refer to type of expression with typeof
//writing in header file, so write __typeof___ instead of typeof

/*define safe “max” and "min" macros which operate
on any arithmetic type and evaluates each of its arguments exactly once:*/
#define max(a,b) \
({__typeof___ (a) _a = (a); \
  __typeof___ (b) _b} = (b); \
  _a > _b ? _a : _b; })
#define min(a,b) \
({__typeof___ (a) _a = (a); \
  __typeof___ (b) _b} = (b); \
  _a > _b ? _a : _b; }
#endif



