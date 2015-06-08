#include <mpi.h>
#include <stdio.h>

// Process 0 will act as the root process
#define rootProcess 0

int totalProcesses;
int currentProcessRank;
int codeToBeCracked;


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
		
		// 
		
	}



	//printf("Total Processes %d Current Rank %d\n",totalProcesses,currentProcessRank);
	return 0;
}
