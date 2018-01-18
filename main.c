#ifndef MAIN_H
#define MAIN_H
#include "main.h"

#endif

#ifndef EMUORD_FIFO_H
#define EMUORD_FIFO_H

#include "Displines/FIFO/FIFO.h"

#endif
int main(int argc, char **argv) {
    stringNode *lines = NULL;
    getLines(openFile(argv[1], "r"), &lines);
    elimComments(&lines);
    enqueueProc(lines);

    exec();
    return 0;
}