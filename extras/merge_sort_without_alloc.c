/*
 * Merge sort using a single scratch buffer allocated once per sort.
 * Returns 0 on success, -1 on allocation failure.
 * @author GPT-5.1
 */

#include <stdio.h>
#include <stdlib.h>

// Order predicate used by merge
static inline int compare(float a, float b) { return a <= b; }

static void merge(float *arr, float *aux, int left, int mid, int right) {
	// Merge sorted slices [left, mid) and [mid, right) from arr into aux, then
	// copy the merged run back into arr
	int i = left, j = mid, k = left;
	while (i < mid && j < right)
		aux[k++] = compare(arr[i], arr[j]) ? arr[i++] : arr[j++];
	while (i < mid)
		aux[k++] = arr[i++];
	while (j < right)
		aux[k++] = arr[j++];
	for (int idx = left; idx < right; ++idx)
		arr[idx] = aux[idx];
}

static void merge_sort_inner(float *arr, float *aux, int left, int right) {
	// Sort the slice [left, right) in-place using aux as shared scratch
	if (right - left <= 1)
		return;
	int mid = left + (right - left) / 2;
	merge_sort_inner(arr, aux, left, mid);
	merge_sort_inner(arr, aux, mid, right);
	merge(arr, aux, left, mid, right);
}

int merge_sort(float *arr, int len) {
	// Allocate one auxiliary buffer for the entire sort
	float *aux = malloc(sizeof(float) * len);
	if (!aux)
		return -1;
	merge_sort_inner(arr, aux, 0, len);
	// aux holds no ownership once merge_sort_inner returns
	free(aux);
	return 0;
}

int main(void) {
	float arr[] = {9, 5, 6, 7, 8, 5, 1, 3, 5, 7, 8};
	int len = (int)(sizeof(arr) / sizeof(arr[0]));

	if (merge_sort(arr, len) != 0) {
		fprintf(stderr, "Allocation failed\n");
		return 1;
	}

	for (int i = 0; i < len; i++)
		printf("%f ", arr[i]);
	putchar('\n');
	return 0;
}
