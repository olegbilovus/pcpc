#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, msg_integer = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        MPI_Send(&msg_integer, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        printf("Rank: %d, Message Sent: %d\n", rank, msg_integer);
    }

    else if (rank == 1)
    {
        MPI_Recv(&msg_integer, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank: %d, Message Received: %d\n", rank, msg_integer);
    }

    MPI_Finalize();
    return 0;
}
