//Brendan Burke
/*ThreadSupervisor.c coordinates the activity of threads to perform all necessary operations
(reading data, computing profit for each of the k shops, and computing regional profits).*/
#include "helpfulVariables.h"

int ThreadSupervisor(int num_Objs, int num_Regs, bool Valid){
	int i;
	int j;
	int num_of_thread = 0; //start thread count at 0
	int max_num_Threads = num_Regs + 2; //1 thread per region plus expenses & revenue
	//recall that there are two groups of threads
	//the first group has to to read the data sets
	//the second group has five threads, one for each region
	int tot_Size = num_Objs*num_Regs; //total # of shops is (#shops/region)*#regions


	FILE* pagesOut;
	pagesOut = saveData("LongSkinny.txt"); //get LongSkinny ready to accept page ref

	//declare input_data type variables for revenue and expenses to be used when reading files
	sourceData revenue;
	sourceData expenses;

	currVar corporate; //currVar type variable corporate
	currVar region[num_Regs]; //data sets for regional values
	pthread_t tid[max_num_Threads]; //thread identifier for each thread (num_Regs + 2)
	pthread_attr_t attr[max_num_Threads]; //holds attributes for each of the threads

	//set the default attributes for all threads...
	for(i=0;i<max_num_Threads;i++){
		pthread_attr_init(&attr[i]);
		num_of_thread++;
	}

	//set up space for corporate...
	corporate.start_reg = 0; //start at region 0
	corporate.number_shops = tot_Size; //total number shops in all (for corp) is (#shops/region)*#regions
	//allocate (set up) space for corporate data...
	corporate.Revenue = (double *) malloc(sizeof(double)*tot_Size);
	corporate.Expenses = (double *) malloc(sizeof(double)*tot_Size);
	corporate.Overhead = (double *) malloc(sizeof(double)*tot_Size);
	corporate.Profit = (double *) malloc(sizeof(double)*tot_Size);

	revenue.num_Objs = tot_Size; //all shops have a revenue
	revenue.values = corporate.Revenue; //sufficient space for all revenue values
	revenue.srcFileName = "Revenue.txt"; //"Revenue.txt" is source file for revenue


	revenue.outfile = pagesOut;


	expenses.num_Objs = tot_Size; //all shops have expenses
	expenses.values = corporate.Expenses; //sufficient space for all expense values
	expenses.srcFileName = "Expenses.txt"; //"Expenses.txt" is source file for expenses

	expenses.outfile = pagesOut;


	//create the thread to read the revenues
	pthread_create(&tid[0],&attr[0],dataFiller,(void *) &revenue);

	//create the thread to read the expenses
	pthread_create(&tid[1],&attr[1],dataFiller,(void *) &expenses);

	//wait for the running threads (reading expense and revenue data) to end before proceeding
	for(j=0;j<2;j++){
		pthread_join(tid[j],NULL);
	}

	//allocate overhead...
	//compute overhead allocations
	double TotalRevenue = 0;

	//declare paging vars
	long pageA, pageB, pageC1, pageC2, pageD;
	pageD = (long) &i/PAGESIZE; //repr of code page
	pageA = (long) &TotalRevenue/PAGESIZE; //results page
	fprintf(pagesOut," %ld \n", pageD);
	fprintf(pagesOut," %ld \n", pageA);

	for(i=0;i<tot_Size;i++){
		TotalRevenue += corporate.Revenue[i]; //total revenue is sum of revenue of all shops
		{
			pageB = ((long) &corporate.Revenue[i])/PAGESIZE; //page for arg B
			fprintf(pagesOut," %ld \n",pageD); //for sending to the algorithm evaluator
			fprintf(pagesOut," %ld \n",pageA);
			fprintf(pagesOut," %ld \n",pageB);
		}
	}

	double Overhead = 1234567.0; //total overhead to be allocated given in project instructions
	//fractional share of overhead...
	double Ovr_Fraction = 100.0 * Overhead / TotalRevenue;
	//printf("Ovr_Fraction = %12.2f\n",Ovr_Fraction); debugging purposes

	//round overhead computations to the next higher penny for each shop...
	double num_Cents, part_Cents, num_Dollars;
	long whole_Cents;

	for(i=0;i<tot_Size;i++){
		/*(for shop_i, Overhead_i = Overhead*((Revenue_i)/TotalRevenue)
		= (Revenue_i*(Overhead/TotalRevenue)) = Revenue_i*Ovr_Fraction*/
		//then multiply by 100 to get overhead amount in cents
		num_Cents = corporate.Revenue[i] * Ovr_Fraction; //amount of overhead per shop in cents
		whole_Cents = (long) num_Cents;
		part_Cents = num_Cents - (double) whole_Cents; //obtain partial cents value (lower than penny)
		if(part_Cents>0.0) whole_Cents++; //round to the next higher penny for each shop
		num_Dollars = (double) whole_Cents / 100.0; //100 cents in a dollar
		corporate.Overhead[i]=num_Dollars; //final dollar amount of overhead for each shop
		{
			//calc and record overhead page references
			pageC1 = ((long) &corporate.Revenue[i])/PAGESIZE; //page for argument c1
			pageC2 = ((long) &corporate.Overhead[i])/PAGESIZE; //page for argument c2

			fprintf(pagesOut," %ld \n",pageD); //for sending to the algorithm eval
			fprintf(pagesOut," %ld \n",pageC1);
			fprintf(pagesOut," %ld \n",pageC2);
			fprintf(pagesOut," %ld \n",pageA);
		}
	}



	int beginning;

	for(i=0;i<num_Regs;i++){ //regions 0 to 4 (five total)
		beginning = i*num_Objs; //what shop # to begin at in each case
		region[i].start_reg = beginning; //start region at correct shop
		region[i].number_shops = num_Objs; //1000 shops per region
		//assign revenue, expenses, overhead, and profit amounts to regions from corresponding shops
		region[i].Revenue = &corporate.Revenue[beginning];
		region[i].Expenses = &corporate.Expenses[beginning];
		region[i].Overhead = &corporate.Overhead[beginning];
		region[i].Profit = &corporate.Profit[beginning];
		region[i].reg_Num = i; //region number is i, 0-4

		region[i].outfile = pagesOut;

		//create the thread
		pthread_create(&tid[2+i],&attr[2+i],accountingFunction, (void *) &region[i]);
	}
	//wait for the running threads (computing profits for five regions) to end
	for(j=2;j<max_num_Threads;j++){
		pthread_join(tid[j],NULL);
	}
	//summarize profits...
	double TotalOverhead = 0;
	double TotalProfit = 0;
	double TotalExpenses = 0;


	for(i=0;i<tot_Size;i++){
		TotalOverhead += corporate.Overhead[i]; //total overhead is sum of (rounded) overhead among all shops
		TotalProfit += corporate.Profit[i]; //total profit is sum of profits among all shops
		TotalExpenses += corporate.Expenses[i]; //total expenses is sum of expenses among all shops
	}
	//print computed values for total revenue, total expenses, total overhead, and total profit
	printf("Total Revenue = %12.2f\n",TotalRevenue);
	printf("Total Expenses = %12.2f\n",TotalExpenses);
	printf("Total Overhead = %12.2f\n",TotalOverhead);
	printf("Total Profit = %12.2f\n",TotalProfit);

	TotalProfit = 0.0; //calculate again to check (as a PROOF)
	for(i=0;i<num_Regs;i++){
		beginning = i*num_Objs; //what shop # to begin at in each case (for each region)
		region[i].start_reg = beginning; //start region at correct shop
		printf("Region %d profits = %13.2f\n",i,region[i].RegionProfit); //print profits out by region
		TotalProfit = TotalProfit + region[i].RegionProfit; //Total Profit is a sum of all regional profits
	}
	printf("\nTotal Profit for the Firm = %12.2f\n\n",TotalProfit);
	fclose(pagesOut);//close file
	return num_of_thread;
}

