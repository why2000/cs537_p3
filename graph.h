//
// Created by hanyuan on 11/3/20.
//

#ifndef CS537_P3_GRAPH_H
#define CS537_P3_GRAPH_H
#include "537make.h"
#include "cmdLine.h"

// We don't necessarily implement the whole graph, in fact, we don't have to remove any vertices/edges

typedef struct Vertex{
    int cmdNum;
    int adjNum;
    char name[MAX_LINE];
    Cmd* cmdHead;
    Cmd* cmdLines;
    struct Vertex** adj;
    struct Vertex* next;
} Vertex;


typedef struct Graph{
    int nVertices;
    Vertex** vertices;
} Graph;

Vertex* findVertexFromName(char* name, Graph* graph);
void addVertex(Vertex* vertex, Graph* graph);
void addEdge(Vertex* source, Vertex* target, Graph* graph);
Vertex** getAdjacentVerticesOf(char* name, Graph* graph);
Vertex* postTranversal(Vertex* vertex, Graph* graph);
void freeGraph(Graph* graph);




#endif //CS537_P3_GRAPH_H
