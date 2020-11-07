//
// Created by hanyuan on 11/3/20.
// Team member: Hanyuan Wu, Zhihao Shu


#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "cmdLine.h"



/**
 * execute a command using the cmd struct, if any error occurred, exit immediately
 * @param cmd: the struct to be executed
 */
void cmdExec(Cmd* const cmd){
    int pid = 0;
    if((pid = fork())){
        int status;
        waitpid(pid, &status, 0);
        if(status != 0){
            fprintf(stderr,
                    "%d: execution failed: %s", cmd->lineNum, cmd->rawStr);
            exit(1);
        }
    }
    else{
        // redirect in
        if(cmd->inRed){
            int inStream;
            if((inStream = open(cmd->inFile, O_RDONLY)) == -1) {
                fprintf(stderr,
                         "%d: Unable to open redirect file %s: %s", cmd->lineNum, cmd->inFile, cmd->rawStr);
                exit(1);
            }
            if(dup2(inStream, STDIN_FILENO) == -1){
                fprintf(stderr,
                         "%d: Unable to redirect to file %s: %s", cmd->lineNum, cmd->inFile, cmd->rawStr);
                exit(1);
            }
            close(inStream);
        }
        // redirect out
        if(cmd->outRed){
            int outStream;
            if((outStream = open(cmd->outFile,
                                 O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IRGRP|S_IWGRP|S_IWUSR))==-1) {
                fprintf(stderr,
                        "%d: Unable to open redirect file %s: %s", cmd->lineNum, cmd->outFile, cmd->rawStr);
                exit(1);
            }
            if(dup2(outStream, STDOUT_FILENO) == -1){
                fprintf(stderr,
                        "%d: Unable to redirect from file %s: %s", cmd->lineNum, cmd->inFile, cmd->rawStr);
                exit(1);
            }
            close(outStream);
        }
        // execute
        if(execvp(cmd->argv[0], cmd->argv) == -1){
            perror(cmd->argv[0]);
            exit(1);
        }
        exit(0);
    }
}