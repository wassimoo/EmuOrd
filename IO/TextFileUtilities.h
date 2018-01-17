//
// Created by wassim on 25/11/17.
//
#ifndef PCB_H
#define PCB_H
#include "../PCB/PCB.h"
#endif

typedef struct stringnode {
    char *line;
    struct stringnode *next;
} stringNode;

FILE *openFile(char *path, char *mode);

void getLines(FILE *fp, stringNode **node);

void elimComments(stringNode **node);

void enqueueProc(stringNode *node);

int nextWord(char **c, char sep);

Date extractDate(char **stringedDate);

void deleteNode(stringNode **head, stringNode **node);

stringNode *seekPrev(stringNode *head, stringNode *node);