#include <stdio.h>

#define DCTSIZE 8
#define DESCALE(x)  (((x) + (1 << 14)) >> 15)

//#define FIX_1_847759065  ((int)15137) /* FIX(1.847759065) */


int main(void) {

    int z1 = -881723700;
    int tmp12 = -408000;

    int val = z1 + tmp12 * ( -15137 );

    int debug = ( int ) DESCALE(z1 + tmp12 * ( -15137 ));
    printf("%d\n", debug);

    return debug != 30493; // 161565
}
