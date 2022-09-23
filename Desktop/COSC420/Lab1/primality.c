/* Kalyn Howes
    Lab 1
    9.10.21
    primality.c - preform a primality test of a given number 
*/
#include <stdio.h>
#include <mpi.h>
#include <stdbool.h> // for bools
#include <math.h> // for sqrt
#include <stdlib.h> 
#include <string.h>

int main(int argc, char** argv) {

  MPI_Init(&argc,  &argv); // need everytime!

  // printf("Testing!\n");
  // for (int i = 0; i < argc; i++){
  //   printf("argv[%d] = %s\n", i, argv[i]);
  // }

  MPI_Comm world = MPI_COMM_WORLD; // the group of processes

  int worldSize, myRank, nameLen;
  char name[MPI_MAX_PROCESSOR_NAME];

  // passing the container for the result in second param
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);
  MPI_Get_processor_name(name, &nameLen);

  unsigned long long N = strtoull (argv[1], NULL, 10);
  //int N = atoi(argv[1]);
  double s = sqrt((double)N);
  bool isPrime = true;

  // print only once!
  MPI_Barrier(world);
  if (myRank == 0)
    printf("\nN = %llu\nsqrt(N) = %f\n\n", N, s);

  for (int i = 2; i < s;) {
    printf("Using rank rank %d out of %d (i = %d to start)\n", myRank, worldSize, i);

    // set prime bool to false
    if (N % 2 == 0) {
      isPrime = false;
    }
  
    i += worldSize; // increment by world size (# of processes running)
    printf("Now, i = %d\n", i);
  }

  // print only once!
  MPI_Barrier(world);
  if (myRank == 0){

    if (isPrime) {
      printf("\n%llu is prime\n", N);

    // if not prime, find a factor
    } else {
      printf("\n%llu is NOT prime\n", N);

      // find factor - divide by 2!
      int factor = N / 2;
      printf("Possible factor for N: 2 x %d\n\n", factor);

    }
  }

  MPI_Finalize(); // need everytime!
  return 0;
}