// MPI_PACKED : is used in conjunction with MPI_Pack and MPI_Unpack functions to send
// a collection of data types together in a single message, allowing you to pack multiple
// datatypes into a contiguous buffer. This is particularly useful when you want to send complex,
// non-contiguous data structures or mixed data types in a single communication call.

    #include <mpi.h>
    #include <stdio.h>

    int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        int a = 10;
        double b = 20.5;
        char c[5] = "Hello";

        int position = 0;
        char buffer[100]; // buffer to hold packed data

        // Pack integer,double and char array into buffer
        MPI_Pack(&a, 1, MPI_INT, buffer, 100, &position, MPI_COMM_WORLD);
        MPI_Pack(&b, 1, MPI_DOUBLE, buffer, 100, &position, MPI_COMM_WORLD);
        MPI_Pack(c, 5, MPI_CHAR, buffer, 100, &position, MPI_COMM_WORLD);

        // send packed buffer to process 1
        MPI_Send(buffer, position, MPI_PACKED, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1)
    {
        int a;
        double b;
        char c[5];

        int position = 0;
        char buffer[100];

        // receive packed buffer from process 0
        MPI_Recv(buffer, 100, MPI_PACKED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // unpacked data from the buffer
        MPI_Unpack(buffer, 100, &position, &a, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, 100, &position, &b, 1, MPI_DOUBLE, MPI_COMM_WORLD);
        MPI_Unpack(buffer, 100, &position, c, 5, MPI_CHAR, MPI_COMM_WORLD);

        printf("Received data in process %d: a = %d, b = %f, c = %s\n", rank, a, b, c);
    }
        MPI_Finalize();
        return 0;
}






// mpicc -o packed packed.c
// mpirun --oversubscribe -np 4 ./packed

// Received data in process 1: a = 10, b = 20.500000, c = Hello