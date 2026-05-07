// here job sequencing is solved using greedy approach
// each job has deadline and each job takes 1 unit of time
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int id, profit, deadline;
}Job;


// compare function for qsort
int cmp(const void* a, const void* b){
  Job* job = (Job*) a;
  Job* job2 = (Job*) b;

  if (job2->profit > job->profit) return 1;
  else if (job2->profit < job->profit) return -1;
  return 0;
  
}
int main(){
  // define the jobs with thier id, profit, deadline
  Job arr[] = {
    {1, 300, 4},
    {2, 250, 2},
    {3, 130, 3},
    {4, 212, 3},
    {5, 100, 3},
    {6, 424, 3}
  };
  int const NUM_JOBS = sizeof(arr)/sizeof(Job);

  // sort the job array in decreasing order based on profit
  qsort(arr, NUM_JOBS, sizeof(Job), cmp);

  const int MAX_SLOT = 4;
  // stores job id of the alloted job at given slot at index i of the array
  int slots[MAX_SLOT];
  memset(slots, 0, sizeof(slots));

  int profit = 0;
  int avl_slots = MAX_SLOT - 1;

  // iterate through the sorted jobs
  for (int i = 0; i < NUM_JOBS; i++){
    if (avl_slots == 0) break;
    // when new job is already alloted
    if (slots[arr[i].deadline] != 0) break;
    slots[arr[i].deadline -1] = arr[i].id;
    profit += arr[i].profit;
    avl_slots -= 1;
  }  
  printf("Profit of %d when following job sequence is chosen\n",profit);
  for (int i = 0; i < MAX_SLOT; i++)
    printf("Slot %d to %d: Job %d\n", i, i+1, slots[i]);  
}
