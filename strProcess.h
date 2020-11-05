//
// Created by hanyuan on 11/4/20.
//

#ifndef CS537_P3_STRPROCESS_H
#define CS537_P3_STRPROCESS_H
#include "cmdLine.h"

int parseTarget(const char* line);
int parseCmd(Cmd* cmd);
int readItem(char* target, const char* rawStr, int* begin, int strict);

#endif //CS537_P3_STRPROCESS_H
