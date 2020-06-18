int main(void)
{
    int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i < 2; i++, j++) {
		k += 2;
	}

	return k - (j * 2);
}
