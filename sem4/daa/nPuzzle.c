// branch and bound strategy used for solving n Puzzle problem
// it can solve max of 15 puzzle problem, i.e. it supports 4x4 tile board
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 1000

typedef struct{
  int64_t state; // hashed state
  char act;
  int val;
}act_val;

char solution[MAX_LENGTH];
int top = 0;

int cmpActs(const void *a, const void *b){
  int vala = ((act_val*)a)->val;
  int valb = ((act_val*)b)->val;
  return vala - valb;
}

char opposite(char act){
  if (act =='u') return 'd';
  if (act =='d') return 'u';
  if (act == 'l') return 'r';
  if (act =='r') return 'l';
  return ' ';
}

// misplaced tile heuristic function
int value(int n, int board[n][n]){
  int sum = 0;
  int incorrect = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      sum++;
      // bottom right cell must be zero
      if (i == n-1 && i == n-1 && board[i][j] == 0) break; 
      if (sum != board[i][j])
        incorrect++;
    }
  }
  return incorrect;
}

// manhatten distance heuristic function
int value2(int n, int board[n][n]){
  int sum = 0;
  return 0;
}
// moves the blank cell and modifies i, j to reflect new position of blank cell
// return 0 if move made, -1 if illegal move is made
int move(int n, int board[n][n], char act, int* i, int* j){
  int old_i = *i;
  int old_j = *j;
  int temp;
  if (act =='u' && old_i -1 >= 0)
    *i = old_i -1;
  else if (act == 'd' && old_i +1 < n)
    *i = old_i +1;
  else if (act == 'l' && old_j-1 >= 0)
    *j = old_j -1;
  else if (act == 'r' && old_j +1 < n)
    *j = old_j +1;
  else {
    printf("Not valid action. So no action taken!\n");
    return -1;
  }
  temp = board[old_i][old_j];
  board[old_i][old_j] = board[*i][*j];
  board[*i][*j] = temp;
  return 0;
}

void print_solution(){
  printf("Start of solution! \n");
  for (int i = 0; i < top; i++){
    printf("%c\n", solution[i]);
  }
  printf("End of solution! \n");
}
void solve(int n, int board[n][n], char prev_act, int i, int j){
  if (value(n, board) == 0){
    print_solution();
    return;
  }
  act_val actions[4];
  int no_actions = 0;
  
  // find merits of all actions
  char available_acts[] = {'u','d','l','r'};
  char act;
  for (int k = 0; k < 4; k++){
    act = available_acts[k];
    printf("%c %c %d\n",act, opposite(act),k);
    if (prev_act != opposite(act) && move(n, board, act, &i, &j) == 0){
      actions[no_actions++] = (act_val){.act = act, .val = value(n, board)};
      move(n, board, opposite(act), &i, &j);
    }
  }

  // sort the actions based on value in ascending
  qsort(actions, no_actions, sizeof(act_val), cmpActs);

  // make most promising moves first
  for (int k = 0; k < no_actions; k++){
    move(n, board, actions[k].act, &i, &j);
    solution[top++] = actions[k].act;
    solve(n, board, actions[k].act, i, j);
    top--;
    move(n, board, opposite(actions[k].act), &i, &j);
  }
}

int main(){
  enum {n = 4};
  
  int board[n][n] = {
    {3, 5, 4, 10},
    {13, 7, 12, 1},
    {0, 15, 6, 11},
    {8, 9, 14, 2}
  };
  
  solve(n, board, ' ', 2, 0);
  return 0;
}
