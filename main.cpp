#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <mpi.h>
#include <iostream>
#include <assert.h>
#include <fstream>
using namespace std;

/*
  create_matrix
    matrix: multidimensional matrix the problem is working on
    matrixWidth: the width of the matrix
    inputFile: file that contains the matrix values to read in

    return: void
*/
void create_matrix(vector<vector<int> > &matrix,int matrixWidth,ifstream &inputFile) {
  int num;

  for (int row =0; row < matrixWidth; row++){
      vector<int> singleRow;
      matrix.push_back(singleRow);  // creates multidimensional matrix, push another vector into the matrix for each row
      for(int column = 0; column < matrixWidth; column++){ // for each column read from the input file a number
        inputFile >> num;
        matrix[row].push_back(num);  // push numbers onto the row vector 
      }
  }
}

/*
  displayMatrix
    matrix: multi dimensional matrix passed in to be printed or displayed
    matrixWidth: pass matrix width

    return: void

    Function displays the matrix of the problem of size matrixWidth.
*/
void displayMatrix(vector<vector<int> > matrix, int matrixWidth){
  for(int row = 0; row < matrixWidth; row++){
    for(int col = 0; col < matrixWidth; col++){
      cout << matrix[row][col] << " "; // displays space between elements
    }
    cout << endl;
  }
} 


/*
  displaySubMatrix
    subMatrix: matrix that is the solution to the problem. Represents
               a 2x2 matrix that with all its elements holds the highest
               sum of numbers.
    matrixWidth: pass matrix width

    return: void

    Funciton displays the submatrix as the solution to the problem. 
*/
void displaySubMatrix(vector<vector <int> > subMatrix, int rowStart, int colStart, int matrixWidth){
  int endCol = colStart+matrixWidth;
  int endRow = rowStart+matrixWidth;
  
  for (int row = rowStart; row < endRow; row++){
    for(int col = colStart; col < endCol; col++){
      cout << subMatrix[row][col] <<  ' ';
    }
    cout << endl;
  }
}

// Computes the average of an array of numbers
int computeSum(int array[], int num_elements) {
  int sum = 0;
  for (int index = 0; index < num_elements; index++) {
    sum += array[index];
  }
  return sum ;
}


/*
  getSubMatrix
    matrix: multidimensional matrix the problem is working on
    startRow: the row where the submatrix is received.
    startCol: the column where the submatrix is received.
    subMatrixSize: the size of the submatrix  
*/
vector <int>getSubMatrix(vector<vector <int> > &matrix, int startRow,int startCol ,int subMatrixSize){
  vector <int> subMatrix;
  int endCol = startCol+subMatrixSize;
  int endRow = startRow+subMatrixSize;
  
  for (int row = startRow; row < endRow; row++){
    for(int col = startCol; col < endCol; col++){
      subMatrix.push_back(matrix[row][col]);
    }
  }
  return subMatrix;
}

int find_sum_submatrix(vector<int> subMatrix, int subMatrixSize){
  int sum = 0;
  for(int index = 0; index < subMatrixSize; index++){
    sum += subMatrix[index];
  }
  return sum;
}

int main(int argc, char** argv) {
  bool finished = false;
  ifstream inputFile;
  int matrixWidth;
  int world_rank;
  int world_size;
  int sum =0;
  int temp = 0;
  int sizeOfSubMatrix;
  vector<int> subMatrix;
  string line;

  if (argc != 2){
    cout << "error" << endl;
    fprintf(stderr, "Usage: avg num_elements_per_proc\n");
    exit(1);
  }
  
  
  sizeOfSubMatrix = atoi(argv[1]);

  MPI_Init(NULL, NULL); // initiates the communicator
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // reports the rank, identifying the calling process
  MPI_Comm_size(MPI_COMM_WORLD, &world_size); // reports the number of processes
  
  // Create a random array of elements on the root process. Its total
  // size will be the number of elements per process times the number
  // of processes
  vector<vector <int> > matrix;
  if (world_rank == 0) { // if the root process
    int maxRow;
    int maxCol;
    int currentDestProcess = 0;
    MPI_Request request;

    inputFile.open("./data.txt");      
    //gets the size of the matrix
    getline(inputFile, line);
    sscanf(line.c_str(), "%d", &matrixWidth);
    if (matrixWidth < sizeOfSubMatrix || sizeOfSubMatrix <= 0){
      cout << "\nIncorrect matrix size.\n";
      cout << "Please smaller submatrix of size: " << matrixWidth << " to 1.\n" << endl;
      exit(1);
    }
    create_matrix(matrix,matrixWidth, inputFile);
    cout << endl <<"The matrix read in is: " << endl;
    displayMatrix(matrix,matrixWidth);
    cout << endl;

    for(int row = 0; row <= matrixWidth-sizeOfSubMatrix; row++){
      for(int col = 0; col <= matrixWidth-sizeOfSubMatrix; col++ ){
        subMatrix = getSubMatrix(matrix,row,col,sizeOfSubMatrix);
        ++currentDestProcess;
        if(currentDestProcess == world_size){
          currentDestProcess = 1;
        }
        if(world_size > 1){
          MPI_Send(&subMatrix[0], subMatrix.size(), MPI_INT,currentDestProcess,0, MPI_COMM_WORLD); // send the submatrix to the other processes          
          MPI_Send(&finished, 1, MPI_C_BOOL,currentDestProcess, 1, MPI_COMM_WORLD);
          MPI_Irecv(&temp , 1, MPI_INT, currentDestProcess, 2, MPI_COMM_WORLD,&request);
      }
        else{
          temp = find_sum_submatrix(subMatrix, subMatrix.size());
        }
        if (temp > sum){
          sum = temp;
          maxRow = row;
          maxCol = col;
        }
      }
    } // end of for loop
    finished = true;
    for(int process = 1; process < world_size; process++){
      MPI_Send(&finished, 1, MPI_C_BOOL,process, 1, MPI_COMM_WORLD);
    }

    cout << "The max sum of a submatrix of size: " << sizeOfSubMatrix << 'x' << sizeOfSubMatrix << " has a value of: " << sum << endl;
    cout << "It starts at row " << maxRow+1 << " and column " << maxCol+1 << endl << endl;
    cout << "The submatrix reads: " << endl;
    displaySubMatrix( matrix, maxRow, maxCol, sizeOfSubMatrix);
    cout << endl;
  } 
  else{ 
    MPI_Status status;
    int subMatrixWidth;
    while(!finished){
      MPI_Recv(&finished, 1, MPI_C_BOOL, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      if (!finished){
        MPI_Probe(0,0,MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &subMatrixWidth);
        subMatrix.resize(subMatrixWidth*subMatrixWidth);
        MPI_Recv(&subMatrix[0], subMatrix.size(), MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        temp = find_sum_submatrix(subMatrix, subMatrix.size());
        MPI_Send(&temp, 1, MPI_INT,0,2, MPI_COMM_WORLD);
      }
    }
  }

  MPI_Barrier(MPI_COMM_WORLD); 
  MPI_Finalize(); //stop participating in any communicator
}