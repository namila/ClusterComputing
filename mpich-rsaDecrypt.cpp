#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <list>
#include <stdlib.h>
//#include <iostream>

// Process 0 will act as the root process
#define rootProcess 0
using namespace std;
int totalProcesses;
int currentProcessRank;
int codeToBeCracked;
int flag;
int inputsForOneProcess;
int tag=100;
int numberOfElementsFiled;
list<int> primeNumbersListForAProcess;
list<int> fullprimeNumberList;
int *primeNumberArrayForAProcess;
int *primeNumbersFromAllProcesses;
int *primeValuesDistribution;
int *resultArray;
int *offSets;


MPI_Datatype variableType;
MPI_Status messageStatus;

int GetPrimesInGivenRange(int lowerBound,int upperBound);



int main(int argc,char **argv){
	

	// Initializing the MPI Environment
	MPI_Init(&argc,&argv);

	// Counting the total number of processes present
	MPI_Comm_size(MPI_COMM_WORLD,&totalProcesses);
	
	// Determining the rank of current proces
	MPI_Comm_rank(MPI_COMM_WORLD,&currentProcessRank);

	
	if(currentProcessRank==rootProcess){

		// Getting the RSA code to be cracked
		printf("Enter tha RSA Code to be Cracked\n");
		scanf("%d",&codeToBeCracked);	
		//primeNumbersFromAllProcesses=(int *)malloc(sizeof(int)*codeToBeCracked);

		printf("Prime numbers Between 0 and %d\n",codeToBeCracked);			
					
	}

	primeValuesDistribution=(int *)malloc(sizeof(int)*totalProcesses);
	resultArray=(int *)malloc(sizeof(int)*1);
	offSets=(int *)malloc(sizeof(int)*totalProcesses);
	// Synchronizing the processes before the broadcast
	MPI_Barrier(MPI_COMM_WORLD);

	// Broadcasting user inputs to other processes
	MPI_Bcast(&codeToBeCracked,1,MPI_INT,rootProcess,MPI_COMM_WORLD);

	// Synchronizing after the broadcast
	MPI_Barrier(MPI_COMM_WORLD); 

	//printf("processRank %d inputData %d\n",currentProcessRank,codeToBeCracked);

	inputsForOneProcess=codeToBeCracked/totalProcesses;
		
	// Value of The RSA code is less than the number of processors
	if(inputsForOneProcess==0){
		GetPrimesInGivenRange(0,codeToBeCracked);	
	}

	else{
		if(currentProcessRank==(totalProcesses-1)){
			GetPrimesInGivenRange(inputsForOneProcess*currentProcessRank+1,codeToBeCracked);
		}

		else{
			GetPrimesInGivenRange(inputsForOneProcess*currentProcessRank+1,inputsForOneProcess*(currentProcessRank+1));
		}
		
	}

	MPI_Barrier(MPI_COMM_WORLD);

		
	// Getting the number of primes found by the process and putting them into an array
	
	resultArray[0]=primeNumbersListForAProcess.size();
	numberOfElementsFiled=resultArray[0];
	printf("wow p:%d %d\n",currentProcessRank,numberOfElementsFiled);
	
	MPI_Gather(resultArray,1,MPI_INT,primeValuesDistribution,1,MPI_INT,rootProcess,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);

	if(currentProcessRank==rootProcess){
		primeNumbersFromAllProcesses=(int *)malloc(sizeof(int)*codeToBeCracked);
		offSets[0]=0;
		for(int i=1;i<totalProcesses;++i){
			offSets[i]=offSets[i-1]+primeValuesDistribution[i-1];
			
		}

	}

	MPI_Barrier(MPI_COMM_WORLD);
	primeNumberArrayForAProcess=(int *)malloc(sizeof(int)*numberOfElementsFiled);
	list<int>::iterator primeNumberIterator = primeNumbersListForAProcess.begin();

	for(int i=0;i<numberOfElementsFiled;++i){
		primeNumberArrayForAProcess[i]=	*primeNumberIterator;
		//printf("Validator %d\n",primeNumberArrayForAProcess[i]);
		++primeNumberIterator;
	}

	MPI_Barrier(MPI_COMM_WORLD);

	 
	MPI_Gatherv(primeNumberArrayForAProcess,primeValuesDistribution[currentProcessRank],MPI_INT,primeNumbersFromAllProcesses,primeValuesDistribution,offSets,MPI_INT,rootProcess,MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	

	if(currentProcessRank==rootProcess){
		for(int i=0;i<codeToBeCracked;++i){
			printf("Final %d : %d\n",i,primeNumbersFromAllProcesses[i]);
		}
		
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	return 0;
}


//Generating the prime Numbers in the given Range.

int GetPrimesInGivenRange(int lowerBound,int upperBound)
{

	for(int i=lowerBound; i<=upperBound; ++i)
	{

		flag=0;

		for(int j=2; j<=i/2; ++j)
		{
         		if(i%j==0)
         		{
            			flag=1;
            			break;
         		}
      		}

		if(flag==0 & (i!=1)& (i!=2))
		{
			primeNumbersListForAProcess.push_back(i);
			printf("Counteed by Process %d   %d\n",currentProcessRank,i);
		}
         
  	}
	
	return 0;
}
