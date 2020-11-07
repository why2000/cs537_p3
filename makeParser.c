//
// Created by hanyuan on 11/3/20.
// Team member: Hanyuan Wu, Zhihao Shu


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "makeParser.h"
#include "graph.h"
#include "strProcess.h"

/**
 * Set up the graph and start making
 * @param makeFile the name of makefile
 * @param target the name of target
 */
void makeInit(const char* const makeFile, char* const target){
    const char* makefile = "makefile";
    const char* Makefile = "Makefile";
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    FILE* fp;
    // load makefile
    if(makeFile[0] != '\0'){
        if((fp = fopen(makeFile, "r")) == NULL){
            perror("Unable to open specified makefile\n");
            exit(1);
        }
    }
    else{
        if((fp = fopen(makefile, "r")) == NULL){
            if((fp = fopen(Makefile, "r")) == NULL){
                perror("Unable to open makefile\n");
                exit(1);
            }
        }
    }
    checkNull(fp);
    rewind(fp);
    makeParse(fp, target, graph);

}


/**
 * get the modification time of a file
 * @param name the name of the file
 * @return the modification time, 0 if unable to read or check stat of the file (or no such file exists)
 */
long getTime(const char* const name){
    FILE* fp;
    if((fp = fopen(name, "r")) != NULL) {
        struct stat buf;
        if (fstat(fileno(fp), &buf) != 0) {
            return 0;
        }
        return buf.st_mtime;
    }
    return 0;
}

/**
 * Check if any null byte in the file, if so, exit the program immediately
 * @param fp the FILE pointer to be checked
 */
void checkNull(FILE* fp){
    int ch, fooRow = 1, fooCol = 0, nullFlag = 0;
    char fooLine[MAX_LINE];

    // check null byte
    while((ch = fgetc(fp)) != EOF){
        if(ch == '\n'){
            if(nullFlag) {
                fooLine[fooCol] = '\0';
                break;
            }
            fooCol = 0;
            fooRow++;
            continue;
        }
        if(ch == '\0'){
            nullFlag = 1;
            continue;
        }
        fooLine[fooCol] = (char)ch;
        fooCol++;
    }
    if(nullFlag) {
        fprintf(stderr, "%d: Null Byte detected in makefile: %s\n", fooRow, fooLine);
        exit(1);
    }
}

/**
 * Parse the lines of makefile, setting up the graph
 * @param fp the FILE pointer to the makefile
 * @param tgtName the name of target
 * @param graph the graph to use
 */
void makeParse(FILE* fp, char* tgtName, Graph* graph){
    char bufLine[MAX_LINE];
    int lineNum = 1;
    char dftTgt[MAX_LINE];
    dftTgt[0] = '\0';
    Vertex* curVet;

    // parse line by line
    while(fgets(bufLine, MAX_LINE, fp) != NULL){
        int j;
        for(j = 0; bufLine[j]=='\t'||bufLine[j]==' '; j++);
        // empty line
        if(bufLine[j] == '\n' || bufLine[j] == '\0'){
            lineNum++;
            continue;
        }
        // comment line
        if(bufLine[0] == '#') continue;
        // target line
        if(bufLine[0] != '\t'){
            curVet = parseTarget(bufLine, graph, lineNum);
            if(dftTgt[0] == '\0'){
                snprintf(dftTgt, MAX_LINE, "%s", curVet->name);
            }

        }
            // cmd line
        else{
            if(curVet == NULL){
                fprintf(stderr, "%d: cmd without a target: %s\n", lineNum, bufLine);
                exit(1);
            }
            if(curVet->cmdHead == NULL){
                curVet->cmdLines = (Cmd*)malloc(sizeof(Cmd));
                curVet->cmdHead = curVet->cmdLines;
                curVet->cmdLines->next = NULL;
            }
            else{
                curVet->cmdLines->next = (Cmd*)malloc(sizeof(Cmd));
                curVet->cmdLines = curVet->cmdLines->next;
                curVet->cmdLines->next = NULL;
            }
            curVet->cmdLines->lineNum = lineNum;
            snprintf(curVet->cmdLines->rawStr, MAX_LINE, "%s", bufLine);
        }
        lineNum++;
    }
    if(!feof(fp)){
        fprintf(stderr, "%d: Exceeding maximum line length: %s\n", lineNum, bufLine);
        exit(1);
    }
    // check target
    if(tgtName[0] == '\0'){
        snprintf(tgtName, MAX_LINE, "%s", dftTgt);
    }
    Vertex* tgtVertex = findVertexFromName(tgtName, graph);
    if(tgtVertex == NULL){
        fprintf(stderr, "%d: No target found: %s\n", lineNum, bufLine);
        exit(1);
    }
    checkCycle(graph);
    make(tgtVertex, graph);
}

/**
 * Recursive function executing the make process
 * @param vertex the target being made
 * @param graph the graph of targets
 * @return 1 if a target is not ruled, 0 if make success
 */
int make(Vertex* vertex, Graph* graph){
    // recur
    int num = vertex->adjNum;
    for(int i = 0; i < num; i++){
        if(make(vertex->adj[i], graph) != 0){
            fprintf(stderr, "%d: No rule to make target %s: %s\n",
                    vertex->lineNum, vertex->adj[i]->name, vertex->fromLine);
            exit(1);
        }
    }

    // set time
    // not a file and not a target
    if((vertex->time = getTime(vertex->name)) == 0 && vertex->isTarget == 0)
        return 1;
    // only a normal file
    if(vertex->isTarget == 0) return 0;

    // Check time
    int updateFlag = 0;
    if(num == 0) updateFlag = 1;
    for(int i = 0; i < num; i++) {
        if (vertex->time < vertex->adj[i]->time || vertex->adj[i]->updated)
            updateFlag = 1;
    }
    // no update
    if(!updateFlag)
        return 0;

    // execute
    vertex->cmdLines = vertex->cmdHead;
    while(vertex->cmdLines != NULL){
        if(parseCmd(vertex->cmdLines) == 0){
            fprintf(stderr, "%d: invalid command line: %s\n", vertex->cmdLines->lineNum, vertex->cmdLines->rawStr);
            exit(1);
        }
        Cmd* cmd = vertex->cmdLines;
        cmdExec(cmd);
        vertex->cmdLines = vertex->cmdLines->next;
    }
    // set new time
    vertex->updated = 1;
    vertex->time = getTime(vertex->name);
    return 0;
}






