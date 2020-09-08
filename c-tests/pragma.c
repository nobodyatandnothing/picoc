int a;

#pragma test1

int b;

_Pragma( "test2" )

int main(void) {
	a = 0;

#pragma test3

	b = 1;

    _Pragma("test4")

    int c = 10;
    for (int i = 0; i < 10; i++)
#pragma test_loop
        c--;

    int d = 0;
    if (0)
#pragma test_loop
        d = 100;

    int e = 5;
    while (e > 0)
#pragma test_while
        e--;

    int f = 8;
    do
#pragma test_do
        f--;
    while (f > 0);

    return c + d + e + f;

#pragma test_end
}
