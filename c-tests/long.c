#include <stdio.h>

int main(void) {
    unsigned long a = 1;

    printf("%2d: 0x%016lx\n", 0, a);

	for (int i = 1; i < 65; i++) {
	    a <<= 1;
	    printf("%2d: 0x%016llx\n", i, a);
	}

	return 0;
}
