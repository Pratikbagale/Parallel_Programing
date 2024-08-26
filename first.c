#include <mpi.h>    // include MPI library
#include <stdio.h>  // standard input/output header
#include <stdlib.h> // standard library header

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv); // Initialize MPI enviornment

    int size;   // no of processes in MPI world
    int rank;   // rank of current process
    int number; // variable to store no to be sent/received

    MPI_Comm_size(MPI_COMM_WORLD, &size); // get the no of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // get the rank of current

    if (rank == 0)
    {
        // Check if this is the master process(rank 0)
        // Master process(rank 0) send a number to all other processes
        number = -1; // number to send
        for (int i = 1; i < size; i++)
        {
            MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Process 0 sent number %d to process %d\n", number, i);
        }
    }
    else
    {
        // All other processes(rank 1 to N-1) receive the number from process 0
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received number %d from process 0\n", rank, number);
    }
    MPI_Finalize(); // Finalize the MPI enviornment
    return 0;
}

//  mpicc -o first first.c
//  mpirun --oversubscribe -np 4 ./first