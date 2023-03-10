#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
  MPI_Init(NULL, NULL);

  int elements_per_proc = 8;
  int initial_seed = 123456;

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  if (!world_rank) printf("running %d elements per task with %d tasks.\n", elements_per_proc, world_size);

  // create seeds
  int scatter_seeds[world_size];
  // scatter_seeds[0] = rand();
  scatter_seeds[0] = initial_seed;
  if (world_rank == 0) 
  {
    for (int i=1; i<world_size; i++) scatter_seeds[i] = scatter_seeds[0] + i;
  }

//  int seeds[world_size];
  int seed;
   
  MPI_Scatter(scatter_seeds, 1, MPI_INT, &seed, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // seed the RNG
  srand(seed);

  float sum = 0;
  for (int i=0; i<elements_per_proc; i++)
  {
//:x    printf("rand() --> %d\n", rand());
    float sample = (float)rand() / (float)RAND_MAX;
    sum += sample;
  }
  sum /= elements_per_proc;
  // MPI_Barrier(MPI_COMM_WORLD);
  // Compute the average of your subset
//  float sub_avg = compute_avg(sub_rand_nums, elements_per_proc);
  // Gather all partial averages down to the root process

//  MPI_Gather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
  //
  // Compute the total average of all numbers.
//  if (world_rank == 0) { float avg = compute_avg(sub_avgs, world_size); } 

 
  // generate a set of seed vals
  // Create a buffer that will hold a subset of the random numbers
//  float *sub_rand_nums = malloc(sizeof(float) * elements_per_proc);
  // Scatter the random numbers to all processes
 
//  printf("process %d got seed value %d\n", world_rank, seeds[world_rank]);
//  printf("process %d got seed value %d and final sum %f\n", world_rank, seed, sum);

  // gather and bin the results:
  float results[world_size];
  MPI_Gather(&sum, 1, MPI_FLOAT, results, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

  int bins[10];
  for (int i=0; i<10; i++) bins[i] = 0;

  if (!world_rank) for (int i=0; i<world_size; i++)
  {
    printf("binning %f\n", results[i]);
    bins[(int)(results[i]*10)]++;
  }

  if (!world_rank) for (int i=0; i<10; i++) 
  {
    for (int j=0; j<bins[i]; j++) printf("X");
    printf("\n");
  }

  MPI_Finalize();
 
}
