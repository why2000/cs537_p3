//
// Created by hanyuan on 11/3/20.
//
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



