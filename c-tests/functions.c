void a() {
    int x = 1;
}

int b(int x, int y) {
    return x + y;
}

void c(int x, int y, int z) {
    return;
}

int main(void) {
	a();
	b(1, 2);
	b(3, 4);
	return 0;
}
