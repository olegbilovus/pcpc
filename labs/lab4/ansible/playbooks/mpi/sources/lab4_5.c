#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "mycollective.h"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    char op = argv[1][0];
    int N = argc >= 3 ? atoi(argv[2]) : 30;
    int char_type = argc >= 4 ? atoi(argv[3]) : 0; // if a 4th arg is passed, char will be used
    MPI_Datatype DATA_TYPE = char_type ? MPI_CHAR : MPI_INT;

    char *array_char = NULL;
    int *array_int = NULL;

    if (char_type)
    {
        array_char = malloc(N * sizeof(char));
        for (int i = 0; i < N; i++)
        {
            array_char[i] = i;
        }
    }
    else
    {
        array_int = malloc(N * sizeof(int));
        for (int i = 0; i < N; i++)
        {
            array_int[i] = i;
        }
    }

    int rank, P;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    double start, end;
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    char *op_str;
    switch (op)
    {
    case 'b':
        op_str = "broadcast";
        broadcast(P, rank, char_type ? array_char : array_int, N, DATA_TYPE, MPI_COMM_WORLD);
        break;
    case 'g':
        op_str = "gather";
        gather(P, rank, char_type ? array_char : array_int, N, DATA_TYPE, MPI_COMM_WORLD);
        break;
    case 's':
        op_str = "scatter";
        scatter(P, rank, char_type ? array_char : array_int, N, DATA_TYPE, MPI_COMM_WORLD);
        break;

    default:
        printf("Selected OP is not valid\n");
        return 1;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    if (rank == 0)
    {
        printf("OP: %s, N: %d, P: %d, Type: %s\nTime in ms = %f\n", op_str, N, P, char_type ? "char" : "int", end - start);
    }

    MPI_Finalize();
    return 0;
}
