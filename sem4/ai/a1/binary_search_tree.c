
#include <stdio.h>
#include <stdlib.h>

#include "binary_search_tree.h"
#include "a8_queue.h"

// allocating space for structure containing root
bst_t* createBst(){
    bst_t *bst = malloc(sizeof(bst_t));
    bst->root = NULL;
    return bst;
}

// inserting into bst
void insertBst_inner(node_t *node,node_t *new){
    if (node->data <= new->data){
        if (node->right == NULL)
            node->right = new;
        else
            insertBst_inner(node->right,new); // go to right of current node
    }
    else if (node->data > new->data){
        if (node->left == NULL)
            node->left = new;
        else
            insertBst_inner(node->left,new); // go to left of current node
    }
}
// wrapper function for inserting into bst
void insertBst(bst_t *bst,int data){
    // allocate space for new node
    node_t *new = malloc(sizeof(node_t));
    new->data = data;
    new->left = NULL;
    new->right = NULL;

    // bst is empty
    if (bst->root == NULL){
        bst->root = new;
        return;
    }
    insertBst_inner(bst->root,new);
}

// breadth first traversal
void level_order_traversal(node_t *node){
    // node which we will visit and print the value
    node_t* visit;
    enqueue(node);
    while (head != NULL){
        visit = dequeue();
        printf("%d ",visit->data);
        // check if we can visit left child of visited node
        // if so add it to left child for visiting later
        if (visit->left != NULL)
            enqueue(visit->left);
        // check similarly for right child as well
        if (visit->right != NULL)
            enqueue(visit->right);
    }  
}
int main(){
    bst_t *bst = createBst();
    int vals[] = {11,6,15,3,8,13,17,1,5,12,14,19};
    int size = sizeof(vals)/sizeof(vals[0]);
    for (int i = 0; i < size; i++)
        insertBst(bst, vals[i]);
    
    // print breadth first
    level_order_traversal(bst->root);
    return 0;
}
