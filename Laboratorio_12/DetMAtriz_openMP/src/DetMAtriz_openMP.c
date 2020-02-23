/*
 ============================================================================
 Name        : DetMAtriz_openMP.c
 Author      : Juan Fernandez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

int main()
{
int i,j,k,l,n ;
float a[100][100];
float det;
double tInicio, tFin;
printf("Ingrese el orden de la matriz N = " );
scanf("%d",&n);




srand(time(0));
for(i=1;i<=n;i++)
{ for(j=1;j<=n;j++)
{a[i][j]=(rand()%20)+1;}}


for(i=1;i<=n;i++)
{ for(j=1;j<=n;j++)
printf("\t\t\tA(%d,%d) =%8.4f\n",i,j,a[i][j] );
}



#pragma omp parallel
{
	tInicio = omp_get_wtime();
	int id = omp_get_thread_num();
	int nt = omp_get_num_threads();
	int size = n/ nt;
	int ini = id * size +1;
	int fin = ini + size-2;


	det=a[1][1];
	for(k=ini;k<=fin;k++)
	{ l=k+1;
	for(i=l;i<=n;i++)
	{ for(j=l;j<=n;j++)
		a[i][j] = ( a[k][k]*a[i][j]-a[k][j]*a[i][k] )/a[k][k]; }
	det=det*a[k+1][k+1];
	}
	printf("\n");
	printf("La determinante es = %f",det);

	tFin=omp_get_wtime();
	printf("\n");
	printf("Tiempo:  %f segundos",tFin-tInicio);
}
return 0;
}
