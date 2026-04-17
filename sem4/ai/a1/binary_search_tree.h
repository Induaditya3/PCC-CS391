
#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

// data structure for node which stores data and reference to left and right child nodes
typedef struct node{
    struct node *left;
    int data;
    struct node *right;
}node_t;

// data structure for storing root node of binary search tree
typedef struct {
    node_t *root;
}bst_t;

// allocating space for structure containing root
bst_t* createBst();
// inserting into bst
void insertBst_inner(node_t *node,node_t *newnode);
// wrapper function for inserting into bst
void insertBst(bst_t *bst,int data);
// printing elements of the bs tree by traversing inorderly
void printInorder(node_t *node);
// printing elements of the bs tree by traversing preorderly
void printPreorder(node_t *node);
// printing elements of the tree by traversing postorderly
void printPostorder(node_t *node);
// delete whole bst
void free_node(node_t *node);
// free the bst
void freeBst(bst_t *bst);
// for finding successor node's value
int successor(node_t *node, int which_child);
// delete particular data element if it exists
void deleteNode(node_t *node,int data);
// wrapper function for deleting particular node with specific value in the bst
void deleteBst(bst_t *bst, int val);

#endif
