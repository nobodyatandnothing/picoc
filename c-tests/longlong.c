long long int a;
unsigned long long b;

int main(void) {
	a = 0x7fffffff;
    a++;

	b = 0xffffffff;
	b++;

	return !((a == 0x80000000) && (b == 0x100000000));
}
