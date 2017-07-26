#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int np, rank;
    int N=5;
    int base[N];
    int receiv[N];
    int size_of_win=N*sizeof(int);
    int disp_unit=sizeof(int);
    MPI_Win win;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for(int i=0; i<N; i++)
        base[i]=i*rank;

    MPI_Win_create(base, size_of_win, disp_unit, MPI_INFO_NULL, MPI_COMM_WORLD, &win);
    MPI_Win_fence(0, win);

    if(rank<np-1){
        MPI_Get(receiv, N, MPI_INT, rank+1, 0, N, MPI_INT, win);
    }else{
        MPI_Get(receiv, N, MPI_INT, 0, 0, N, MPI_INT, win);
    }
    MPI_Win_fence(0, win);

    printf("process %i received this data=%i, %i, %i, %i, %i\n", rank, receiv[0], receiv[1], receiv[2], receiv[3], receiv[4]);

    if(rank<np-1){
        MPI_Put(&rank, 1, MPI_INT, rank+1, 0, 1, MPI_INT, win);
    }else{
        MPI_Put(&rank, 1, MPI_INT, 0, 0, 1, MPI_INT, win);
    }
    MPI_Win_fence(0, win);

    printf("process %i my first element is now %i\n", rank, base[0]);

    MPI_Finalize();

    return 0;
}
