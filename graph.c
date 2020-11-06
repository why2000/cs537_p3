//
// Created by hanyuan on 11/3/20.
// Zhihao Shu
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


/*
 create a graph using adjacent list
 structure:
 graph(v){
    header->node1->node2->..
    header->node1->->node2..
    header->node1->node2..
    .
    .
 }

 #v nodes in total in this graph
 */



Vertex* findVertexFromName(char* name, Graph* graph){
    for(int i=0; i<graph->nVertices;i++){
        if(graph->vertices[i].name == name){
            return graph->vertices[i];
        }
    }
    //stderr("cannot find the vertex");
    return 0;
}

//adding a vertex to the graph and incrementing the number of vertex
void addVertex(Vertex* vertex, Graph* graph){
    //check duplicate
    for(int i=0; i<graph->nVertices; i++){
        if(graph->vertices[i].name == vertex->name){
           // printf("vertex already in the graph");
            return;
        }
    }
    //initialize graph and add the first vertex
    if(graph->nVertices == 0){
        graph->vertices = (Vertex**)malloc(sizeof(Vertex)*graph->size);
        graph->vertices[0] = vertex;
        graph->nVertices++;
        return;
    }
    int *count = graph->nVertices;
    count++;
    //resize the vertices
    if(count >= 0.9*graph->size){
        graph->vertices = realloc(graph->vertices, 2*graph->size);
        graph->size *= 2;
    }
    graph->vertices[count] = vertex;
}


void addEdge(Vertex* source, Vertex* target, Graph* graph){
    Vertex *ptr = NULL;
    Vertex *ptrT = NULL;
    for(int i=0;i<graph->nVertices;i++){
        if(source->name == graph->vertices[i].name){
            ptr = graph->vertices[i];
        }
        if(target->name == graph->vertices[i].name){
            ptrT = graph->vrtices[i];
        }
    }
    //if source is not in the graph
    if(ptr == NULL){
        addVertex(source,graph);
    }
    //if target is not in the graph
    if(ptrT = NULL){
        addVertex(target,graph);
    }
    //redo the finding
    for(int i=0;i<graph->nVertices;i++){
        if(source->name == graph->vertices[i].name){
            ptr = graph->vertices[i];
        }
        if(target->name == graph->vertices[i].name){
            ptrT = graph->vrtices[i];
        }
    }
        
    //initialize vertex adj and add the first edge
    if(ptr->adjNum == 0){
        ptr->adj = (Vertex**)malloc(sizeof(Vertex)*(ptr->size/4));
        ptr->adj[0] = target;
        ptr->adjNum++;
        ptr->HNum++;
        return;
    }
    int *count = ptr->adjNum;
    count++;
    ptr->HNum++;
    if(ptr->adjNum >= 0.9*ptr->size){
        ptr->adj = realloc(ptr->adj, 2*ptr->size);
        ptr->size *= 2;
    }
    ptr->adj[count] = target;
}

//check if src contains target
bool contains(Vertex* src, Vertex* target){
    for(int i=0;i<src->adjNum;i++){
        if(src->adj[i].name == target->name){
            return true;
        }
    }
    return false;
}

//add the target to the end of the chain
void addV(Vertex* src, Vertex* target){
    Vertex* ptr = src;
    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = target;
}



//too slow > O(n^2)
Vertex* postTranversal(Vertex* vertex, Graph* graph){
    Vertex* list;
    //Vertex** list2 = (Vertex**)malloc(sizeof(Vertex)*graph->nVertices);
    //initialize the graph to false
    for(int i=0;i<graph->nVertices;i++){
        graph->vertices[i].visited = false;
    }
    //find the vertex with no children
    for(int i=0;i<graph->nVertices;i++){
        if(graph->vertices[i].HNum == 0){
            list = graph->vertices[i];
            list.visited = true;
            continue;
        }
    }
    if(list == NULL){
        //printf("there is a cycle");
        return;
    }
    //decrement HNum for each node that contains the end node
    for(int i=0; i<graph->nVertices;i++){
        if(contains(graph->vertices[i],list)){
            graph->vertices[i].HNum--;
        }
    }
    //find the next node with HNum == 0 and not visited
    int count = 1;
    while(count < graph->nVertices){
        //adding next qualified node
        Vertex* temp;
        for(int i=0;i<graph->nVertices;i++){
            if(graph->vertices[i].HNum == 0 && !graph->vertices[i].visited){
                temp = graph->vertices[i];
                addV(list,temp);
                temp.visited = true;
                continue;
            }
        }
        if(temp == NULL){
            //printf("cycle detected!");
            return;
        }
        //decrement HNum for each node that contains the node that just added
        for(int i=0; i<graph->nVertices;i++){
            if(contains(graph->vertices[i],temp) && !graph->vertices[i].visited){
                graph->vertices[i].HNum--;
            }
        }
        
        count++;
    }
    return list;
    
    
}


//struct to create a new node
//Node* newNode(char* const v){
//    Node* nodes = (Node*)malloc(sizeof(Node));
//    nodes->next = NULL;
//    snprintf(nodes->value, MAX_LINE,"%s", v);
//    return nodes;
//}
//
////struct to create a new node list
//Graph* newGraph(int v){
//    Graph* graph = (Graph*)malloc(sizeof(Graph));
//    graph->NumNode = v;
//
//    //create a node list with #of node v
//    graph->list = (Nodelist*)malloc(sizeof(Nodelist)*v);
//
//    //initializing the list
//    for(int i=0;i<v;i++){
//        graph->list[i].head = NULL;
//    }
//
//
//    return graph;
//}
//
////add a node to the node list
//void addNode(Graph* graph, char* const src){
//    Node* nodex = newNode(src);
//    int numv = graph->NumNode;
//    //struct node* ptr = graph->list->head;
//    //add the node at first if the graph is empty
//    for(int i=0;i<numv;i++){
//        if(graph->list[i].head == NULL){
//            graph->list[i].head = nodex;
//            return;
//        }
//    }
//    printf("node size not enough");
//
//
//}
//
//// Adds an edge to an undirected graph
//void addEdge(Graph* graph, char* const src, char* const dest)
//{
//    // Add an edge from src to dest.  A new node is
//    // added to the adjacency list of src.  The node
//    // is added at the beginning
//    Node* nodex = newNode(dest);
//    for(int i=0;i<graph->NumNode;i++){
//        if(graph->list[i].head->value == src){
//            Node* ptr = graph->list[i].head;
//            while(ptr->next != NULL){
//                ptr = ptr->next;
//            }
//            ptr->next = nodex;
//            continue;
//        }
//    }
//
//    // Since graph is undirected, add an edge from
//    // dest to src also
//    nodex = newNode(src);
//    for(int i=0;i<graph->NumNode;i++){
//        if(graph->list[i].head->value == dest){
//            Node* ptr = graph->list[i].head;
//            while(ptr->next != NULL){
//                ptr = ptr->next;
//            }
//            ptr->next = nodex;
//            continue;
//        }
//    }
//
//}



