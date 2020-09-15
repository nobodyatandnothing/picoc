#include <stdio.h>

int adpcm_dec_filtez( int *bpl, int *dlt )
{
    int i;
    long int zl;

    printf("*bpl=%d *dlt=%d\n", *bpl, *dlt);

    zl = ( long )( *bpl++ ) * ( *dlt++ );

    for ( i = 1; i < 6; i++ )
        zl += ( long )( *bpl++ ) * ( *dlt++ );

    printf("*bpl=%d *dlt=%d zl=%ld\n", *bpl, *dlt, zl);

    return ( ( int )( zl >> 14 ) ); /* x2 here */
}


int a[6];
int b[6];

int main( void )
{
    adpcm_dec_filtez(&a, &b);
    return !(a == 0 && b == 8);
}
