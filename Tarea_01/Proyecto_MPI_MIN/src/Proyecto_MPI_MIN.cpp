/*
 ============================================================================
 Name        : Proyecto_MPI_MIN.c
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
      * Ilustra cómo usar una operación de reducción mínima.
      * Esta aplicación consiste en una reducción mínima; cada proceso MPI
      * envía su rango de reducción antes de que el mínimo de estos rangos se almacene en el
      * proceso de MPI raíz. Se puede visualizar de la siguiente manera, con el proceso MPI 0 como
      * raíz:
     *
     * +-----------+ +-----------+ +-----------+ +-----------+
     * | Process 0 | | Process 1 | | Process 2 | | Process 3 |
     * +-+-------+-+ +-+-------+-+ +-+-------+-+ +-+-------+-+
     *   | Value |     | Value |     | Value |     | Value |
     *   |   0   |     |   1   |     |   2   |     |   3   |
     *   +-------+     +-------+     +-------+     +-------+
     *            \         |           |         /
     *             \        |           |        /
     *              \       |           |       /
     *               \      |           |      /
     *                +-----+-----+-----+-----+
     *                            |
     *                        +---+---+
     *                        |  MIN  |
     *                        +---+---+
     *                            |
     *                        +---+---+
     *                        |   0   |
     *                      +-+-------+-+
     *                      | Process 0 |
     *                      +-----------+
     **/
    int main(int argc, char* argv[])
    {
        MPI_Init(&argc, &argv);

        //Obtenga el número de procesos y verifique que solo se utilicen 4.
        int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        if(size != 4)
        {
            printf("Esta aplicación está diseñada para ejecutarse con 4 procesos.\n");
           // MPI_Abort (MPI_COMM_WORLD, EXIT_FAILURE);

        }

        // Determinar el rango de la raíz
        int root_rank = 0;

        // Obtén mi rango
        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        // Cada proceso MPI envía su rango a reducción, el proceso raíz MPI recoge el resultado
        int reduction_result = 0;
        MPI_Reduce(&my_rank, &reduction_result, 1, MPI_INT, MPI_MIN, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("El mínimo de todos los rangos es %d.\n", reduction_result);
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }
