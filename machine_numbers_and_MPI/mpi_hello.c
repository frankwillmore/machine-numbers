#include <stdio.h>
#include <mpi.h>
 
 
int main(int argc, char* argv[])
{
  MPI_Init(NULL, NULL);
 
  int mpi_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
  int mpi_size;
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
 
  printf("rank %d/%d running.\n", mpi_rank, mpi_size);
 
  MPI_Finalize( );
}
 
