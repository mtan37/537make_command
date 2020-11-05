// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "executor.h"

#define BUFSIZE 4096

//  used to execute a command
void executeCommand(char* exec, char** args) {
	pid_t pid;
	pid = fork();

	int status;

	if (pid == 0) {
		execvp(exec, args);
	}
	else {
		while(wait(&status) != 0) {
			// do nothing
		}
	}
}

/*
 *  and execute commands from a 
 */
void processCommands(TargetList *targets) {
	//ex of passing to executeCommand
    //assume the Command variable is named cmd
    //executeCommand(cmd->command, cmd->args); 
	if (targets->target->commandList->curr == NULL) {
		exit(-1);
	}

	while (NULL != targets) {
		if (targets->curr->isOutOfDate == 0) {
			for (int i = 0; i < targets->curr->dependSize; i++) {
				if (getTargetFromList(targets->next, targets->curr->dependencies[i]) != NULL) {
					if (targets->next->isOutOfDate == 0) {
						executeCommand(targets->curr->commandList->command, targets->curr->commandList->args);
						targets->next->isOutOfDate = 0;
					} else {
						// do nothing
					}
				} else {
					// do nothing
				}
			}
		} else {
			// do nothing
		}
		targets = targets->next;
	}
}
