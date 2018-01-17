#ifndef _GRAPH
#define _GRAPH
#include "processExecGraph.h"
#endif



void insertHead(execGraph **head, PCB process, int execTime){
    execGraph *new = (execGraph *) malloc(sizeof(execGraph));
    new->process = process;
    new->execTime = execTime;
    new->next = NULL;

    if(!*head){
        *head = new;
        return;
    }
    new->next = *head;
    *head = new;
}

void insert(execGraph **head, PCB process, int execTime){
    if(!*head){
        insertHead(head,process,execTime);
        return;
    }
    execGraph *new = (execGraph *) malloc(sizeof(execGraph));
    new->process = process;
    new->execTime = execTime;
    new->next = NULL;

    execGraph *current = *head;
    //point last
    while(current->next)
        current = current->next;

    current->next = new;
}