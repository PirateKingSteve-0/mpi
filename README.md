# MPI

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

===================================================================================
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

