int main(void) {
	char arr[20];
	int a;
	int size1 = sizeof(arr);
    int size2 = sizeof(char[20]);
    int size3 = sizeof(a);
    int size4 = sizeof(int);

	return size1 - size2 + size3 - size4;
}
