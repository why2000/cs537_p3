//
// Created by hanyuan on 11/4/20.
//

#ifndef CS537_P3_MAKEPARSER_H
#define CS537_P3_MAKEPARSER_H
#include "537make.h"
#include "graph.h"

void makeInit(const char* makefile, char* target);
void make(Vertex* targets);
#endif //CS537_P3_MAKEPARSER_H
