int main(void)
{
	int j = 999;
	int k = 8;

	for (int i = 0; i < 4; i++) {
		j = i - 3;
	}

	for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int z = 0; z < 2; z++) {
                k--;
            }
        }
	}

	return j + k;
}
