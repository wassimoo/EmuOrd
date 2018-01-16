//
// Created by wassim on 25/11/17.
//
#ifndef QUEUE_H
#define QUEUE_H

#include "Queue.h"

#endif


// To Enqueue a PCB
void Enqueue(PCB new_pcb) {
    PCBNODE *new =
            (PCBNODE *) malloc(sizeof(PCBNODE));
    new->current = new_pcb;
    new->next = NULL;
    //Queue is Empty
    if (front == NULL && rear == NULL) {
        front = rear = new;
        return;
    }
    
    PCBNODE *tmp = front;
    PCBNODE *prev = (PCBNODE *) malloc(sizeof(PCBNODE));
    prev->next = front;

    //  Look for the right position to insert new process in Queue
    //  stops if reaches the end of queue
    //  or found creationDate > new process creation date

    for(tmp,prev;
        tmp && cmpDate((tmp->current).creationDate,(new->current).creationDate)<0;
        tmp=tmp->next, prev= prev->next);

    if(!tmp){ //rear
        rear->next = new;
        new->next = NULL;
        rear = new;
    }
    else if(tmp == front){ //front
        new->next = front;
        front = new;
    }
    else{
        prev->next = new;
        new->next = tmp;
    }
}

// To Dequeue a PCB.
void Dequeue() {
    PCBNODE *temp = front;
    if (front == NULL) {
        /* Queue is empty */
        return;
    }
    if (front == rear) {
        front = rear = NULL;
    } else {
        front = front->next;
    }
    free(temp);
}

PCB *getFront() {
    if (front == NULL)
        return NULL;

    return &front->current;
}