int main(void)
{
    int i = 123;
	int j = 456;
	int k = 0;

	for (i = 0, j = 0; i < 2; i++, j++) {
		k += 2;
	}

	return k - (j * 2);
}
