#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int k = size - 2;
    int* data = new int[k + 2];
    if (rank == 0) {
        for (int i = 0; i < k + 2; i++) {
            data[i] = i + 1;
        }
    }

    int* sendcounts = new int[size];
    int* displs = new int[size];
    for (int i = 0; i < size; i++) {
        sendcounts[i] = 3;
        displs[i] = i + 1;
    }
    int* recvbuf = new int[3];
    MPI_Scatterv(data, sendcounts, displs, MPI_INT, recvbuf, 3, MPI_INT, 0, MPI_COMM_WORLD);

    cout << "Process " << rank << ": " << recvbuf[0] << " " << recvbuf[1] << " " << recvbuf[2] << endl;

    MPI_Finalize();
    return 0;
}
