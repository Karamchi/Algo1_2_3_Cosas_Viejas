#include <stdio.h>
#include <stdlib.h>

int main(void) {
	unsigned int a, b;
	printf("Ingrese dos numeros\n");
	scanf("%u %u", &a, &b);
	if (a <= 100 || b <= 100) { printf("Perdiste\n"); exit(1); }
	if (a + b != 100) { printf("Perdiste\n"); exit(1);}
	printf("Ganaste\n");
	return 0;
}
