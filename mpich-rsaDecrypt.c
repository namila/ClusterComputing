#include <mpi.h>
#include <stdio.h>

int totalProcesses;
int currentProcessRank;
int main(int argc,char **argv){
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD);
	return 0;
}
