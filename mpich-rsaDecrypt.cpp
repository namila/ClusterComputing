#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <list>
//#include <iostream>

// Process 0 will act as the root process
#define rootProcess 0
using namespace std;
int totalProcesses;
int currentProcessRank;
int codeToBeCracked;
int flag;
int inputsForOneProcess;
list<int> primeNumbersList;
list<int> fullprimeNumberList;

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
		printf("Prime numbers Between 0 and %d\n",codeToBeCracked);					
	}

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

		if(flag==0)
		{
			primeNumbersList.push_back(i);
			printf("Counteed by Process %d   %d\n",currentProcessRank,i);
		}
         
  	}

	return 0;
}
