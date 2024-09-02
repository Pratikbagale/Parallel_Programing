// MPI_BYTE  : it represent a single byte of data(8 bits).it is often used when you
// want to send raw binary data without any interpretation or conversion

#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{

    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char buffer[26]; // Array of 10 bytes

    if (rank == 0)
    {
        // start the buffer with some data
        for (int i = 0; i < 26; i++)
        {
            buffer[i] = 'A' + i;
        }
        // Send 10 bytes from buffer to process 1
        MPI_Send(buffer, 26, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1)
    {
        // Receive 10 bytes into buffer from process 0
        MPI_Recv(buffer, 26, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received buffer in process %d: ", rank);
        for (int i = 0; i < 26; i++)
        {
            printf("%c", buffer[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}

// mpicc -o byte byte.c
// mpirun --oversubscribe -np 4 ./byte