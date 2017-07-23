#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int np, rank;
    int N=10;
    int * data;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank==0){
        data=calloc(sizeof(int), N);
        for(int i=0; i<N; i++){
            data[i]=i;
        }
    }
    
    int N_local=N/np;
    int * local_data=calloc(sizeof(int),N_local);

    MPI_Scatter(data, N_local, MPI_INT, local_data, N_local, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i=0; i<N_local; i++){
        local_data[i]=local_data[i]*rank;
    }
    
    MPI_Gather(local_data, N_local, MPI_INT, data, N_local, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank==0){
        for(int i=0; i<N; i++){
            printf("%i\n", data[i]);
        }
    }

    MPI_Finalize();

    return 0;

}
