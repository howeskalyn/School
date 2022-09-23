/* Kalyn Howes
    Lab 1
    9.10.21
    hello.c 
*/

#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
  MPI_Init(&argc,  &argv); // initialize the MPI execution environment

  // MPI_Comm - represents the group of processes
  // constant on the right gets assigned in the mpi.h compilation
  MPI_Comm world = MPI_COMM_WORLD;

  int worldSize;
  int myRank;

  // passing the container for the result in second param
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);
  printf("Hello, from rank %d out of %d\n", myRank, worldSize);

  // gets name of processor, gives result length
  // char *name - must be an array of size at least MPI_MAX_PROCESSOR_NAME.
  char name[MPI_MAX_PROCESSOR_NAME];
  int namelen;
  MPI_Get_processor_name(name, &namelen);
  printf("Hello, from processor %s\n", name);

  MPI_Finalize(); // Terminates MPI execution environment
  return 0;
}