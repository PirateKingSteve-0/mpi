# MPI

## Repo Summary
This repo is for learning purposes only. It is meant to better understand MPI, message passing, and parallelization. 

## TO RUN: 
Initiate docker instance: ```docker run --rm -it -v $(pwd):/project nlknguyen/alpine-mpich``` <br>
To build: ```mpic++ main.cpp -o main``` <br>
To run: ```mpiexec -np 2 ./main 3``` <br> (mpiexec -np <# of process> ./main < size of submatrix>) <br>


### Topic
Given a very large (n>10) matrix of n x n elements, write a distributed program in MPI that outputs a submatrix of size nxn with the largest sum of its elements and its relative position or displacement (row-column of the top left element) in the original matrix. There will be only one process with rank 0, that will read the file name with the input data, read from the file the value of n, read from the file the entire matrix, and will output the submatrix of size 2x2 with the largest sum of its elements and its position on the screen. All the other processes will receive portions of the matrix and contribute to identifying the submatrix.

### Points to still explore
Does increasing process count cause frequent send/rec blockings?
Trying to architect aspects of our code to use more collective communication.
How can we parallize this? 

