#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>

#endif

#ifndef QUEUE_H
#define QUEUE_H
#include "../Queue/Queue.h"

#endif

typedef struct execgraph{
    PCB process;
    int execTime; //in milliseconds
    struct execgraph *next;
}execGraph;

void insertHead(execGraph **head, PCB process, int execTime);
void insert(execGraph **head, PCB process, int execTime);