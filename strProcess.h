//
// Created by hanyuan on 11/3/20.
// Team member: Hanyuan Wu, Zhihao Shu


#ifndef CS537_P3_STRPROCESS_H
#define CS537_P3_STRPROCESS_H
#include "cmdLine.h"
#include "graph.h"


Vertex* parseTarget(const char* line, Graph* graph, int lineNum);
int parseCmd(Cmd* cmd);
void readItem(char* target, const char* rawStr, int* begin);

#endif //CS537_P3_STRPROCESS_H
