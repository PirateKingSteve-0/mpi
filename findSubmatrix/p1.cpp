#include <stdio.h>
#include <iostream>
#include <fstream>
// Given a very large (n>10) matrix of n x n elements, write a distributed program in MPI that outputs a submatrix 
// of size 2x2 with the largest sum of its elements and its relative position or displacement (row-column of the top left element) 
// in the original matrix. There will be only one process with rank 0, that will read the file name with the input data, read from 
// the file the value of n, read from the file the entire matrix, and will output the submatrix of size 2x2 with the largest sum of its elements and its position on the screen.
// All the other processes will receive portions of the matrix and contribute to identifying the submatrix.




/* Need to include this to be able to hook into the MPI API */
#include "mpi.h"
#include <string>
#include <vector>
using namespace std;

void displayMatrix(int** matrix, int matrixWidth);
int compute_sum(int** matrix, int num_elements);

int main(int argc, char *argv[]) {
   string line;
   char numberStr;
   int  num; 
   int  matrixWidth;
   int** matrix;
   ifstream inputFile;
   
   
   int rank, size;

   
   /* Initializes MPI */
   MPI_Init(&argc, &argv);
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &size );

   if (rank == 0){
      inputFile.open("./data.txt");
      
      //gets the size of the matrix
      getline(inputFile, line);
      sscanf(line.c_str(), "%d", &matrixWidth);
      cout << "size of the array: " << matrixWidth << endl;

      //inputs to matrix
      matrix = new int*[matrixWidth];
      for (int row =0; row < matrixWidth; row++){
         matrix[row] = new int[matrixWidth];
         for(int column = 0; column < matrixWidth; column++){
            inputFile >> num;
            matrix[row][column] = num;
         }
      }
      int **sub_matrix = (int **)malloc(sizeof(int)*2);
      assert(sub_rand_nums != NULL);


      for (int row = 0; row < matrixWidth; row+=2){
         for(int column = 0; column < matrixWidth; column+=2){
            MPI_Send(row, 1, MPI_INT, dest, source, MPI_COMM_WORLD);
         }
      }

      // display matrix
      displayMatrix(matrix,matrixWidth);
   }

   printf("Process %d out of %d\n", rank, size);
   /* Need this to shutdown MPI */

   else{
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   }   
   MPI_Finalize();
}

int compute_sum(int** matrix, int num_elements){
   int sum = 0;
   for(int row = 0; row < num_elements; row++){
      for(int column = 0; column < num_elements; column++){
         sum += matrix[row][column];
      }
   }
   return sum;
}
void displayMatrix(int** matrix, int matrixWidth){
      for (int row =0; row < matrixWidth; row++){
         for(int column = 0; column < matrixWidth; column++){
            cout << matrix[row][column] << " ";
         }
         cout << endl;
      }
}