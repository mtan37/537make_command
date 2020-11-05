// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "executor.h"
//  used to execute a command
short executeCommand(char** argv) {
	pid_t pid;
	pid = fork();
	int status;
    if (-1 == pid){
        fprintf(stderr, "ERROR: child process failed to be created\n");
        exit(1);
    }
	else if (0 == pid) {//this is the child process
		execvp(argv[0], argv);
        //if the code reaches here, the execution failed abnormally 
        exit(1);
    }
	else {//this is the parent process
		wait(&status);
        //if the child process exited abnormally
        if( 0 != status){
            return 0;
        }
	    return 1;
    }
}

/*
 * Recursive helper for the processCommands function
 */
void processCommandsHelper(Target* target, TargetList* targets) {
    //if the target is out of date
    if(1 == target->isOutOfDate){
        //loop through its dependecnies
        for(int i = 0; i < target->dependSize; i++){
            Target *dep = getTargetFromList(targets, target->dependencies[i]);
            //if the dependecy is also a target, and it is out of date 
            if(NULL != dep && 1 == dep->isOutOfDate){
                processCommandsHelper(dep, targets);
            }
        }
        target->isOutOfDate = 0; 
        //execute the commands
        Command *cmd = target->commandList;
        while(NULL != cmd){
            if(0 == executeCommand(cmd->argv)){
                exit(1);
            }
            cmd = cmd->next;
        }
    }
}

/*
 *  and execute commands from a 
 */
void processCommands(TargetList* targets, char *targetName) {
    Target *target = NULL;
    if(targetName == NULL){//take the first target in the list
        target = targets->curr;
    }
    else{
        target = getTargetFromList(targets, targetName);
        if(NULL == target){
            fprintf(stderr, "%s is not a target name. Exit the program\n", targetName);
            exit(1);
        }
    }
    processCommandsHelper(target, targets);
}
