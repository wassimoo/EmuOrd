//
// Created by wassim on 25/11/17.
//
#ifndef QUEUE_H
#define QUEUE_H

#include "QUEUE.h"

#endif

#include <stdlib.h>


// To Enqueue a PCB
void Enqueue(PCB new) {
    procQueue *temp =
            (procQueue *) malloc(sizeof(procQueue));
    temp->current = new;
    temp->next = NULL;
    if (front == NULL && rear == NULL) {
        front = rear = temp;
        return;
    }
    temp->next = rear;
    rear = temp;
}

// To Dequeue a PCB.
void Dequeue() {
    procQueue *temp = front;
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

