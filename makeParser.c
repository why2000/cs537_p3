//
// Created by hanyuan on 11/4/20.
//Zhihao Shu
#include <stdio.h>
#include <stdlib.h>
#include "makeParser.h"
#include "graph.h"
#include "strProcess.h"

void makeInit(const char* const makeFile, char* const target){
    const char* makefile = "makefile";
    const char* Makefile = "Makefile";
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    FILE* fp;
    // load makefile
    if(makeFile[0] != '\0'){
        if((fp = fopen(makeFile, "r")) == NULL){
            perror("Unable to open specified makefile");
            exit(1);
        }
    }
    else{
        if((fp = fopen(makefile, "r")) == NULL){
            if((fp = fopen(Makefile, "r")) == NULL){
                perror("Unable to open makefile");
                exit(1);
            }
        }
    }
    int ch, bufN;
    while((ch = fgetc(fp)) != EOF){
        if(ch == '\n'){
            bufN++;
        }
        if(ch == '\0'){
            fprintf(stderr, "%d: Null Byte detected in makefile: %s\n", i, line);
            exit(1);
        }
    }
    rewind(fp);
    char bufLine[MAX_LINE];
    int lineNum = 1;
    char dftTgt[MAX_LINE];
    dftTgt[0] = '\0';
    Vertex* curVet;
    while(fgets(bufLine, MAX_LINE, fp) != NULL){
        const int cmdFlag = (bufLine[0] == '\t');
        if(!cmdFlag){
            curVet = parseTarget(bufLine, graph, lineNum);
            if(dftTgt[0] == '\0'){
                snprintf(dftTgt, MAX_LINE, "%s", curVet->name);
            }
        }
        else{
            if(curVet->cmdHead == NULL){
                curVet->cmdLines = (Cmd*)malloc(sizeof(Cmd));
                curVet->cmdHead = curVet->cmdLines;
                curVet->cmdLines->next = NULL;

            }
            else {
                curVet->cmdLines->next = (Cmd*)malloc(sizeof(Cmd));
                curVet->cmdLines = curVet->cmdLines->next;
                curVet->cmdLines->next = NULL;
            }
            curVet->cmdLines->rowPos = lineNum;
            snprintf(curVet->cmdLines->rawStr, MAX_LINE, "%s", bufLine);
        }
        lineNum++;
    }
    if(!feof(fp)){
        fprintf(stderr, "%d: Exceeding maximum line length: %s\n", lineNum, bufLine);
        exit(1);
    }
    // check target
    if(target[0] == '\0'){
        snprintf(target, MAX_LINE, "%s", dftTgt);
    }
    Vertex* tgtVertex = findVertexFromName(target, graph);
    Vertex* targets = postTranversal(tgtVertex, graph);
    make(targets);

}



void make(Vertex* targets){
    for(int i = 0; targets != NULL; i++){
        targets->cmdLines = targets->cmdHead;
        while(targets->cmdLines != NULL){
            if(parseCmd(targets->cmdLines) > 0){
                Cmd* cmd = targets->cmdLines;
                cmdExec(cmd);
            }

            targets->cmdLines = targets->cmdLines->next;
        }

        targets = targets->next;
    }
}








