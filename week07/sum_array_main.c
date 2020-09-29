#include <stdio.h>

int sum_array_c(int*, int);
int sum_array_s(int*, int);

int main(int argc, char **argv) {
	int arr[4] = {1,2,3,4};
	int s1 = sum_array_c(arr, 4);
	int s2 = sum_array_s(arr, 4);
	printf("sum_array_c = %d, sum_array_s = %d\n", s1, s2);
}
