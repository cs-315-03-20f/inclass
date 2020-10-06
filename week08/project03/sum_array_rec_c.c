int sum_array_rec_c(int *arr, int index, int len) {
    if (index == len - 1)
        return arr[index];
    return arr[index] + sum_array_rec_c(arr, index + 1, len);
}
