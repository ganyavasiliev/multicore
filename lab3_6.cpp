#include <iostream>
#include <mpi.h>

using namespace std;

void average_op(void* invec, void* inoutvec, int* len, MPI_Datatype* datatype) {
    int count = *len;
    double* in = (double*)invec;
    double* inout = (double*)inoutvec;
    for (int i = 0; i < count; i++) {
        inout[i] = (in[i] + inout[i]) / 2.0;
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double local_sum = rank + 1;
    double global_sum = 0;
    MPI_Op op;
    MPI_Op_create((MPI_User_function*)average_op, 1, &op);
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, op, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        double expected_sum = (size * (size + 1)) / 2.0;
        cout << "Global sum: " << global_sum << endl;
    }
    MPI_Op_free(&op);
    MPI_Finalize();
    return 0;
}
