#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int np, rank;
    int N=10;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int ai[2]={rank, rank+1};
    int sum[2]={};

    MPI_Reduce(&ai, sum, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank==0){
        printf("sum=(%i, %i)\n", sum[0], sum[1]);
    }

    MPI_Finalize();

    return 0;

}
