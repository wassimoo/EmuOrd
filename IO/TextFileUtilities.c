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

#ifndef STRING_H
#define STRING_H

#include <string.h>

#endif


#ifndef QUEUE_H
#define QUEUE_H

#include "../Queue/Queue.h"

#endif

#ifndef TEXT_H
#define TEXT_H
#include "TextFileUtilities.h"

#endif

#ifndef DATE_H
#define DATE_H
#include "../Date/Date.h"
#endif //DATE_H



PCBNODE *front;
PCBNODE *rear;

// Having all file lines in pointer to pointer **node,
// elimComments eliminates all comments including inline comments.
void elimComments(stringNode **node) {
    // '#' introduces full line comment,<>
    // '<' & '>' introduces Multi-inline comments
    stringNode *cpy;

    cpy = *node;
    int deletedNode = 0; // deletedNode flag to avoid skipping one node after deletion
    int onComment = -1; // onComment index to indicate if current char is currently commented (-1 not commented, other is the index of the first char comment in line)

    while (cpy) {
        int i = 0;
        if (cpy->line[i] == '\0') {
            deleteNode(node, &cpy);
            deletedNode = 1;
        }
        while (cpy->line[i] != '\0') {
            //Full line Comment
            if (cpy->line[i] == '#') {
                if (i + 1 == 1) {
                    //line is Empty so we delete it
                    deleteNode(node, &cpy);
                    deletedNode = 1;
                    break;
                } else {
                    cpy->line[i] = '\0';
                }
            }
            //MultiLine Comment
            if (cpy->line[i] == '<') {
                onComment = i;
            }
            if (cpy->line[i] == '>') {
                //shift chars left if possible
                int j = i + 1;
                while (cpy->line[j - 1] != '\0') {
                    cpy->line[onComment + j - i - 1] = cpy->line[j];
                    j++;
                }
                onComment = -1;
                //TODO : delete node if line is empty
            }
            i++;
            if (cpy->line[i] == '\0' && onComment != -1) {
                cpy->line[onComment] = '\0';
                onComment = 0;
                //TODO : delete node if line is empty (comment not yet closed)
            }
        }
        if (!deletedNode) {
            cpy = cpy->next;
        } else
            deletedNode = 0;
    }
}

// using the linkedList structure (stringNode) , getLines reads all lines
// from fp , store them in *new  linkedList and assign it to the **node pointer
void getLines(FILE *fp, stringNode **node) {
    if (!fp) return;

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    stringNode *new = (stringNode *) malloc(sizeof(stringNode));
    *node = new;
    int hasMore = 1;
    hasMore = ((linelen = getline(&line, &linecap, fp)) != -1) ? 1 : 0;
    while (hasMore) {
        if (linelen && (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
            line[--linelen] = '\0';
        new->line = strdup(line);
        if ((linelen = getline(&line, &linecap, fp)) != -1) {
            hasMore = 1;
            new->next = (stringNode *) malloc(sizeof(stringNode));
            new = new->next;
        } else
            break;
    }
}

FILE *openFile(char *path, char *mode) {
    return fopen(path, mode);
}

void closeFile(FILE **fp) {
    if (*fp != NULL) {
        fclose(*fp);
        *fp = NULL;
    }
}

void enqueueProc(stringNode *node) {
    front = NULL;
    rear = NULL;
    while(node){
        // TODO : life is not always colored, so users aren't always friendly..
        // check valid types, whether all data are present or not ...
        PCB *pcbProc = (PCB*) malloc(sizeof(PCB));
        char *lineCpy = node->line;
        int len; // pos of next char -to skip whitespaces

        /*  id   */
        len = nextWord(&lineCpy,' ');
        pcbProc->id = atoi(lineCpy);

        /*  name   */
        lineCpy += len;
        len = nextWord(&lineCpy,' ');
        pcbProc->name = strdup(lineCpy);

        /*  ioTime   */
        lineCpy += len;
        len = nextWord(&lineCpy,' ');
        pcbProc->owner = strdup(lineCpy);

        /*  priority   */
        lineCpy += len;
        len = nextWord(&lineCpy,' ');
        pcbProc->priority = atoi(lineCpy);

        /* Creation Date */
        lineCpy += len;
        len = nextWord(&lineCpy,' ');
        pcbProc->creationDate = extractDate(&lineCpy);

        /*  cpuCycles   */
        len = nextWord(&lineCpy,' ');
        pcbProc->cpuCycles = extractDate(&lineCpy);


        /*  ioTime   */
        len = nextWord(&lineCpy,' ');
        pcbProc->ioTime = extractDate(&lineCpy);

        /* Remmaining Executing Time */

        pcbProc->remExecTime = addDates(pcbProc->cpuCycles,pcbProc->ioTime);

        /* Estimated Memory Size */
        //TODO : ???

        
        pcbProc->state = NEW;
        node = node->next;

        Enqueue(*pcbProc);
    }
}

//Warning : Some real ugly code :(
 int nextWord(char **c, char sep){
     
     if(*(*c) != sep && *(*c) != '\0')
        goto nextWhite;

    //look for next non white space
    while((*c)++){
        if(*(*c) == '\0')
            return -1;
        else if(*(*c) != sep)
            break;
    }

    //look for next whitespace xD
    int i;
    nextWhite:
    i = 1;
    while(*((*c)+i) != sep && *((*c)+i) != '\0') i++;

     *((*c)+i) = '\0';

    return i;
}

// TODO : think of iterating over struct fields using pointers as they are all of same type (int)
Date extractDate(char **stringedDate){
    /*Format : MS:SS:MN:HH[:DD[:MM[:YY]]] */

    Date d = {-1,-1,-1,-1,-1,-1,-1};

    nextWord(stringedDate,':');
    d.millisecond = atoi(*stringedDate);
    *stringedDate +=2;

    nextWord(stringedDate,':');
    d.second = atoi(*stringedDate);
    *stringedDate +=2;

    nextWord(stringedDate,':');
    d.minute = atoi(*stringedDate);
    *stringedDate +=2;

    nextWord(stringedDate,':');
    d.hour = atoi(*stringedDate);
    *stringedDate +=2;

    nextWord(stringedDate, ':');
    if (**stringedDate < '0' || **stringedDate > '9')
        goto returnDate;
    //else
    d.day = atoi(*stringedDate);
    *stringedDate += 2;

    nextWord(stringedDate, ':');
    if (**stringedDate < '0' || **stringedDate > '9')
        goto returnDate;
    //else
    d.month = atoi(*stringedDate);
    *stringedDate += 2;

    nextWord(stringedDate, ':');
    if (**stringedDate < '0' || **stringedDate > '9')
        goto returnDate;
    //else
    d.year = atoi(*stringedDate);

    returnDate:
        return d;
}

void deleteNode(stringNode **head, stringNode **node) {
    stringNode *tmp;
    if (!*head)
        return;
    if (*head == *node) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
        *node = *head;
        return;
    }

    stringNode *prev = seekPrev(*head, *node);
    tmp = prev->next;
    prev->next = (*node)->next;
    free(tmp);
    *node = prev->next;
}

stringNode *seekPrev(stringNode *head, stringNode *node) {
    if (!head) return NULL;

    while (head) {
        if (head->next == node)
            return head;
        head = head->next;
    }
}