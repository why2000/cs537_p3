//
// Created by hanyuan on 11/4/20.
//

#include <stdlib.h>
#include "strProcess.h"


int parseTarget(const char* const line){

    char tgtName[MAX_LINE];
    char bufDep[MAX_LINE];
    const int cmdFlag = (line[0] == '\t');
    int i;
    for(i = 0; i < MAX_LINE; i++){
        if (bufLine[i] == ':') {
            tgtName[i] = '\0';
            break;
        }
        tgtName[i] = bufLine[i];
    }
    while(i < MAX_LINE){
        readItem()
    }
}


/**
 * Parse and fill the cmd struct from its rawStr field
 * @param cmd: the cmd struct to be parsed
 * @return the number of arguments detected
 */
int parseCmd(Cmd* const cmd){
    if(cmd->rawStr[0] == '\0' || cmd->rawStr[0] == '#')
        return 0;
    for(int i = 0; i < MAX_LINE; i++){
        char ch = cmd->rawStr[i];
        // jump spaces
        if(ch==' '||ch=='\n'||ch=='\t')
            continue;
        switch(ch){
            // redirection
            case '>':
                i++;
                readItem(cmd->outFile, cmd->rawStr, &i);
                cmd->outRed = 1;
                break;
            case '<':
                i++;
                readItem(cmd->inFile, cmd->rawStr, &i);
                cmd->inRed = 1;
                break;
                // normal args
            default:
                cmd->argv[cmd->argc] = (char*)malloc(sizeof(char)*MAX_LINE);
                // non-strict mode, as \0 is already checkeda
                readItem(cmd->argv[cmd->argc], cmd->rawStr, &i, 0);
                cmd->argc++;
                break;
        }
        if(cmd->rawStr[i] == '\0')
            return cmd->argc;
    }
    return cmd->argc;
}

/**
 * read an item (string without space) out of a longer string from a given start position
 * @param target: the buffer to store the item
 * @param rawStr: the long string to be parsed
 * @param pos: the start position
 * @param strict: non zero value turns on strict mode -- return non-zero if reaches '\0' while reading
 * @return 0 if read succeeded, otherwise failed
 */
int readItem(char* const target, const char* const rawStr, int* pos, int strict){
    int i = *pos;
    // do a left strip
    while(rawStr[i] == ' ' && i < MAX_LINE-1)
        i++;
    *pos = i;
    // copy item
    for(int j = 0; *pos < MAX_LINE; j++,(*pos)++){
        if(rawStr[*pos] == '\0' && strict){
            return 1;
        }
        if(*pos == MAX_LINE - 1 || rawStr[*pos] == ' ' || rawStr[*pos] == '\t'){
            target[j] = '\0';
            break;
        }
        target[j] = rawStr[*pos];
    }
    return 0;
}