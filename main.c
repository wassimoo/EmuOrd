#include "main.h"

int main(int argc, char **argv) {
    stringNode *lines = NULL;

    getLines(openFile(argv[1], "r"), &lines);
    elimComments(&lines);
    enqueueProc(lines);
    return 0;
}