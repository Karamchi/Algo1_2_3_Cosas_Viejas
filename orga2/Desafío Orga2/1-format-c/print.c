#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static char data[101] = {0};

void funcion(int c) {
	printf(data);
	printf("El valor de c es %d\n", c);
}

int main(void) {
	FILE *f = fopen("archivo", "r");
	if (f == NULL) goto perdiste;
	size_t res = fread(data, 1, 99, f);
	if (res != 99)  goto perdiste;
	data[99] = '\n';
	srand(time(NULL));
	int c = rand();
	funcion(c);
	return 0;
perdiste:
	printf("Perdiste\n");
	exit(1);
}
