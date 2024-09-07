#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank;
    int size;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int globalsum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {

        FILE *inputFile = fopen("input.txt", "r");
        if (inputFile == NULL)
        {
            printf("Error opening input file \n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        for (int i = 0; i < 12; i++)
        {
            fscanf(inputFile, "%d", &arr[i]);
        }
        fclose(inputFile);

        int sum = 0;
        for (int i = 0; i <= 2; i++)
        {
            sum = sum + arr[i];
        }
        printf("sum0: %d\n", sum);
        globalsum = sum;
        for (int i = 1; i < size; i++)
        {
            int temp = 0;
            MPI_Recv(&temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            globalsum = globalsum + temp;
        }
        printf("globalsum: %d\n", globalsum);

        FILE *outputFile = fopen("output.txt", "w");
        if (outputFile == NULL)
        {
            printf("Error opening output file.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        fprintf(outputFile, "Global sum: %d\n", globalsum);
        fclose(outputFile);
        }

    if (rank == 1)
    {
        int sum = 0;
        for (int i = 3; i <= 5; i++)
        {
            sum = sum + arr[i];
        }
        printf("sum1: %d\n", sum);
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 2)
    {
        int sum = 0;
        for (int i = 6; i <= 8; i++)
        {
            sum = sum + arr[i];
        }
        printf("sum2: %d\n", sum);
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 3)
    {
        int sum = 0;
        for (int i = 9; i <= 11; i++)
        {
            sum = sum + arr[i];
        }
        printf("sum3: %d\n", sum);
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}

// mpicc -o sum sum.c
// mpirun --oversubscribe -np 4 ./sum