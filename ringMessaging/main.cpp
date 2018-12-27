#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <iostream>
#include <assert.h>
using namespace std;

int main(int argc, char** argv){
   int world_rank;
   int world_size;
   int nextProc;
   int tmp;
   
   MPI_Init(NULL, NULL); // initiates the communicator
   MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // reports the rank, identifying the calling process
   MPI_Comm_size(MPI_COMM_WORLD, &world_size); // reports the number of processes
   //tmp =  malloc(sizeof(int));
   
   if(world_rank == world_size-1){
      nextProc = 0;
   }
   else{
      nextProc = world_rank+1;
   }
   
   if(world_rank == 0){
      tmp = 1;
      cout << "Sending first message now..." << endl;
      MPI_Send(&tmp, 1, MPI_INT,nextProc,0, MPI_COMM_WORLD);
   }
   else{      
      MPI_Recv(&tmp, 1, MPI_INT, world_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Send(&tmp, 1, MPI_INT,nextProc,0, MPI_COMM_WORLD);
   }
   
   if(world_rank == 0){
      MPI_Recv(&tmp, 1, MPI_INT, world_size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      cout<< "Finally ";
   }

   cout << "rank " << world_rank << " says " << tmp << endl;
   MPI_Barrier(MPI_COMM_WORLD);
   MPI_Finalize(); 
}