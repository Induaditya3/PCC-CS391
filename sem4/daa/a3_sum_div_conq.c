#include <stdio.h>

// sum of elements using divide and conquer approach
// start and end are indexes that specify range of array to sum
// start, end are inclusive indexes
int sum(int arr[], int start, int end){
  // base cases
  // case 1: no of element to sum is 1
  if (start == end) return arr[start];
  // case 2: no of element to sum is 2
  if (start+1 == end) return arr[start] + arr[end];
  int mid = (start+end)/2;
  // recursive case or divide step
  // split the array into two halves and find their sum
  int left_sum = sum(arr, start, mid);
  int right_sum = sum(arr, mid+1, end);
  // conquer step
  return left_sum + right_sum;
}

int main(){
  int arr[] = {1,2,3,4,5,7};
  int size = sizeof(arr)/sizeof(arr[0]);
  printf("Sum = %d\n",sum(arr,0, size-1));
  int s = 0;
  for (int i = 0; i < size; i++){
    s+= arr[i];
  }
  printf("%d \n",s);
  return 0;
}
