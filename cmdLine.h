//
// Created by hanyuan on 11/3/20.
// Team member: Hanyuan Wu, Zhihao Shu


#ifndef CS537_P3_CMDLINE_H
#define CS537_P3_CMDLINE_H
#include "537make.h"

typedef struct Cmd {
    int argc;
    int lineNum;
    char inRed, outRed; // 0/1 flags, 0 means not redirect
    char* argv[MAX_LINE];
    char rawStr[MAX_LINE];
    char inFile[MAX_LINE], outFile[MAX_LINE];
    char errMsg[MAX_LINE];
    struct Cmd* next;
} Cmd;


void cmdExec(Cmd* cmd);

#endif //CS537_P3_CMDLINE_H
