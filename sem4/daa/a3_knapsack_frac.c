#include <stdio.h>
#include <stdlib.h>


typedef struct {
  int weight, price;
  float ratio; // price per weight
  int idx; // original index of the item
}Item;

// cmp function for qsort function of stdlib
// which will compare items based on price per weight
int cmp(const void *a, const void *b){
  Item* item = (Item*)a;
  Item* item2 = (Item*)b;
  if (item2->ratio > item->ratio) return 1;
  else if (item2->ratio < item->ratio) return -1;
  return 0;
}


int main(){
  // define the items
  int prices[] = {300,200,400,500};
  int weights[] = {2,1,5,3};
  const int NUM_ITEMS = sizeof(prices)/sizeof(int);
  Item items[NUM_ITEMS];
  for (int i = 0; i < NUM_ITEMS ; i++){
    items[i] = (Item){
      .weight = weights[i],
      .price = prices[i],
      .ratio = (float)prices[i]/weights[i],
      .idx = i
    };
  }

  // define max capacity of the knapsack
  const int CAPACITY = 10;

  // sort the items based on price per weight
  qsort(items, NUM_ITEMS, sizeof(Item), cmp);

  // initialize arr for tracking which items is taken
  int arr[NUM_ITEMS];
  // fill the sack with items having maximum price per weight first if possible
  int capacity = CAPACITY;
  float total_val = 0;
  for (int i = 0; i < NUM_ITEMS; i++){
    if (capacity < items[i].weight) {
      arr[i] = (float)capacity/items[i].weight;
      total_val += items[i].price * arr[i];
      printf("Item%d ",items[i].idx);
      capacity = 0;
      break;
    }
    capacity -= items[i].weight;
    arr[i] = 1;
    total_val += items[i].price;
    printf("Item%d ",items[i].idx);
  }

  printf("Total profit: %f",total_val);
  return 0;
}
