//
// Created by hanyuan on 11/3/20.
// Team member: Hanyuan Wu, Zhihao Shu


#ifndef CS537_P3_GRAPH_H
#define CS537_P3_GRAPH_H
#include "537make.h"
#include "cmdLine.h"

// We don't necessarily implement the whole graph, in fact, we don't have to remove any vertices/edges

typedef struct Vertex{
    int hasEdgeIn;
    int isTarget;
    int adjNum;
    int lineNum;
    int updated;
    int visited;
    int size;
    long time;
    char fromLine[MAX_LINE];
    char name[MAX_LINE];
    Cmd* cmdHead;
    Cmd* cmdLines;
    struct Vertex** adj;
    struct Vertex* next;
} Vertex;


typedef struct Graph{
    int nVertices;
    int size;
    Vertex** vertices;
} Graph;

Vertex* findVertexFromName(const char* name, Graph* graph);
void addVertex(Vertex* vertex, Graph* graph);
void addEdge(Vertex* source, Vertex* target);
void freeGraph(Graph* graph);
void checkCycle(Graph* graph);



#endif //CS537_P3_GRAPH_H
