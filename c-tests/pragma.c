int a;

#pragma test1

int b;

_Pragma( "test2" )

int main(void) {
	a = 0;

#pragma test3

	b = 1;

    _Pragma("test4")

	return a;
}
