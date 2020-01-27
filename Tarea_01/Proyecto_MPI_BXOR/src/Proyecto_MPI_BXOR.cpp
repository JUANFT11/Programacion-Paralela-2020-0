/*
 ============================================================================
 Name        : Proyecto_MPI_BXOR.c
 Author      : Juan Fernandez
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/**
  * Ilustra cómo usar una operación exclusiva o de reducción a nivel de bits.
  * Esta aplicación consiste en una exclusiva o reducción a nivel de bit;
  * cada proceso MPI envía su valor de reducción antes de la exclusiva bit-wise
  * o de estos valores se almacena en el proceso raíz de MPI. Se puede visualizar como
  * sigue, con MPI proceso 0 como root:
 *
 * +-----------+ +-----------+ +-----------+ +-----------+
 * | Process 0 | | Process 1 | | Process 2 | | Process 3 |
 * +-+-------+-+ +-+-------+-+ +-+-------+-+ +-+-------+-+
 *   | Value |     | Value |     | Value |     | Value |
 *   |   0   |     |   1   |     |   3   |     |   8   |
 *   +-------+     +-------+     +-------+     +-------+
 *            \         |           |         /
 *             \        |           |        /
 *              \       |           |       /
 *               \      |           |      /
 *                +-----+-----+-----+-----+
 *                            |
 *                        +---+---+
 *                        |  BXOR |
 *                        +---+---+
 *                            |
 *                        +---+---+
 *                        |   10  |
 *                      +-+-------+-+
 *                      | Process 0 |
 *                      +-----------+
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Obtenga el número de procesos y verifique que solo se utilicen 4.
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("Esta aplicación está diseñada para ejecutarse con 4 procesos.\n");
        //MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Determinar el funcionamiento de la raízk
    int root_rank = 0;

    // Obtén mi rango
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Cada proceso MPI envía su rango a reducción, el proceso raíz MPI recoge el resultado
    char all_values[4] = {0, 1, 3, 8};
    char my_value = all_values[my_rank];
    char reduction_result = 0;
    MPI_Reduce(&my_value, &reduction_result, 1, MPI_UNSIGNED_CHAR, MPI_BXOR, root_rank, MPI_COMM_WORLD);

    if(my_rank == root_rank)
    {
        printf("La exclusiva en cuanto a bits o de todos los valores es %d.\n", reduction_result);
    }

    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
