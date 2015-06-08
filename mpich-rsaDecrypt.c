#include <mpi.h>
#include <stdio.h>

int totalProcesses;
int currentProcessRank;
int main(int argc,char **argv){
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&totalProcesses);
	MPI_Comm_rank(MPI_COMM_WORLD,&currentProcessRank);
	printf("Total Processes %d Current Rank %d\n",totalProcesses,currentProcessRank);
	return 0;
}
