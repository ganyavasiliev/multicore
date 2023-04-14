#include <mpi.h>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size, k = 3;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = k * size;
    vector<int> data(n);

    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            data[i] = i;
        }
    }

    vector<int> localData(k);
    MPI_Scatter(&data[0], k, MPI_INT, &localData[0], k, MPI_INT, 0, MPI_COMM_WORLD);

    cout << "Process " << rank << ": ";
    for (int i = 0; i < k; i++) {
        cout << localData[i] << " ";
    }
    cout << endl;

    MPI_Finalize();
    return 0;
}
