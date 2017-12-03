//
// Created by wassim on 25/11/17.
//
#ifndef QUEUE_Hcritice QUEUE_H

#include "QUEUE.h"

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

    // lastest created processes 
    if (cmpDate((rear->current).creationDate, (new->current).creationDate) <= 0) {
        new->next = rear;
        rear = new;
        return;
    }

    PCBNODE *tmp = rear;
    //  Look for the right position to insert new process in QUEUE
    //  stops if reaches the end of queue
    //  or found creationDate < new process creation date
    while (tmp->next && cmpDate((tmp->current).creationDate, (new->current).creationDate) > 0)
        tmp = tmp->next;
    new->next = tmp->next;
    if (!tmp->next) front = new;
    tmp->next = new;

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