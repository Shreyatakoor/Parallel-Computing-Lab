#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int number;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Program requires at least 3 processes
    if (size <4) {
        if (rank == 0) {
            printf("This program requires at least 4 processes.\n");
        }

        MPI_Finalize();
        return 0;
    }

    // Process 0 sends a number to Process 1
    if (rank == 0) {
        number = 100;

        printf("Process 0 is sending number %d to Process 1\n", number);

        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }

    // Process 1 receives from Process 0 and sends to Process 2
    else if (rank == 1) {
        MPI_Recv(&number, 1, MPI_INT, 0, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 1 received number %d from Process 0\n", number);

        number = number + 50;

        printf("Process 1 is sending updated number %d to Process 2\n", number);

        MPI_Send(&number, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
    }

    // Process 2 receives from Process 1
    else if (rank == 2) {
        MPI_Recv(&number, 1, MPI_INT, 1, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 2 received number %d from Process 1\n", number);
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}