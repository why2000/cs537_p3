//
// Created by hanyuan on 11/3/20.
// Zhihao Shu

#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "cmdLine.h"



/**
 * execute a command using the cmd struct
 * @param cmd: the struct to be executed
 * @return 0 if execution succeeded, otherwise failed
 */
int cmdExec(Cmd* const cmd){
    int pid = 0;
    if((pid = fork())){
        int status;
        waitpid(pid, &status, 0);
        return status;
    }
    else{
        // redirections
        if(cmd->inRed){
            int inStream;
            if((inStream = open(cmd->inFile, O_RDONLY)) == -1) {
                snprintf(cmd->errMsg, MAX_LINE,
                         "Unable to open redirect file %s", cmd->inFile);
                exit(1);
            }
            if(dup2(inStream, STDIN_FILENO) == -1){
                snprintf(cmd->errMsg, MAX_LINE,
                         "Unable to redirect to file %s", cmd->outFile);
                exit(1);
            }
            close(inStream);
        }
        if(cmd->outRed){
            int outStream;
            if((outStream = open(cmd->outFile, O_WRONLY|O_TRUNC|O_CREAT))==-1) {
                snprintf(cmd->errMsg, MAX_LINE,
                         "Unable to open redirect file %s", cmd->outFile);
                exit(1);
            }
            if(dup2(outStream, STDOUT_FILENO) == -1){
                snprintf(cmd->errMsg, MAX_LINE,
                         "Unable to redirect to file %s", cmd->outFile);
                exit(1);
            }
            close(outStream);
        }
        // execute
        if(execvp(cmd->argv[0], cmd->argv) == -1)
            exit(1);
        exit(0);
    }
}
