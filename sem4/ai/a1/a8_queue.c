
// queue implemented through linked list
// head node represents front of the queue 
// tail node represents rear of the queue

/*------------------------------------IT WILL BE USED IN PERFORMING BFS-------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "a8_queue.h"
#include "binary_search_tree.h"


qnode_t* head = NULL;
qnode_t* tail = NULL;

int enqueue(node_t* item){
    qnode_t* temp = malloc(sizeof(qnode_t));
    if (!temp){
        perror("malloc");
        return 0;
    }
    temp->data = item;
    temp->next = NULL;

    // case where the append happens when ll is empty
    // we handle it as - we initialize the head and make tail equal to head
    if (!head){
        head = temp;
        tail = head;
        return 1;
    }
    // when the there is one element in the ll 
    // we make new element a tail node and connect head to tail 
    if (head == tail){
        tail = temp;
        head->next = tail;
    }
    // ll contains more than one element
    // connect tail to new element node and make new node the tail node
    else {
        tail ->next = temp;
        tail = temp;
    }
    return 1;
}
node_t* dequeue(){
    node_t* val;
    // there is no element
    // !head is also enough
    if (!head ){
        return 0; // means empty
    }
    // there is only one element
    if (head == tail){
        val = head->data;
        free(head); // freeing head also frees tail as they point to same thing
        head = NULL, tail = NULL;
    }
    // more than one element
    else {
        qnode_t* temp = head;
        head = head->next;
        val = temp->data;
        free(temp);
    }
    return val;
}
void display(){
    if (!head){
        puts("Empty");
        return;
    }
    for (qnode_t* trav = head; trav != NULL; trav = trav->next){
        if (trav == tail)
            printf("%d\n",trav->data->data);
        else
            printf("%d <- ",trav->data->data);
    }
}
