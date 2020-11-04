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
void processCommands(Target* target) {
	//ex of passing to executeCommand
    //assume the Command variable is named cmd
    //executeCommand(cmd->command, cmd->args); 
    if (target->commandList->curr == NULL) {
		exit(-1);
	}

	char *str[BUFSIZE];

	while (target->commandList->curr != NULL) {
		strcat(str, target->commnandList->curr);
		target->commandList->curr = target->commandList->next;
	}

	executeCommand(target->fileName, str);
	free_w(str);
}
