//
// Created by hanyuan on 11/4/20.
//Zhihao SHu

#include <stdlib.h>
#include <stdio.h>
#include "strProcess.h"

/**
 * Parse a string into Vertices and Edges of items
 * @param line the string to parse
 * @param graph the graph to set the vertex and edge
 * @param lineNum the index of this line
 * @return the point to first (target) Vertex that is parsed
 */
Vertex* parseTarget(const char* const line, Graph* graph, int lineNum){
    char tgtName[MAX_LINE];
    int i;
    // read target
    for(i = 0; i < MAX_LINE; i++){
        // jump
        while(line[i] == ' '||line[i] == '\t')
            i++;
        if(i > 0 && line[i] != '\n' && line[i] != '\0') {
            fprintf(stderr, "%d: Unable to parse target: %s\n", lineNum, line);
            exit(1);
        }
        if (line[i] == ':') {
            tgtName[i] = '\0';
            break;
        }
        tgtName[i] = line[i];
    }
    if(tgtName[0] == '\0' || i == MAX_LINE){
        fprintf(stderr, "%d: Unable to parse target: %s\n", lineNum, line);
        exit(1);
    }
    Vertex* target;
    if((target = findVertexFromName(tgtName, graph)) == NULL){
        target = (Vertex*)malloc(sizeof(Vertex));
        snprintf(target->name, MAX_LINE, "%s", tgtName);
    }
    addVertex(target, graph);
    // read dependencies
    while(i < MAX_LINE){
        char bufDep[MAX_LINE];
        readItem(bufDep, line, &i);
        Vertex* vet = (Vertex*)malloc(sizeof(Vertex));
        snprintf(vet->name, MAX_LINE, "%s", bufDep);
        addVertex(vet, graph);
        addEdge(target, vet, graph);
    }
    return target;

}


/**
 * Parse and fill the cmd struct from its rawStr field
 * @param cmd: the cmd struct to be parsed
 * @return the number of arguments detected
 */
int parseCmd(Cmd* const cmd){
    if(cmd->rawStr[0] == '\0' || cmd->rawStr[0] == '#')
        return 0;
    int i = 0;
    while(i < MAX_LINE){
        char ch = cmd->rawStr[i];
        if(ch == '\0'||ch=='\n')
            return cmd->argc;
        // jump spaces
        if(ch==' '||ch=='\t'){
            i++;
            continue;
        }
        // redirection
        if(ch == '>'){
            i++;
            // non-strict mode, as \0 is already checked
            readItem(cmd->outFile, cmd->rawStr, &i);
            cmd->outRed = 1;
            break;
        }
        else if(ch == '<') {
            i++;
            readItem(cmd->inFile, cmd->rawStr, &i);
            cmd->inRed = 1;
            break;
        }
        else {
            // normal args
            cmd->argv[cmd->argc] = (char*) malloc(sizeof(char) * MAX_LINE);
            readItem(cmd->argv[cmd->argc], cmd->rawStr, &i);
            cmd->argc++;
        }
    }
    return cmd->argc;
}

/**
 * read an item (string without space) out of a longer string from a given start position
 * @param target: the buffer to store the item
 * @param rawStr: the long string to be parsed
 * @param pos: the start position
 */
void readItem(char* const target, const char* const rawStr, int* pos){
    int i = *pos;
    // do a left strip
    while((rawStr[i] == ' ' || rawStr[i] == '\t') && i < MAX_LINE-1)
        i++;
    *pos = i;
    // copy item
    for(int j = 0; *pos < MAX_LINE; j++,(*pos)++){
//        if(rawStr[*pos] == '\0' && strict){
//            return 1;
//        }
        if(*pos == MAX_LINE - 1 || rawStr[*pos] == ' '
            || rawStr[*pos] == '\t' || rawStr[*pos] == '\0' || rawStr[*pos] == '\n'){
            target[j] = '\0';
            break;
        }
        target[j] = rawStr[*pos];
    }
//    return 0;
}
