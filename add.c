#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank;
    int size;
    int nprocs;
    globalsum = 0;

    int n = 12 / nprocs;
    int offset;
    int B[n];

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int globalsum = 0;
    int sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        for (int i = 1; i < nprocs; i++)
        {
            offset = n * i;
            MPI_Send(&A[offset], n, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        int sum = 0;
        for (int i = 1; i < nprocs; i++)
        {
            sum = sum + A[i];
        }
        globalsum = sum;

        for (int i = 1; i < size; i++)
        {
            temp = 0;
            MPI_Rec(&temp, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
            globalsum = globalsum + temp;
        }
        printf("globalsum is = %d \n", globalsum);
    }
    else
    {
        int B[n];
        MPI_Rec(&B, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum = sum + B[i];
        }
        MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}