// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "executor.h"

void executeCommand(Target* target) {
	pid_t pid;
	pid = fork();

	int status;

	// append command->curr to commandArg and set command->curr = command->next while command->next != endC?
	
	// error handling
	if (pid < 0) {
		exit(-1);
	}

	if (pid == 0) { // we are the child process
		if (execvp(target->fileName, commandArg) < 0){
			exit(-1);
		} else{
			exit(0);
		}
	} else { // we are the parent process
		while(wait(&status) != 0) {
			// TODO: error handling?
		}
	}
}
