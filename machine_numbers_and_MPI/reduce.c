#include <stdio.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
  MPI_Init(NULL, NULL);
 
  float delta = 0.000000059604645;
  int mpi_rank, mpi_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
 
  printf("rank %d/%d running.\n", mpi_rank, mpi_size);

  // place the larger value at each rank, then reduce
  for (int i=0; i<mpi_size; i++)
  {
    float global_sum, local_val;
    if (mpi_rank == i) local_val = 1.0f;
    else local_val = delta;
	  MPI_Reduce(&local_val, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
 
  	// Print the result
    if (mpi_rank == 0) {
      printf("big val to rank %d, gives global sum = %1.10f\n", i, global_sum);
    }
  }
 
  MPI_Finalize( );
}
 
