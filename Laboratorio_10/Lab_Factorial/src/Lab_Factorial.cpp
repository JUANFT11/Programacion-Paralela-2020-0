#include<iostream>
#include<pthread.h>
using namespace std;
int num;
void* factorial() {
	int fac = 1;
	for (int a = 1; a <= num; a++) {
		fac = fac * a;
		cout << "Factorial of Given Number is =" << fac;
	}
}
int main() {
	pthread_t t;
	cout << " Enter Number To Find Its Factorial: ";
	cin >> num;
	pthread_create(&t, NULL, factorial, (void*) &num);
	return 0;
}
