//
// Created by hanyuan on 11/3/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "makeParser.h"
#include "cmdLine.h"
#include "graph.h"

int main(int argc, char** argv) {
    char makeFile[MAX_LINE];
    char target[MAX_LINE];
    const int MAX_ARG = 4;
    if(argc > MAX_ARG){
        printf("Usage: 537make [-f <makefile>] [target]");
        return 1;
    }
    // very few args, no need to use getopt
    for(int i = 1; i < argc; i++){
        if((strncmp("-f", argv[i], MAX_LINE) == 0)){
            if(i == argc-1){
                printf("Usage: 537make [-f <makefile>] [target]");
                return 1;
            }
            else if(i == argc-2){
                target[0] = '\0';
                snprintf(makeFile, MAX_LINE, "%s", argv[i+1]);
                if(argc == MAX_ARG)
                    snprintf(target, MAX_LINE, "%s", argv[i-1]);
            }
            else if(i == argc-3){
                snprintf(makeFile, MAX_LINE, "%s", argv[i+1]);
                snprintf(target, MAX_LINE, "%s", argv[i+2]);
            }
            break;
        }
    }
    makeInit(makeFile, target);

    return 0;
}
