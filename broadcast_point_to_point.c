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

    if(rank==0){
        for(int i=1; i<N; i++){
            MPI_Send(data, N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    if(rank!=0){
        MPI_Recv(data, N, MPI_INT, 0, 0, MPI_COMM_WORLD);

    }

    if(rank==1){
        for(int i=0; i<N; i++){
            printf("%i\n", data[i]);
        }
    }

    MPI_Finalize();

    return 0;

}
