

//TODO : define as needed (#IFNDEF)
#include "IO/TextFileUtilities.h"


int main(int argc, char **argv) {
    //openFile(argv[1]);
    getproc(argv, argc);
    return 0;
}

/*char** openFile(char *fileName){
    FILE *fp ;
    if(! (fp = fopen(fileName,"r")))
        return NULL;

    char** fileLines;
    char* line = NULL;
    ssize_t linelen = 0;


}*/