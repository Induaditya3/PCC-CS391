#include <stdio.h>
#include <stdlib.h>


typedef struct {
  int weight;
  int price;
  int ratio; // price per weight
}Item;

// cmp function for qsort function of stdlib
int cmp(const void *a, void *b){
  Item* item = (Item*)a;
  Item* item2 = (Item*)b;
  return (int) (item->ratio-item2->ratio);
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
      .ratio = weights[i]/prices[i]
    };
  }

  // define max capacity of the knapsack
  const int CAPACITY = 10;

  // sort the items based on price per weight
  
}
