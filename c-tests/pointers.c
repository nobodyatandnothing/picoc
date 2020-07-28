int *a;

int main(void) {
	int b[2] = {0, 5};
	a = b;
	a++;
	a++;
	a -= 1;
    (*a)--;
    (*a) += 2;
	return *a - 6;
}
