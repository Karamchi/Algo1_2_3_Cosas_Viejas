#include <stdio.h>

int main(void) {
	int a = 5;
	double b = 3.141592653;
	char data[10];

	gets(data);

	printf("%d %.4f\n", a, b);
	return 0;
}
