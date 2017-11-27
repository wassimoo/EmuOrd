//
// Created by wassim on 25/11/17.
//

#include "TextFileUtilities.h"


procQueue *rear;
procQueue *front;

// Having all file lines in pointer to pointer **node,
// elimComments eliminates all comments including inline comments.
void elimComments(stringNode **node) {
    // '#' introduces full line comment,
    // '<' & '>' introduces Multi-inline comments
    stringNode *cpy = (stringNode *) malloc(sizeof(stringNode));

    cpy = *node;
    int deletedNode = 0; // deletedNode flag to avoid skipping one node after deletion
    int onComment = -1; // onComment index to indicate if current char is currently commented (-1 not commented, other index of first char comment in line)

    while (cpy->next != NULL) {
        int i = 0;
        while (cpy->line[i] != '\0') {
            //Full line Comment
            if (cpy->line[i] == '#') {
                if (i + 1 == 1) {
                    //line is Empty so we delete it
                    stringNode *p = *node;
                    *node = (*node)->next;
                    cpy = *node;
                    free(p);
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

    while ((linelen = getline(&line, &linecap, fp)) != -1) {
        if (linelen && (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
            line[--linelen] = '\0';
        new->line = strdup(line);
        new->next = (stringNode *) malloc(sizeof(stringNode));
        new = new->next;
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

procQueue *getproc(char *lines[], int numLine) {
    front = NULL;
    rear = NULL;

    int i;
    for (i = 0; i < numLine; i++) {
        //TODO : left from here
    }
}
