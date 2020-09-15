#include <stdio.h>

#define BITSPERLONG 32
#define TOP2BITS(x) ((x & (3L << (BITSPERLONG-2))) >> (BITSPERLONG-2))

int main(void) {
    unsigned long a = 1;
    unsigned long b = 0;

    printf("%2d: 0x%016lx\n", 0, a);

	for (int i = 1; i < 65; i++) {
	    a <<= 1;
        b = TOP2BITS(a);
	    printf("%2d: 0x%016lx 0x%lx\n", i, a, b);
	}

    unsigned long x = 0;
	x = TOP2BITS(0x40000000);
    printf("0x%lx\n", x);

    unsigned long y = TOP2BITS(0x40000000);
    printf("0x%lx\n", y);

	return 0;
}
