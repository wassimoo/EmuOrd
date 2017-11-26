#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>
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
    openFile(argv[1]);
    return 0;
}

char** openFile(char *fileName){
    FILE *fp ;
    if(! (fp = fopen(fileName,"r")))
        return NULL;

    char** fileLines;
    char* line = NULL;
    ssize_t linelen = 0;
    //TODO : continue from here 
    
}
