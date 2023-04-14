//#include <mpi.h>
//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//int main(int argc, char** argv) {
//    MPI_Init(&argc, &argv);
//
//    int rank, size;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    int R = rank + 2;
//    vector<int> sendbuf(R);
//    for (int i = 0; i < R; i++) {
//        sendbuf[i] = i;
//    }
//
//    vector<int> recvcounts(size);
//    vector<int> displs(size);
//    int total_count = 0;
//    for (int i = 0; i < size; i++) {
//        int count = i + 2;
//        recvcounts[i] = count;
//        displs[i] = total_count;
//        total_count += count;
//    }
//
//    vector<int> recvbuf(total_count);
//    MPI_Gatherv(sendbuf.data(), R, MPI_INT, recvbuf.data(), recvcounts.data(), displs.data(), MPI_INT, 0, MPI_COMM_WORLD);
//
//    if (rank == 0) {
//        for (int i = 0; i < size; i++) {
//            int offset = displs[i];
//            int count = recvcounts[i];
//            vector<int> data(count);
//            for (int j = 0; j < count; j++) {
//                data[j] = recvbuf[offset + j];
//            }
//            sort(data.begin(), data.end());
//            cout << "Rank " << i << ": ";
//            for (int j = 0; j < count; j++) {
//                cout << data[j] << " ";
//            }
//            cout << std::endl;
//        }
//    }
//
//    MPI_Finalize();
//    return 0;
//}
