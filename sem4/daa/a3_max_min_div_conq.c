#include <stdio.h>

typedef struct {
  int max, min;
}MaxMin;

// finding maximum and minimum of an array using divide and conquer approach
MaxMin maxmin(int arr[], int start, int end){
  // base cases:
  // case 1: no of elements to consider is 1
  if (start == end ) {
    return (MaxMin){arr[start], arr[start]};
  }
  // case 2: no of elements to consider is 2
  if (start + 1 == end) {
    return (MaxMin){
      .max = arr[start] > arr[end] ? arr[start]:arr[end],
      .min = arr[start] < arr[end] ? arr[start]:arr[end]
    };
  }
  // recursive case
  // divde step: find max, min in left and right halves
  int mid = (start+end)/2;
  MaxMin left = maxmin(arr, start, mid);
  MaxMin right = maxmin(arr, mid+1, end);
  // conquer step: find min, max between left and right
  return (MaxMin){
    .max = left.max > right.max ? left.max : right.max,
    .min = left.min < right.min ? left.min : right.min
  };
}

int main(){
  int arr[] = {3,1,4,1,4};
  int size = sizeof(arr)/sizeof(arr[0]);

  MaxMin val = maxmin(arr, 0, size-1);
  printf("Max: %d, Min: %d", val.max, val.min);
  return 0;
}
