//
// Created by hanyuan on 11/3/20.
// Team member: Hanyuan Wu, Zhihao Shu

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graph.h"

/**
 * Simply find a vertex in graph by its name
 * @param name the vertex name (usually a target name or file name)
 * @param graph the graph to search
 * @return the vertex found, NULL if not found
 */
Vertex* findVertexFromName(const char* name, Graph* graph){
    for(int i=0; i<graph->nVertices;i++){
        if(strncmp(graph->vertices[i]->name, name, MAX_LINE) == 0){
            return graph->vertices[i];
        }
    }
    return NULL;
}

/**
 * Adding a vertex to the graph and incrementing the number of vertex
 * @param vertex the vertex to be added
 * @param graph the graph to add vertex into
 */

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

/**
 * add an edge from source to target, using the adjacent array in vertex
 * @param source from this vertex
 * @param target to this vertex
 */
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
 * Private, recursive helper for cycle checking
 * @param curVet the current vertex being checked
 */
void cycleHelperRec(Vertex* curVet){
    if(curVet->visited == 1){
        fprintf(stderr, "%d: Cycle detected in makefile: %s\n",
                curVet->lineNum, curVet->fromLine);
        exit(1);
    }
    if(curVet->visited == 2) return;
    curVet->visited = 1;
    for(int i = 0; i < curVet->adjNum; i++){
        cycleHelperRec(curVet->adj[i]);
    }
    curVet->visited = 2;

}

/**
 * Check if any cycle in the graph, if so, exit the program immediately
 * @param graph the graph to be checked
 */
void checkCycle(Graph* graph){
    int j = 0;
    Vertex** rootList = (Vertex**)malloc(sizeof(Vertex*)*graph->nVertices);
    for(int i = 0; i < graph->nVertices; i++){
        if(graph->vertices[i]->hasEdgeIn == 0){
            rootList[j] = graph->vertices[i];
            j++;
        }
    }
    if(j == 0 && graph->nVertices != 0){
        fprintf(stderr, "%d: Cycle detected in makefile: %s\n",
                graph->vertices[0]->lineNum, graph->vertices[0]->fromLine);
        exit(1);
    }
    for(int i = 0; i < j; i++){
        cycleHelperRec(rootList[i]);
    }
    free(rootList);
    rootList = NULL;
}







