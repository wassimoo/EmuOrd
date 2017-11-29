//
// Created by wassim on 25/11/17.
//

#ifndef QUEUE_H
#define QUEUE_H

#include "../QUEUE/QUEUE.h"

#endif

#ifndef STDIO_H
#define STDIO_H

#include <stdio.h>

#endif

#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>

#endif

#ifndef STRING_H
#define STRING_H

#include <string.h>

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

Date extractDate(char *stringedDate);