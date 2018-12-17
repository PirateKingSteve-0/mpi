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


## maxSubmatrixLocator


### Known Errors and output

/project/maxSubmatrixLocator $ mpic++ main.cpp -o main
/project/maxSubmatrixLocator $ mpiexec -np 3 ./main 2

The matrix read in is: 
4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 
1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 
8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 
5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 
4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 
1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 
8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 
5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 
4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 
1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 
4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 
1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 
8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 
5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 
4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 
1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 
8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 
5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 
4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 
1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 
4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 
1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 
8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 
5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 
4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 
1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 
8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 8 5 4 3 8 5 4 3 8 5 
5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 5 6 3 9 5 6 3 9 5 6 
4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 4 1 5 7 4 1 5 7 4 1 
1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 1 2 3 4 1 2 3 4 1 2 

The max sum of a submatrix of size: 2x2 has a value of: 24
It starts at row 3 and column 11

The submatrix reads: 
8 5 
5 6 

/project/maxSubmatrixLocator $ 



## maxSubmatrixLocator_v2




### Known Errors and output
There is an error with memeory allocation that we couldn't solve.


#### Output
/project/maxSubmatrixLocator_v2 $ mpic++ main.cpp -o main
/project/maxSubmatrixLocator_v2 $ mpiexec -np 10 ./main

The matrix read in is: 
4 1 5 7 
1 2 3 4 
8 5 4 3 
5 6 3 9 

The max is: 24
The submatrix: 
8 5 
5 6 

=   BAD TERMINATION OF ONE OF YOUR APPLICATION PROCESSES
=   PID 5279 RUNNING AT bc33b37a853f
=   EXIT CODE: 11
=   CLEANING UP REMAINING PROCESSES
=   YOU CAN IGNORE THE BELOW CLEANUP MESSAGES
===================================================================================
YOUR APPLICATION TERMINATED WITH THE EXIT STRING: Segmentation fault (signal 11)
This typically refers to a problem with your application.
Please see the FAQ page for debugging suggestions
/project/maxSubmatrixLocator_v2 $ mpiexec -np 10 ./main

The matrix read in is: 
4 1 5 7 
1 2 3 4 
8 5 4 3 
5 6 3 9 


===================================================================================
=   BAD TERMINATION OF ONE OF YOUR APPLICATION PROCESSES
=   PID 5291 RUNNING AT bc33b37a853f
=   EXIT CODE: 11
=   CLEANING UP REMAINING PROCESSES
=   YOU CAN IGNORE THE BELOW CLEANUP MESSAGES
===================================================================================
YOUR APPLICATION TERMINATED WITH THE EXIT STRING: Segmentation fault (signal 11)
This typically refers to a problem with your application.
Please see the FAQ page for debugging suggestions
/project/maxSubmatrixLocator_v2 $ 
=======
