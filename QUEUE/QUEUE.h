//
// Created by wassim on 25/11/17.
//
#ifndef STDIO_H
#define STDIO_H

#include <stdio.h>

#endif

#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>

#endif

#ifndef PCB_H
#define PCB_H

#include "../PCB/PCB.h"

#endif

typedef struct procqueue {
    PCB current;
    struct procqueue *next;
} procQueue;

// Two glboal variables to store address of front and rear nodes.

extern procQueue *front;
extern procQueue *rear;

// To Enqueue a PCB.
void Enqueue(PCB new);

// To Dequeue a PCB.
void Dequeue();

//get front
PCB *getFront();