/*
 ============================================================================
 Name        : Proyecto_MPI_BAND.c
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
      * Ilustra cómo usar una operación de reducción y bit-sabio.
      * Esta aplicación consiste en un bit-sabio y reducción; cada proceso MPI
      * envía su valor para la reducción antes de los bits y de estos valores se almacena en
      * El proceso raíz de MPI. Se puede visualizar de la siguiente manera, con el proceso MPI 0 como
      * raíz:
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
     *                        |  BAND |
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
        char all_values[4] = {0, 1, 3, 8};
        char my_value = all_values[my_rank];
        char reduction_result = 0;
        MPI_Reduce(&my_value, &reduction_result, 1, MPI_UNSIGNED_CHAR, MPI_BAND, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("El bit-wise y de todos los valores es %d.\n", reduction_result);
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }
