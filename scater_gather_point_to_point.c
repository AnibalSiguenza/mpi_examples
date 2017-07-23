#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int np, rank;
    int N=10;
    int * data;
    MPI_Status status;

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

    if(rank==0){
        for(int i=0; i<np; i++){
            MPI_Send(&data[i*N_local], N_local, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Recv(local_data, N_local, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);


    for(int i=0; i<N_local; i++){
        local_data[i]=local_data[i]*rank;
    }
    
    MPI_Send(local_data, N_local, MPI_INT, 0, 0, MPI_COMM_WORLD);

    if(rank==0){
        for(int i=0; i<np; i++){
            MPI_Recv(&data[i*N_local], N_local, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        }
    }

    if(rank==0){
        for(int i=0; i<N; i++){
            printf("%i\n", data[i]);
        }
    }

    MPI_Finalize();

    return 0;

}
