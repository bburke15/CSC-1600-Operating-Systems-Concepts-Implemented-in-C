//Brendan Burke
/*accountingFunction.c performs the profit calculation for each shop, and, in turn, each region
(or district or sector). (For k shops, Profit_k= Revenue_k - Expenses_k - Overhead_k; regional profits are computed by
summing profits in groups of individual shops).*/
#include "helpfulVariables.h"

void *accountingFunction(void *dataIn){
	int k;
	//use inputted data with currVar variables
	currVar *data = (currVar *) dataIn; //to use the void * pthreads...

	//Note: passing a pointer to struct is how to exchange info with threads

	//assign revenue, expenses, overhead, and profit from dataIn
	double *Revenue = data -> Revenue;
	double *Expenses = data -> Expenses;
	double *Overhead = data -> Overhead;
	double *Profit = data -> Profit;

	//do the accounting...
	double TotalProfit = 0.0;

	//create paging vars
	long pageA, pageB, pageC1, pageC2, pageC3, pageD;
	FILE* pagesOut = data->outfile;
	pageD = (long) &k/PAGESIZE; //implem code paging
	pageA = (long) &TotalProfit/PAGESIZE;
	fprintf(pagesOut," %ld \n",pageD);

	for(k=0;k<data->number_shops;k++){
		{
			//calculate page references
			pageB= (long) Profit/PAGESIZE;
			pageC1 = (long) Revenue /PAGESIZE;
			pageC2 = (long) Expenses/PAGESIZE;
			pageC3 = (long) Overhead/PAGESIZE;
			//saving page references...
			fprintf(pagesOut," %ld \n", pageD);
			fprintf(pagesOut," %ld \n", pageB);
			fprintf(pagesOut," %ld \n", pageC1);
			fprintf(pagesOut," %ld \n", pageC2);
			fprintf(pagesOut," %ld \n", pageC3);
			fprintf(pagesOut," %ld \n", pageA);
		}
		*Profit = (*Revenue++) - (*Expenses++) - (*Overhead++); //compute profit for each shop
		TotalProfit = TotalProfit + *Profit++; //compute total profit as sum of all shop profits
	}

	data->RegionProfit = TotalProfit; /*assign TotalProfit computation to RegionProfit
	(will be used to calculate total profit again as a proof in ThreadSupervisor.c)*/
	return 0;
}
