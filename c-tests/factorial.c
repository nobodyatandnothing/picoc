#include <stdlib.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	int in = atoi(argv[1]);
	int fact = 1;

	for (int i = 1; i <= in; i++) {
		fact *= i;
	}

	printf("%d factorial is %d", in, fact);

	return 0;
}
