//
// Created by hanyuan on 11/3/20.
// Team member: Hanyuan Wu, Zhihao Shu


#ifndef CS537_P3_MAKEPARSER_H
#define CS537_P3_MAKEPARSER_H
#include "537make.h"
#include "graph.h"

void makeInit(const char* makefile, char* target);
int make(Vertex* vertex, Graph* graph);
long getTime(const char* name);
void checkNull(FILE* fp);
void makeParse(FILE* fp, char* tgtName, Graph* graph);
#endif //CS537_P3_MAKEPARSER_H
