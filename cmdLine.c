//
// Created by hanyuan on 11/3/20.
//

#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include "cmdLine.h"

int cmdProcess(const char* const cmdLine){
    int pid = 0;
    if((pid = fork())){
        int status;
        waitpid(pid, &status, 0);
        return status;
    }
    else{



        exit(0);
    }
}