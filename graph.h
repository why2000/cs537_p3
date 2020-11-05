//
// Created by hanyuan on 11/3/20.
//

#ifndef CS537_P3_GRAPH_H
#define CS537_P3_GRAPH_H

typedef struct Node{
    char* value;
    struct Node* next;
} Node;

typedef struct Nodelist{
    Node* head;

} Nodelist;


typedef struct Graph{
    int NumNode;
    Nodelist* list;
} Graph;

#endif //CS537_P3_GRAPH_H
