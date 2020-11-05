//
// Created by hanyuan on 11/3/20.
//

#ifndef CS537_P3_CMDLINE_H
#define CS537_P3_CMDLINE_H
#include "537make.h"

typedef struct Cmd {
    int argc;
    int rowPos;
    char inRed, outRed; // 0/1 flags, 0 means not redirect
    char* argv[MAX_LINE];
    char rawStr[MAX_LINE];
    char inFile[MAX_LINE], outFile[MAX_LINE];
    char errMsg[MAX_LINE];
} Cmd;


int cmdExec(Cmd* cmd);

#endif //CS537_P3_CMDLINE_H
