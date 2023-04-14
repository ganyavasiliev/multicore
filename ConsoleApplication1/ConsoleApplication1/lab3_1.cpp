#include <mpi.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int arrSize = 5;
    int arr[arrSize] = { rank + 1, rank + 2, rank + 3, rank + 4, rank + 5 };

    int* recvbuf = nullptr;
    if (rank == 0) {
        recvbuf = new int[arrSize * size];
    }

    MPI_Gather(arr, arrSize, MPI_INT, recvbuf, arrSize, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        vector<pair<int, vector<int>>> data;

        for (int i = 0; i < size; i++) {
            vector<int> tmpVec;
            for (int j = 0; j < arrSize; j++) {
                tmpVec.push_back(recvbuf[i * arrSize + j]);
            }
            data.push_back(make_pair(i, tmpVec));
        }

        sort(data.begin(), data.end());

        for (const auto& pair : data) {
            if (pair.first == 0) {
                for (int i = 0; i < arrSize; i++) {
                    cout << arr[i] << " ";
                }
            }
            else {
                for (int i = 0; i < arrSize; i++) {
                    cout << pair.second[i] << " ";
                }
            }
            cout << endl;
        }

        delete[] recvbuf;
    }

    MPI_Finalize();
    return 0;
}
