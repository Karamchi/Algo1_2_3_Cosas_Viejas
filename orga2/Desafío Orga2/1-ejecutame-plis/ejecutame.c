#include <stdio.h>
#include <stdlib.h>


int main(void) {
	char data[110] = {0}; // No se olviden de hacer el stack ejecutable!
	FILE *f = fopen("archivo", "rb");
	if (f == NULL) goto perdiste;
	size_t res = fread(data, 1, 100, f);
	if (res != 100) goto perdiste;
	fclose(f);

	// Basicamente lo que se hace aca es convertir data
	// a un puntero a funcion y llamarlo.
	((void (*)(void)) data)();

	return 0;
perdiste:
	printf("Perdiste\n");
	exit(1);
}
