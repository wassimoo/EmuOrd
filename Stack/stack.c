#ifndef _STACK
#define _STACK 
#include "stack.h"
#endif


//  Push(), Insert one node at the head
//  of LinkedList , and change the head pointer
void push(PCBNODE **head, PCB pcb){
    PCBNODE *new = (PCBNODE *) malloc(sizeof(PCBNODE));
    new->process = pcb;
    new->next = *head;
    *head = new;
}

//  Pop(), Returns header Node
//  of LinkedList , & free  it's space.
void pop(PCBNODE **head, PCB* pcb){
    if(! *head)
        return;

    *pcb= (*head)->process;
    PCBNODE *tmp = *head;
    *head = (*head)->next;
    free(tmp);
}