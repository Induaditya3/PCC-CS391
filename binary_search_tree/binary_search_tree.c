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
// printing elements of the bs tree by traversing inorderly
void printInorder(node_t *node){
    // node is empty
    if (node == NULL) return;
    // traverse to left of bst
    printInorder(node->left);
    // print current node's value
    printf("%d ",node->data);
    // traverse right of bst
    printInorder(node->right);
}
// printing elements of the bs tree by traversing preorderly
void printPreorder(node_t *node){
    // node is empty
    if (node == NULL) return;
    printf("%d ",node->data);
    // traverse left of the current node
    printPreorder(node->left);
    // traverse right of the current node
    printPreorder(node->right);
}
// printing elements of the tree by traversing postorderly
void printPostorder(node_t *node){
    // node is empty
    if (node == NULL) return;
    // traverse left subtree of current node
    printPostorder(node->left);
    // traverse right subtree of current node
    printPostorder(node->right);
    // print value of current node
    printf("%d ",node->data);
}
// delete whole bst
void free_node(node_t *node){
    // base case- current node is a leaf
    if (node->left == NULL && node->right == NULL)
        free(node);
    
    // current node has only left subtree
    else if (node->left != NULL && node->right == NULL){
        free_node(node->left);
        free(node);
    }
    // current node has only right subtree
    else if (node->right != NULL && node->left == NULL) {
        free_node(node->right);
        free(node);
    }
    // free both left and left subtree
    else {
        free_node(node->left);
        free_node(node->right);
        free(node);
    }
}
// free the bst
void freeBst(bst_t *bst){
    // when space for bst is not allocated
    if (bst == NULL) return;
    // free all nodes of the bst
    free_node(bst->root);
    // free the bst's data structure
    free(bst);
}
// for finding successor node's value
int successor(node_t *node, int which_child){
    // when which_child is 0 then we find left successor
    // else we find right successor
    node_t *trav;
    if (which_child == 0){
        // find the node with largest value in the left subtree
        trav = node->left;
        if (trav->right == NULL) // when left subtree has no right node
            return trav->data;
        while (trav->right->left != trav->right->right) // both nodes will point to same address when both of them is NULL
            trav = trav->right;
    }
    else {
        // find the node with smallest value in the right subtree
        trav = node->right;
        if (trav->left == NULL) // when right subtree has no left node
            return trav->data;
        while (trav->left->left != trav->left->right)
            trav = trav->left;
    }
    return trav->data;
}

// delete particular data element if it exists
void deleteNode(node_t *node,int data){
    // check if null node
    if (node == NULL){
        puts("No such element\nNo deletion possible");
        return;
    }
    // node to be deleted is leaf node
    
    // required node is in the left subtree
    if (node->left != NULL && node->left->data == data && node->left->left == NULL && node->left->right == NULL){
        // free the node containing the required data and set the parent node 's left to null
        free(node->left);
        node->left = NULL;
    }
    // required node is in the right node
    else if (node->right != NULL && node->right->data == data && node->right->left == NULL && node->right->right == NULL){
        // free the node containing the required data and set the parent node 's right to null
        free(node->right);
        node->right = NULL;
    }
    // node to be deleted has left subtree only
    
    // required node is in the left 
    else if (node->left != NULL && node->left->data == data &&  node->left->left != NULL && node->left->right == NULL){
        node_t *deleted = node->left;
        // point current's node left to deleted node's left
        node->left = deleted->left;
        free(deleted);
    }
    // required node is in the right 
    else if (node->right != NULL && node->right->data == data && node->right->left != NULL && node->right->right == NULL){
        node_t *deleted = node->right;
        // point current's node right to deleted node's left
        node->right = deleted->left;
        free(deleted);
    }
    // node to be deleted has right subtree only
    
    // required node is in the left 
    else if (node->left != NULL && node->left->data == data &&  node->left->left == NULL && node->left->right != NULL){
        node_t *deleted = node->left;
        // point current's node left to deleted node's right
        node->left = deleted->right;
        free(deleted);
    }
    // required node is in the right 
    else if (node->right != NULL && node->right->data == data && node->right->left == NULL && node->right->right != NULL){
        node_t *deleted = node->right;
        // point current's node right to deleted node's left
        node->right = deleted->right;
        free(deleted);
    }
    // node to be deleted has both left and right subtrees
    else if (node->data == data && node->left != NULL && node->right != NULL){
        // find left or right successor - we choose right successor - because we wanna be right ;)
        // then we set current node's value with its successor, then we delete the successor, by calling this function recursively
        int successor_val = successor(node,1);
        node->data = successor_val;
        // edge case : the node's immediate right child is successor - because we are considering right child as successor
        if (node->right->data == successor_val){
            node_t *deleted = node->right;
            node->right = deleted->right;
            free(deleted);
            return;
        }
        deleteNode(node->right,successor_val);
    }
    // traverse the tree to find the node to be deleted
    else {
        if (node->data < data) deleteNode(node->right,data);
        else deleteNode(node->left,data);
    }
}
// wrapper function for deleting particular node with specific value in the bst
void deleteBst(bst_t *bst, int val){
    // root node is to be deleted which is also leaf node
    if (bst->root->data == val && bst->root->left == bst->root->right){
        free(bst->root);
        bst->root = NULL;
        return;
    }
    deleteNode(bst->root,val); // need to dive into bst
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
    insertBst(bst,11);
    insertBst(bst,6);
    insertBst(bst,15);
    insertBst(bst,3);
    insertBst(bst,8);
    insertBst(bst,13);
    insertBst(bst,17);
    insertBst(bst,1);
    insertBst(bst,5);
    insertBst(bst,12);
    insertBst(bst,14);
    insertBst(bst,19);

    // deleteBst(bst,1);
    // deleteBst(bst,15);
    // deleteBst(bst,17);
    // deleteBst(bst,6);
    printInorder(bst->root);
    puts("");
    printPostorder(bst->root);
    puts("");
    printPreorder(bst->root);
    printf("\n\n\n");
    // print breadth first
    level_order_traversal(bst->root);
    freeBst(bst);
    return 0;
}