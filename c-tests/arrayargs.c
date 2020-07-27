int arr[3] = {77, 88, 99};

void func(int x[3], int y[3]) {
    x[0] = 1;
    y[1] = -1;
}

int main(void) {
    arr[0] = 10;
    arr[1] = 20;
    func(arr, arr);
    int ret = arr[0] + arr[1] + arr[2] - 99;
	return ret;
}
