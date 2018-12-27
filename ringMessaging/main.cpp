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
   int prevProc;
   int tmp;
   
   MPI_Init(NULL, NULL); // initiates the communicator
   MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // reports the rank, identifying the calling process
   MPI_Comm_size(MPI_COMM_WORLD, &world_size); // reports the number of processes
   
   // establishes the next process that it will send a msg to.
   if(world_rank == world_size-1){
      nextProc = 0;
   }
   else{
      nextProc = world_rank+1;
   }

   // establishing the process it is recieving a msg from 
   prevProc = world_rank-1;

   // process 0 sends a message
   if(world_rank == 0){
      tmp = 1;
      cout << "Sending first message now..." << endl;
      // sends a message to next process
      MPI_Send(&tmp, 1, MPI_INT,nextProc,0, MPI_COMM_WORLD);

      // establishing the process it is recieving a msg from for process 0 
      prevProc = world_size-1;
      
      // recieves another rank
      MPI_Recv(&tmp, 1, MPI_INT, prevProc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      cout<< "Finally ";
   }
   else{      
      // recieves the message from the lower rank then sends to next process
      MPI_Recv(&tmp, 1, MPI_INT, prevProc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      tmp++;
      MPI_Send(&tmp, 1, MPI_INT,nextProc,0, MPI_COMM_WORLD);
   }
   // outputs result
   cout << "rank " << world_rank << " says " << tmp << endl;
   MPI_Barrier(MPI_COMM_WORLD);
   MPI_Finalize(); 
}