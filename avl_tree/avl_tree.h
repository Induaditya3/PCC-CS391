#ifndef AVL_TREE
#define AVL_TREE

// data structure for storing the nodes of the avl tree
typedef struct node{
    int h; // height of the node
    int data; // data to be stored - it should be comparable
    struct node* parent; // parent node of current node
    struct node* left; // left child of current node
    struct node* right; // right child of current node
}node_t;
// we can also store store balance factor(bf) but
// we decided not do it as it changes with every insertions and deletions
// and since knowing previous bf does not help with calculation of bf when insertions or deletions occurs

// data structure for storing the root node of the avl tree
typedef struct{
    node_t *root;
}avl_t;

//allocation of structure containing root
avl_t* createAvl();
// function to return maximum height of node whose child nodes are left and right
// takes left and right nodes and which node's subtree's insertion/deletion has happened
// which_side: 0 means insertion/deletion happened in left subtree otherwise insertion/deletion happened in right node
// val : whether insertion or deletion happened- -1 means deletion and 1 means insertion
int max_height(node_t *left,node_t *right,int which_side);
// recursive function for height of the node
// for testing purpose
int height_node(node_t *node);

// inserting into avl 
// just plain insertion, no balancing
void insertAvl_inner(node_t *node, node_t *newnode);
// wrapper function for inserting into avl
// it also does necessary rotations to maintain bf between -1 and 1
void insertAvl(avl_t *avl,int data);
// for printing inorderly fashion
void printInorder(node_t *node);
// for printing in preorderly fashion
void printPreorder(node_t *node);
// for printing in postorderly fashion
void printPostorder(node_t *node);
// delete all nodes of avl
void free_nodes(node_t *node);
// free the avl 
void freeAvl(avl_t *avl);
// find the successor node's value
int successor(node_t *node,int which_child);
// for deleting specific data element if it exists
// returns address of parent node of deleted node - for updating height of nodes
node_t* deleteNode(node_t *node,int data);
// wrapper function for deleting particular node with specific value in the avl
void deleteAvl(avl_t *avl,int val);
// breadth first printing of value of nodes
void level_order_traversal(node_t *node);
#endif