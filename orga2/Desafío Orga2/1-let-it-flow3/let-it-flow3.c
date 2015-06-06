#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main(void) {
	int a, b;
	printf("Ingrese dos números enteros\n");
	scanf("%d %d", &a, &b);
	if (b == 0) goto perdiste;
	long long int c = ((long long int) a) / b;
	if (c <= INT_MAX) goto perdiste;
	printf("Ganaste\n");
	return 0;
perdiste:
	printf("Perdiste\n");
	exit(1);
}
