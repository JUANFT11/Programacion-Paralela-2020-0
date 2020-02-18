/*
 ============================================================================
 Name        : Lab_Factorial.c
 Author      : Juan
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
//#include<iostream>
#include<stdio.h>
#include"pthread.h"
#include<stdlib.h>
//using namespace std;
int num;
void*factorial(int n) {
	int fac = 1;
	for (int a = 1; a <= n; a++) {
		fac = fac * a;


	}
	printf("El factorial del numero dado es: %d\n\n", fac);

}

int main() {
	int num;
	pthread_t t;
	printf(" Ingrese un numero para el factorial: ");
	scanf("%d",&num);
	pthread_create(&t, NULL, factorial, &num);
	pthread_join(t,NULL);
	return 0;
}
