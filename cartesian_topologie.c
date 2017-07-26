#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int np, rank;
    int N=10;

    MPI_Comm comm_2d;

    MPI_Init(&argc, &argv);

    int dims[2];
    int periods[2];
    int coords[2];
    int source; int dest;

    dims[0]=2; dims[1]=2;
    periods[0]=0; periods[1]=0;
    int reorder=0;

    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &comm_2d);
    MPI_Cart_coords(comm_2d, rank, 2, &coords);
    
    int dimension_of_movement=0; //to to move in x and 1 to move in y
    int number_of_cells_to_move=1; //to move in x or y direction n space
    
    MPI_Cart_shift(comm_2d, dimension_of_movement, number_of_cells_to_move, &source, &dest); //here you obtain the origin and destination ...
                                                                                             //... rank to do the specific data transfer desired  

    printf("Rank=%i coordinates=(%i,%i) source=%i dest=%i\n", rank, coords[0], coords[1], source, dest);

    //MPI_Sendrecv(a, 1, MPI_REAL, dest, 13, b, 1, MPI_REAL, source, 13, comm_2d, &status);

    MPI_Finalize();

    return 0;
}
