#ifndef A8_QUEUE
#define A8_QUEUE
#include "binary_search_tree.h"
// data structure for storing node of the bst and encapsulating as node of the queue
typedef struct qnode{
    node_t* data; // node_t is the node of bst
    struct qnode* next;
}qnode_t;

extern qnode_t* head;
extern qnode_t* tail;

int enqueue(node_t* item);
node_t* dequeue();
void display();

#endif
