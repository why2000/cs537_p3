//
// Created by hanyuan on 11/3/20.
// Team member: Hanyuan Wu, Zhihao Shu

#include <stdlib.h>
#include <string.h>
#include "graph.h"

Vertex* findVertexFromName(const char* name, Graph* graph){
    for(int i=0; i<graph->nVertices;i++){
        if(strncmp(graph->vertices[i]->name, name, MAX_LINE) == 0){
            return graph->vertices[i];
        }
    }
    //stderr("cannot find the vertex");
    return NULL;
}

//adding a vertex to the graph and incrementing the number of vertex
void addVertex(Vertex* vertex, Graph* graph){
    //check duplicate
    for(int i=0; i<graph->nVertices; i++){
        if(strncmp(graph->vertices[i]->name, vertex->name, MAX_LINE)==0){
            // printf("vertex already in the graph");
            return;
        }
    }
    //initialize graph and add the first vertex
    if(graph->nVertices == 0){
        graph->size = MAX_LINE;
        graph->vertices = (Vertex**)malloc(sizeof(Vertex*)*graph->size);
        vertex->hasEdgeIn = 0;
        graph->vertices[0] = vertex;
        graph->nVertices++;
        return;
    }

    //resize the vertices array

    if(graph->nVertices >= 0.9*graph->size){
        graph->vertices = realloc(graph->vertices, 2*graph->size);
        graph->size *= 2;
    }
    graph->vertices[graph->nVertices] = vertex;
    graph->nVertices++;
    vertex->hasEdgeIn = 0;
}


void addEdge(Vertex* source, Vertex* target){

    //initialize vertex adj and add the first edge
    if(source->adjNum == 0){
        source->size = MAX_LINE;
        source->adj = (Vertex**)malloc(sizeof(Vertex*)*(source->size));
        source->adj[0] = target;
        source->adjNum++;
        return;
    }
    if(source->adjNum >= 0.9*source->size){
        source->adj = realloc(source->adj, 2*source->size);
        source->size *= 2;
    }
    source->adj[source->adjNum] = target;
    source->adjNum++;
    target->hasEdgeIn = 1;
}

//check if src contains target
int contains(Vertex* src, Vertex* target){
    for(int i=0;i<src->adjNum;i++){
        if(strncmp(src->adj[i]->name, target->name, MAX_LINE) == 0){
            return 1;
        }
    }
    return 0;
}


/**
 * Check if any cycle in the graph, if so, exit the program immediately
 * @param graph the graph to be checked
 */
void checkCycle(Graph* graph){
    Vertex** rootList = (Vertex**)malloc(sizeof(Vertex*)*)
    for(int i = 0; i < graph->nVertices; i++){
        if()
    }
}

void freeGraph(Graph* graph){

}



