//take in target object and read the list of commands
//parse commands and execute them by fork a child process and wait

// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)

#infdef EXECUTOR_H
#define EXECUTOR_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "executor.h"

#define BUFSIZE 4096

void executeCommand(char*  fileName, char* command);
void getCommand(Target* target);

#endif
