// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "executor.h"

#define BUFSIZE 4096

//  used to execute a command
void executeCommand(char* command) {	
	pid_t pid;
	pid = fork();

	int status;

	if (pid == 0) {
		execvp(command->curr, command);
	}
	else {
		while(wait(&status) != 0) {
			// do nothing
		}
	}
}

// used to call the function to execute a command after checking if it's null
void getCommand(Target* target) {
	if (target->commandList->curr == NULL) {
		exit(-1);
	}

	executeCommand(target->commandList->curr);
}
>>>>>>> origin/jrmartin4
