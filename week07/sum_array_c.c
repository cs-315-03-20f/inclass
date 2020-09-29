int sum_array_c(int *array, int len) {
	int sum = 0;
	for (int i = 0; i < len; i++) {
		sum += array[i];
	}
	return sum;
}
