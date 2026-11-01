#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char** argv) {

	int* a;

	a = malloc(sizeof(int));

	free(a);

	printf("%d", *a);
}
