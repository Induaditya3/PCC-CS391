/*
 * Merge sort implementation that allocates intermediate arrays on the heap,
 * frees them as soon as they are no longer needed, and returns a newly
 * allocated sorted array without mutating the caller's input.
 * @author Induaditya3
 */
#include <stdio.h>
#include <stdlib.h>

// Compare helper
static inline int compare(float a, float b) { return a <= b; }

float *merge(int len, int len2, float arr[len], float arr2[len2]) {
  // Allocate merged array of size len + len2
  int mergedLen = len + len2;
  float *mergedArr = malloc(sizeof(float) * mergedLen);
  // indexes for iterating each array
  int i, j, k;
  i = j = k = 0;
  // Populate mergedArr until all elements are consumed
  while (k < mergedLen) {
    // If arr2 is exhausted, pull from arr
    if (j >= len2) {
      mergedArr[k] = arr[i++];
    }
    // If arr is exhausted, pull from arr2
    else if (i >= len) {
      mergedArr[k] = arr2[j++];
    }
    // Both have remaining elements; pick the smaller one
    else if (compare(arr[i], arr2[j])) {
      mergedArr[k] = arr[i++];
    }
    else {
      mergedArr[k] = arr2[j++];
    }
    k++;
  }
  // freeup original arrays
  free(arr), free(arr2);
  return mergedArr;
}
// copy elements from the start to end inclusive to other arr
void copyArr(int start, int end, float *arr, float *copyarr) {
  for (int i = start; i <= end; i++)
    copyarr[i - start] = arr[i];
}
// Recursive merge sort on a heap-allocated array; returns a new heap buffer
float *mergeSort_inner(int len, float arr[len]) {
  // Base case: length 0 or 1 is already sorted
  if (len == 1 || len == 0)
    return arr;
  // recursive case: divide array into two arrays
  int mid = len / 2;
  // left half holds indexes 0..mid-1
  float *left_half = malloc(sizeof(float) * mid);
  copyArr(0, mid - 1, arr, left_half);
  // right half holds indexes mid..len-1
  float *right_half = malloc(sizeof(float) * (len - mid));
  copyArr(mid, len - 1, arr, right_half);
  float *sort_left = mergeSort_inner(mid, left_half);
  float *sort_right = mergeSort_inner(len - mid, right_half);
  // free up space of original arr and left an right ones are freed in the
  // recursive call of mergeSort
  free(arr);
  return merge(mid, len - mid, sort_left, sort_right);
}
// wrapper function for merge sort which can take either heap or stack alloc arr
// and does not modify or delete original arr
float *mergeSort(int len, float arr[len]) {
  // create temp arr which will be freed by mergeSort_inner
  float *temparr = malloc(sizeof(float) * len);
  // copy contents
  copyArr(0, len - 1, arr, temparr);
  return mergeSort_inner(len, temparr);
}
int main() {
  float arr[] = {9, 5, 6, 7, 8, 5, 1, 3, 5, 7, 8};
  int len = sizeof(arr) / sizeof(arr[0]);

  // int len = 10;
  // float *arr = malloc(sizeof(float) * len);
  // for (int i = 0; i < len; i++)
  //   arr[i] = 10 - i;

  float *sorted = mergeSort(len, arr);
  for (int i = 0; i < len; i++)
    printf("%f ", sorted[i]);

  free(sorted);
  return 0;
}
