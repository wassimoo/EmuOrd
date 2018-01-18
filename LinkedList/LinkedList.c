//
// Created by wassim on 18/01/18.
//

#ifndef EMUORD_LINKEDLIST_H
#define EMUORD_LINKEDLIST_H

#include "LinkedList.h"

#endif

#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>

#endif

#ifndef PCB_H
#define PCB_H

#include "../PCB/PCB.h"

#endif


//  Push(), Insert one node at the head
//  of LinkedList , and change the head pointer
void insertHead(LinkedList **head, PCB d) {
    LinkedList *new = (LinkedList *) malloc(sizeof(LinkedList));
    new->data = d;
    new->next = *head;
    *head = new;
}


//  Insert node at the end of LinkedList,
//  if List is empty , new node will be the head
void append(LinkedList **head, PCB d) {
    if (!*head) {
        LinkedList *new = (LinkedList *) malloc(sizeof(LinkedList));
        new->data = d;
        new->next = NULL;
        *head = new;
        return;
    }
    append(&(*head)->next, d);
}

//Returns length of linkedList
int length(LinkedList *head) {
    int n = 0;
    while (head) {
        head = head->next;
        n++;
    }
}