#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char **argv) {
	long long int a, b;
	errno = 0;
	if (argc != 3) goto perdiste;

	a = strtoll(argv[1], NULL, 10);
	if (errno != 0) goto perdiste;
	b = strtoll(argv[2], NULL, 10);
	if (errno != 0) goto perdiste;

	if (a >= UINT_MAX || a <= 0) goto perdiste;
	if (b >= UINT_MAX || b <= 0) goto perdiste;
	unsigned int c, d;
	c = (unsigned int) a;
	d = (unsigned int) b;

	if (c <= 100 || d <= 100) goto perdiste; 
	if (c + d != 100) goto perdiste;
	printf("Ganaste\n");
	return 0;
perdiste:
	printf("Perdiste\n");
	exit(1);
}
