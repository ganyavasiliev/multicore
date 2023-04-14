#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int num_numbers = rank + 2;

    vector<int> send_buffer(num_numbers);
    for (int i = 0; i < num_numbers; i++) {
        send_buffer[i] = i + rank * num_numbers;
    }

    vector<int> recvcounts(size);
    vector<int> displs(size);
    for (int i = 0; i < size; i++) {
        recvcounts[i] = i + 2;
        displs[i] = i > 0 ? displs[i - 1] + recvcounts[i - 1] : 0;
    }

    vector<int> recv_buffer(displs[size - 1] + recvcounts[size - 1]);

    MPI_Allgatherv(send_buffer.data(), num_numbers, MPI_INT, recv_buffer.data(), recvcounts.data(), displs.data(), MPI_INT, MPI_COMM_WORLD);

    for (int i = 0; i < size; i++) {
        cout << "Rank " << i << ": ";
        for (int j = displs[i]; j < displs[i] + recvcounts[i]; j++) {
            cout << recv_buffer[j] << " ";
        }
        cout << std::endl;
    }

    MPI_Finalize();

    return 0;
}
