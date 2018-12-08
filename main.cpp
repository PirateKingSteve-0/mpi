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

void displaySubMatrix(vector<int> subMatrix, int matrixWidth){
  int matrixSize= matrixWidth+matrixWidth;
  cout << "Submatrix: " << endl;
  for(int number = 0; number < matrixSize; number++){
    if(number+number == matrixSize){
        cout<<endl;
    }
    cout << subMatrix[number] << " ";
  }
}

// Computes the average of an array of numbers
int computeSum(int array[], int num_elements) {
  int sum = 0;
  cout << "num_elements: " << num_elements << endl;
  cout << "numbers in array: ";
  for (int index = 0; index < num_elements; index++) {
    sum += array[index];
  }
  cout<< endl; 
  cout << "sum: " << sum << endl;
  return sum ;
}

vector <int>getSubMatrix(vector<vector <int> > &matrix, int startRow,int startCol ,int subMatrixSize){
  vector <int> subMatrix;
  int endCol = startCol+subMatrixSize;
  int endRow = startRow+subMatrixSize;
  
  for (int row = startRow; row < endRow; row++){
    for(int col = startCol; col < endCol; col++){
      subMatrix.push_back(matrix[row][col]);
    }
    cout << endl;
  }
  //displaySubMatrix(subMatrix, subMatrixSize);
  return subMatrix;
}



int main(int argc, char** argv) {
  bool readyToSend;
  ifstream inputFile;
  int matrixWidth;
  int world_rank;
  int world_size;
  int currentDestProcess = 1;
  vector<int> subMatrix;
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
    for(int row = 0; row < matrixWidth; row += sizeOfSubMatrix){
      for(int col = 0; col < matrixWidth; col += sizeOfSubMatrix){
        subMatrix = getSubMatrix(matrix,row,col,sizeOfSubMatrix);
        displaySubMatrix(subMatrix, sizeOfSubMatrix);
        if(currentDestProcess == world_size){
          currentDestProcess = 1;
        }
        MPI_Send(&subMatrix, (sizeOfSubMatrix+sizeOfSubMatrix), MPI_INT,currentDestProcess++,0, MPI_COMM_WORLD);
      }
      cout << endl;
    }
  }
  else{ 

    MPI_Recv(&subMatrix, sizeOfSubMatrix, MPI_INT, 0, 0, MPI_COMM_WORLD,0);
    displaySubMatrix(subMatrix,sizeOfSubMatrix );
  }

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}