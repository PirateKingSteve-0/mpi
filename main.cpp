#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <mpi.h>
#include <iostream>
#include <assert.h>
#include <fstream>
using namespace std;
// Creates an array of random numbers. Each number has a value from 0 - 1
void create_matrix(vector<vector<int> > &matrix,int matrixWidth,ifstream &inputFile) {
  int num;

  for (int row =0; row < matrixWidth; row++){
      vector<int> singleRow;
      matrix.push_back(singleRow);
      for(int column = 0; column < matrixWidth; column++){
        inputFile >> num;
        matrix[row].push_back(num);
      }
  }
}

void displayMatrix(vector<vector<int> > matrix, int matrixWidth){
  for(int row = 0; row < matrixWidth; row++){
    for(int col = 0; col < matrixWidth; col++){
      cout << matrix[row][col] << " ";
    }
    cout << endl;
  }
} 

// void displaySubMatrix(int *subMatrix, int matrixWidth){
//   int matrixSize= matrixWidth+matrixWidth;
//   cout << endl << "Submatrix: " << endl;
//   for(int number = 0; number < matrixSize; number++){
//     if(number+number == matrixSize){
//         cout<<endl;
//     }
//     cout << subMatrix[number] << " ";
//   }
//   cout << endl;
// }

// // Computes the average of an array of numbers
// int computeSum(int* array, int num_elements) {
//   int sum = 0;
//   cout << "num_elements: " << num_elements << endl;
//   cout << "numbers in array: ";
//   for (int index = 0; index < num_elements; index++) {
//     sum += array[index];
//   }
//   cout<< endl; 
//   cout << "sum: " << sum << endl;
//   return sum ;
// }

// void getSubMatrix(int **matrix, int startRow,int startCol ,int subMatrixSize){
//   vector<int> subMatrix(subMatrrixSize);
//   int  index;
//   index = 0;
//   cout << "startRow: " << startRow << " startCol: "<< startCol <<endl;
//   for (int row = startRow; row < subMatrixSize; row++){
//     cout<< "numbers being inserted: ";
//     for(int col = startCol; col < subMatrixSize; col++){
//       cout << matrix[row][col] << ' ';
//       subMatrix[index] = matrix[row][col];
//       index++;
//     }
//     cout << endl;
//   }

//   displaySubMatrix(subMatrix, subMatrixSize);
// }

int main(int argc, char** argv) {
  ifstream inputFile;
  int matrixWidth;
  int world_rank;
  int world_size;
  string line;

  if (argc != 2){
    cout << "error" << endl;
    fprintf(stderr, "Usage: avg num_elements_per_proc\n");
    exit(1);
  }

  int sizeOfSubMatrix = atoi(argv[1]);
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  
  // Create a random array of elements on the root process. Its total
  // size will be the number of elements per process times the number
  // of processes
  vector<vector <int> > matrix;
  if (world_rank == 0) {
    inputFile.open("./data.txt");      
    //gets the size of the matrix
    getline(inputFile, line);
    sscanf(line.c_str(), "%d", &matrixWidth);
    create_matrix(matrix,matrixWidth, inputFile);
    displayMatrix(matrix,matrixWidth);

    cout << endl;
    cout << "Sub Matrix list: "<< endl; 
    // for(int row = 0; row < matrixWidth; row += sizeOfSubMatrix){
    //   for(int col = 0; col < matrixWidth; col += sizeOfSubMatrix){
    //     getSubMatrix(matrix,row,col,sizeOfSubMatrix);
    //     cout << endl << endl;
    //   }
    //   displayMatrix(matrix, matrixWidth);
    //   cout << endl;
    // }
  }
  else{ 
    
  }
 
  // // For each process, create a buffer that will hold a subset of the entire
  // // array
  // int **sub_rand_nums = (int **)malloc(sizeof(int) * num_elements_per_proc);
  // assert(sub_rand_nums != NULL);
  
  // // Scatter the random numbers from the root process to all processes in
  // // the MPI world
  // MPI_Scatter(rand_nums, num_elements_per_proc, MPI_INT, sub_rand_nums,
  //             num_elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);
  // // Compute the average of your subset
  // int sub_avg = compute_avg(sub_rand_nums, num_elements_per_proc);

  // // Gather all partial averages down to the root process
  // int **sub_avgs = NULL;
  // if (world_rank == 0) {
  //   sub_avgs = (int **)malloc(sizeof(int) * world_size);
  //   assert(sub_avgs != NULL);
  // }
  // MPI_Gather(&sub_avg, 1, MPI_INT, sub_avgs, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // // Now that we have all of the partial averages on the root, compute the
  // // total average of all numbers. Since we are assuming each process computed
  // // an average across an equal amount of elements, this computation will
  // // produce the correct answer.
  // if (world_rank == 0) {
  //   int sum = 0;
  //   if( sum < sub_avg){
  //     sum = sub_avg;
  //   }

  //   printf("max sum of all elements is %d\n", sum);
  //   // Compute the average across the original data for comparison
  //   int original_data_avg =
  //     compute_avg(rand_nums, num_elements_per_proc * world_size);
  //   printf("Max Sum computed across original data is %d\n", original_data_avg);
  // }

  // // Clean up
  // if (world_rank == 0) {
  //   free(rand_nums);
  //   free(sub_avgs);
  // }
  // free(sub_rand_nums);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}