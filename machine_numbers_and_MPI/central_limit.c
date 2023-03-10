#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
  MPI_Init(NULL, NULL);

  int elements_per_proc = 8;
  int initial_seed = 123456;

  int mpi_rank, mpi_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

  if (!mpi_rank) printf("running %d elements per task with %d tasks.\n", elements_per_proc, mpi_size);

  // create seeds
  int scatter_seeds[mpi_size];
  scatter_seeds[0] = initial_seed;
  if (!mpi_rank) for (int i=1; i<mpi_size; i++) scatter_seeds[i] = scatter_seeds[0] + i;

  // scatter the seeds
  int seed;
  MPI_Scatter(scatter_seeds, 1, MPI_INT, &seed, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // seed the RNG
  srand(seed);

  float sum = 0;
  for (int i=0; i<elements_per_proc; i++)
  {
    float sample = (float)rand() / (float)RAND_MAX;
    sum += sample;
  }
  sum /= elements_per_proc;

  // gather and bin the results:
  float results[mpi_size];
  MPI_Gather(&sum, 1, MPI_FLOAT, results, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

  int bins[10];
  for (int i=0; i<10; i++) bins[i] = 0;

  if (!mpi_rank) for (int i=0; i<mpi_size; i++)
  {
    printf("binning %f\n", results[i]);
    bins[(int)(results[i]*10)]++;
  }

  if (!mpi_rank) for (int i=0; i<10; i++) 
  {
    for (int j=0; j<bins[i]; j++) printf("X");
    printf("\n");
  }

  MPI_Finalize();
 
}
