/*
 ============================================================================
 Name        : Proyecto_SumaVectores.c
 Author      : Juan Fernandez
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>


#define DESTINO 1
#define SUMA 2


void llenar_vector(int VECTOR[], int MAX);
void imprime_vectores(int VECTOR[], int MAX);

int main(int argc, char *argv[])
{
	int rank, size;
	int MAX= atoi(argv[1]);
	int VECTOR_A[MAX], VECTOR_B[MAX];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		llenar_vector(VECTOR_A, MAX);
		llenar_vector(VECTOR_B, MAX);

		MPI_Send(VECTOR_A, MAX, MPI_INT, DESTINO, 2, MPI_COMM_WORLD);
		MPI_Send(VECTOR_B, MAX, MPI_INT, DESTINO, 3, MPI_COMM_WORLD);
	}
	else
	{
		if (rank == DESTINO)
		{

			MPI_Recv(VECTOR_A, MAX, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(VECTOR_B, MAX, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);
			printf("Vector A\n");
			imprime_vectores(VECTOR_A, MAX);
			printf("VECTOR B\n");
			imprime_vectores(VECTOR_B, MAX);
			MPI_Send(VECTOR_A, MAX, MPI_INT, SUMA, 2, MPI_COMM_WORLD);
			MPI_Send(VECTOR_B, MAX, MPI_INT, SUMA, 3, MPI_COMM_WORLD);
		}
		else
		{
			if (rank == SUMA)
			{

				MPI_Recv(VECTOR_A, MAX, MPI_INT, DESTINO, 2, MPI_COMM_WORLD, &status);
				MPI_Recv(VECTOR_B, MAX, MPI_INT, DESTINO, 3, MPI_COMM_WORLD, &status);
				int VECTOR_RES[MAX];
				int i;
				for(i = 0; i < MAX; i++)
				{
					VECTOR_RES[i] = (VECTOR_A[i] + VECTOR_B[i]);
				}
				printf("VECTOR RESULTANTE\n");
				imprime_vectores(VECTOR_RES, MAX);
			}
		}
	}
	MPI_Finalize();
	return 0;
}

void llenar_vector(int VECTOR[], int MAX)
{
	srand(time(NULL));
	int i;
	for(i = 0; i < MAX; i++)
	{
		VECTOR[i] = rand()%20;
	}
}

void imprime_vectores(int VECTOR[], int MAX)
{
	int i;
	for(i = 0; i < MAX; i++)
	{
		printf("%d\n", VECTOR[i]);
	}
}
