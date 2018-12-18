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
  //cycles through line by line adding to the global matrix
  for (int row =0; row < matrixWidth; row++){
      vector<int> singleRow;
      // creates multidimensional matrix, push another vector into the matrix for each row
      matrix.push_back(singleRow);  
      for(int column = 0; column < matrixWidth; column++){ 
        // for each column read from the input file a number
        inputFile >> num;
        // push numbers onto the row vector 
        matrix[row].push_back(num);  
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
               a nxn matrix that with all its elements holds the highest
               sum of numbers.
    matrixWidth: pass matrix width
    return: void
    Funciton displays the submatrix as the solution to the problem. 
*/
void displaySubMatrix(vector<vector <int> > subMatrix, int rowStart, int colStart, int matrixWidth){
  int endCol = colStart+matrixWidth;
  int endRow = rowStart+matrixWidth;
  displayMatrix(subMatrix, 4);
  for (int row = rowStart; row < endRow; row++){
    for(int col = colStart; col < endCol; col++){
      cout << subMatrix[row][col] <<  ' ';
    }
    cout << endl;
  }
}

/*
  computeSum
    array[]: pass in array that holds the elements of the submatrix waiting to be summed
    num_elements: number of elements that are in the array

    return: int
*/
int computeSum(int array[], int num_elements) {
  int sum = 0;
  // FOR - sums up the elements of the array, the submatrix of the problem
  for (int index = 0; index < num_elements; index++) {
    sum += array[index];
  }
  return sum;
}

/*
  getSubMatrix
    matrix: multidimensional matrix the problem is working on
    startRow: the row where the submatrix is received.
    startCol: the column where the submatrix is received.
    subMatrixSize: the size of the submatrix  

    return: vector submatrix
*/
vector <int>getSubMatrix(vector<vector <int> > &matrix, int startRow,int startCol ,int subMatrixSize){
  vector <int> subMatrix;
  int endCol = startCol+subMatrixSize;
  int endRow = startRow+subMatrixSize;
  
  // FOR - each row and column create the sub matrix
  for (int row = startRow; row < endRow; row++){
    for(int col = startCol; col < endCol; col++){
      subMatrix.push_back(matrix[row][col]);
    }
  }
  return subMatrix;
}

/*
  find_sum_submatrix
    subMatrix: matrix that is the solution to the problem. Represents
               a nxn matrix that with all its elements holds the highest
               sum of numbers.
    matrixWidth: pass matrix width
    return: int
    Funciton sums all the values of the submatrix
*/
int find_sum_submatrix(vector<int> subMatrix, int subMatrixSize){
  int sum = 0;
  for(int index = 0; index < subMatrixSize; index++){
    sum += subMatrix[index];
  }
  return sum;
}

int main(int argc, char** argv) {
  int         world_rank;
  int         world_size;
  ifstream    inputFile;                 // input stream for file of nxm matrix for the problem
  string      line;
  int         matrixWidth;               // width of the matrix
  int         sizeOfSubMatrix;           // size of the sub matrix
  int         minimumProcessAllowed = 0; // there must be a floor that num of precessors cannot pass
  vector<vector <int> > matrix;          // the matrix to be worked on
  vector<int> subMatrix;                 // subMatrix that needs to be the solution 
  int*        subDetails = NULL;         // integer pointer
  int*        allSubDetails = NULL;      
  int sum     = 0;                       // sum that represents the sum of the submatrix
  
  sizeOfSubMatrix = 2;            

  MPI_Init(NULL, NULL); // initiates the communicator
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // reports the rank, identifying the calling process
  MPI_Comm_size(MPI_COMM_WORLD, &world_size); // reports the number of processes
  
  

  int currentDestProcess = 0;

  //get the width of the matrix and sets restrict on the processes
  if (world_rank == 0) { 
    inputFile.open("./data2.txt");      
    //gets the size of the matrix
    getline(inputFile, line);
    sscanf(line.c_str(), "%d", &matrixWidth);
    //sets the minimum amount of processes allowed based on size of matrix
    minimumProcessAllowed = ((matrixWidth-1)*(matrixWidth-1));
  }

  // error checking for process input 
  if(world_size < minimumProcessAllowed+1 ) {
    cout << "Incorrect Process amount entered";
    cout << "The minimum number of process required is: " + ((matrixWidth-1)*(matrixWidth-1));
    exit(1);
  }

  
  if (world_rank == 0) {
    // create and display the matrix
    create_matrix(matrix,matrixWidth, inputFile);
    cout << endl <<"The matrix read in is: " << endl;
    displayMatrix(matrix,matrixWidth);
    cout << endl;
    
    // cycles through the matrix getting and sending the submatrixes out  
    for(int row = 0; row <= (matrixWidth-sizeOfSubMatrix); row++){
      for(int col = 0; col <= (matrixWidth-sizeOfSubMatrix); col++ ){
        // gets the sub matrix 
        subMatrix = getSubMatrix(matrix,row,col,sizeOfSubMatrix);
        
        // gets the process to send to
        ++currentDestProcess;
        
        // sends the sub matrix
        MPI_Send(&subMatrix[0], subMatrix.size(), MPI_INT,currentDestProcess,0, MPI_COMM_WORLD); // send the submatrix to the other processes          
        
        //sends an array to process to place submatrix score, row, col
        subDetails = new int[3];
        subDetails[0] = row;
        subDetails[1] = col;
        MPI_Send(&subDetails[0], subMatrix.size(), MPI_INT,currentDestProcess,1, MPI_COMM_WORLD); // send the submatrix to the other processes          
      }
    }
    subDetails[0] = -1;
    subDetails[1] = -1;
    subDetails[2] = -1;
  } 
  else{ 
    // allocates room for recieving submatrix
    subMatrix.resize(4);
    // recieves the submatrix
    MPI_Recv(&subMatrix[0], 4, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    // allocates space for sub matrix details
    subDetails = (int*)malloc(3);
    // recieves the row and col for the sub matrix
    MPI_Recv(&subDetails[0], 4, MPI_INT, 0, 1, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    // gets the sum matrix
    sum = find_sum_submatrix(subMatrix, 4);
    // places it into the sub details
    subDetails[2] = sum;
  }
  //cout << world_rank << ": " << subDetails[2] <<  endl;
  if(world_rank == 0){
    allSubDetails = new int[world_size];
  }
//MPI_Gather(&subDetails[0], 3, MPI_INT,allSubDetails,3,MPI_INT,0,MPI_COMM_WORLD);
MPI_Gather(subDetails, 3, MPI_INT, allSubDetails, 3 , MPI_INT, 0, MPI_COMM_WORLD);
MPI_Barrier(MPI_COMM_WORLD); 

// IF - only when the world size is zero 
if(world_rank == 0){
  int row, col;
  sum = 0;
  for(int index = 0; index < (world_size*3); index++){
    if((index+1)%3==0){
      // Save all the submatrix details 
      if ( sum < allSubDetails[index] ){
        sum = allSubDetails[index];   // every third position is the sum and saved into sum variable
        row = allSubDetails[index-2]; // every first postion is the row number
        col = allSubDetails[index-1]; // every second number is the column number s
      }
    }
  }

  cout << "The max is: " << sum << endl;
  cout << "The submatrix: " << endl;
  for(int rw = row; rw < row+2; rw++){
    for(int cl = col; cl < col+2; cl++){
       cout << matrix[rw][cl] << ' ';
    }
    cout << endl;
  }
  delete allSubDetails; // delete pointer
}

  delete subDetails; // delete pointer
  MPI_Finalize(); //stop participating in any communicator
}