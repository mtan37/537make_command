// Authors: Marvin Tan(mtan37) (marvin.tan@wisc.edu), Joseph Martin(jrmartin4) (jrmartin4@wisc.edu)

//take in target object and read the list of commands
//parse commands and execute them by fork a child process and wait

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "structs.h"

void processCommands(TargetList* target, char *targetName);

#endif
