#ifndef MAIN_H
#define MAIN_H
#include "main.h"

#endif

int main(int argc, char **argv) {
    stringNode *lines = NULL;

    getLines(openFile(argv[1], "r"), &lines);
    elimComments(&lines);
    enqueueProc(lines);
    return 0;
}