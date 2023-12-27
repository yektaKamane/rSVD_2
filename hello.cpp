#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the total number of processes and the rank of the current process
    int numProcesses, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Print "Hello, World!" from each process
    std::cout << "Hello, World! from process " << rank << " out of " << numProcesses << " processes." << std::endl;

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
