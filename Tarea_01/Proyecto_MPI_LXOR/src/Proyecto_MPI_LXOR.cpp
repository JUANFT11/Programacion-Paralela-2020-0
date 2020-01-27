/*
 ============================================================================
 Name        : Proyecto_MPI_LXOR.c
 Author      : Juan Fernandez
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
/**
 * @author RookieHPC
 * @brief Original source code at https://www.rookiehpc.com/mpi/docs/mpi_lxor.php
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

/**
  * Ilustra cómo utilizar una operación lógica exclusiva o de reducción.
  * Esta aplicación consiste en una lógica exclusiva o reducción; cada
  * El proceso MPI envía su valor de reducción antes de la lógica exclusiva o de
  * estos valores se almacenan en el proceso raíz de MPI. Se puede visualizar como
  * sigue, con MPI proceso 0 como root:
 *
 * +-----------+ +-----------+ +-----------+ +-----------+
 * | Process 0 | | Process 1 | | Process 2 | | Process 3 |
 * +-+-------+-+ +-+-------+-+ +-+-------+-+ +-+-------+-+
 *   | Value |     | Value |     | Value |     | Value |
 *   | false |     | false |     | false |     | true  |
 *   +-------+     +-------+     +-------+     +-------+
 *            \         |           |         /
 *             \        |           |        /
 *              \       |           |       /
 *               \      |           |      /
 *                +-----+-----+-----+-----+
 *                            |
 *                        +---+---+
 *                        |  LXOR |
 *                        +---+---+
 *                            |
 *                        +---+---+
 *                        |  true |
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

    // Determinar el rango de la raíz
    int root_rank = 0;

    // Obtén mi rango
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Cada proceso MPI envía su rango a reducción, el proceso raíz MPI recoge el resultado
    bool my_value = (my_rank == 3);
    bool reduction_result = false;
    MPI_Reduce(&my_value, &reduction_result, 1, MPI_C_BOOL, MPI_LXOR, root_rank, MPI_COMM_WORLD);

    if(my_rank == root_rank)
    {
        printf("La lógica exclusiva o de todos los valores es %s.\n", reduction_result ? "true" : "false");
    }

    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
