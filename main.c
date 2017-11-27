#ifndef STDLIB_H
#define STDLIB_H

#endif

#ifndef STDIO_H
#define STDIO_H

#include <stdio.h>
#endif

#ifndef TEXT_H
#define TEXT_H
#include "IO/TextFileUtilities.h"
#endif

int main(int argc, char **argv) {
    stringNode *lines = NULL;

    getLines(openFile(argv[1], "r"), &lines);
    elimComments(&lines);
    return 0;
}