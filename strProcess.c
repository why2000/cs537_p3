//
// Created by hanyuan on 11/3/20.
// Team member: Hanyuan Wu, Zhihao Shu


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
    while(line[0] == ' '||line[0] == '\t'){
        fprintf(stderr, "%d: Space at the beginning of line: %s\n", lineNum, line);
        exit(1);
    }
    int i = 0;
    // read target
    for(; i < MAX_LINE; i++){
        // jump
        if (line[i] == ':') {
            tgtName[i] = '\0';
            i++;
            break;
        }
        if(line[i] == ' ' || line[i] == '\t'){
            tgtName[i] = '\0';
            while(line[i] != ':'){
                if(i == MAX_LINE || line[i] == '\n'){
                    fprintf(stderr, "%d: Unable to parse target: %s\n", lineNum, line);
                    exit(1);
                }
                i++;
            }
            i++;
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
        addVertex(target, graph);
    }
    target->isTarget = 1;
    target->lineNum = lineNum;
    snprintf(target->fromLine, MAX_LINE, "%s", line);
    // read dependencies
    while(i < MAX_LINE){
        if(line[i] == '\0'||line[i] == '\n')
            break;
        char bufDep[MAX_LINE];
        readItem(bufDep, line, &i);
        if(bufDep[0] == '\0') break;
        Vertex* vet;
        if((vet = findVertexFromName(bufDep, graph)) == NULL){
            vet = (Vertex*)malloc(sizeof(Vertex));
            vet->isTarget = 0;
            snprintf(vet->name, MAX_LINE, "%s", bufDep);
            addVertex(vet, graph);
        }
        addEdge(target, vet);

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
        if(ch == '>' && cmd->outRed == 0){
            i++;
            // non-strict mode, as \0 is already checked
            readItem(cmd->outFile, cmd->rawStr, &i);
            cmd->outRed = 1;
        }
        else if(ch == '<' && cmd->inRed == 0) {
            i++;
            readItem(cmd->inFile, cmd->rawStr, &i);
            cmd->inRed = 1;
        }
        else {
            // no more args
            if(cmd->inRed != 0 || cmd->outRed != 0) break;
            // normal args
            cmd->argv[cmd->argc] = (char*) malloc(sizeof(char) * MAX_LINE);
            readItem(cmd->argv[cmd->argc], cmd->rawStr, &i);
            if(cmd->argv[cmd->argc][0] == '\0') break;
            cmd->argc++;
        }
        if(cmd->inRed != 0 && cmd->outRed != 0) break;
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
        if(*pos == MAX_LINE - 1 || rawStr[*pos] == ' '
            || rawStr[*pos] == '\t' || rawStr[*pos] == '\0' || rawStr[*pos] == '\n'){
            target[j] = '\0';
            break;
        }
        target[j] = rawStr[*pos];
    }
//    return 0;
}