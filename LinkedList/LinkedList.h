//
// Created by wassim on 18/01/18.
//

#ifndef PCB_H
#define PCB_H

#include "../PCB/PCB.h"

#endif

typedef struct _linked_list {
    PCB data;
    struct _linked_list *next;
} LinkedList;


void append(LinkedList **head, PCB d);