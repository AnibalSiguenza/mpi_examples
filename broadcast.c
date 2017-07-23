#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int np, rank;
    int N=10;
    int * data=calloc(sizeof(int), N);

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank==0){
        for(int i=0; i<N; i++){
            data[i]=i;
        }
    }

    MPI_Bcast(data, N, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank==3){
        for(int i=0; i<N; i++){
            printf("%i\n", data[i]);
        }
    }

    MPI_Finalize();

    return 0;

}
