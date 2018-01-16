/* LIFO */

//Approach : Add recent element as the header

#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>

#endif


#ifndef PCB_H
#define PCB_H

#include "../PCB/PCB.h"

#endif


typedef struct pcbnode {
    PCB process;
    struct pcbnode *next;
} PCBNODE;

void push(PCBNODE **head, PCB pcb);

void pop(PCBNODE **head, PCB* pcb);