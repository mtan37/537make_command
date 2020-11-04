//parses the Make file.
//It will read the file and load it into a struct called Target
//Target... just like the name, represents a target file. It will have three fields
    //1)fileName
    //2)a list of dependencies
    //3)a list of command to execute
    //4)indicte whether it is out of date
//it will store those loaded targets into a list of targets.
//it will call the validator to check:
    
    //1)whether there is a chain in the dependencies. If there is, not more check is needed and return error
    //2)whether the dependecies are all existing files or targets
    //3) whether the dependencies are out of date
//a target will be only sent to the executor if it is out of date

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "util.h"

const int BUFFSIZE = 4096;

//Function for TESTING, DELETE
void printTargetList(TargetList *list){
    while(NULL != list){
        Target *curr = list->curr;
        printf("-----Target info-----\n");
        printf("target filename %s,filename length: %ld \n", curr->fileName, strlen(curr->fileName));
        printf("target isOutOfDate: %d\n", curr->isOutOfDate);
        printf("Target dependencies\n");//DELETE
        for(int i = 0; i < curr->dependSize; i++){
            printf("dependecy %d: %s\n", i + 1, curr->dependencies[i]);//DELETE
        }
        Command *currC = curr->commandList;
        int count = 0;
        while(NULL != currC){
            count++;
            printf("command %d: %s", count, currC->command);//DELETE
            for(int i = 0; i < currC->argSize; i++){
                printf(", %s", currC->args[i]);
            }
            printf("\n");
            currC = (currC->next);
        }
        list = list->next; 
    }  
}

/*
 * Check if the line contains only spaces and tabs
 * return 1 if it is a blank line, else returns 0
 */
short isBlankLine(char *line){
    int i = 0;
    int length = strlen(line);
    while(NULL != line && i < length){
        if(' ' != line[i] && '\t' != line[i]){
            return 0;
        }
        i++;
    }
    return 1;
}

/*
 * process line that describe a target
 */
Target *processTargetLine(char *line, int lineCount){
    int length = strlen(line);
    char buff[BUFFSIZE];
    char **tempList = calloc_w(BUFFSIZE, sizeof(char *));
    int i = 0;
    //get the target name
    while(i < BUFFSIZE && ':' != line[i]){
        buff[i] = line[i];
        i++;
    }
    //check if there exist a valid target
    if(i <= 0 || i >= BUFFSIZE){
        fprintf(stderr, "%d: Can't parse target: \"%s\"\n", lineCount, line);
        exit(1);
    }
    buff[i] = '\n';
    i++;//skip char :
    Target *currTarget = initTarget();
    currTarget->fileName = calloc_w(i, sizeof(char));
    strncpy(currTarget->fileName, buff,i-1);
    //get the list of dependencies
    int dependenciesCount = 0;
    while(i < 4096 && i < length){
        int j = 0;
        while(' ' != line[i+j] && '\t' != line[i+j] && (i+j) < length){
            buff[j] = line[i+j]; 
            j++;
        }
        i = i + j; 
        if(j > 0){
            buff[j + 1] = '\n';
            tempList[dependenciesCount] = calloc(j + 1,sizeof(char));
            strncpy(tempList[dependenciesCount], buff,j);
            dependenciesCount++;
        }   
        if(length == i)
            break;
        i++;
    }
    if(dependenciesCount == 0){//if no dependencies are listed
        currTarget->dependSize = 0;
        currTarget->dependencies = NULL;    
    }
    currTarget->dependencies = calloc_w(dependenciesCount, sizeof(char *));
    currTarget->dependSize = dependenciesCount;    
    //copy the dependencies from tempList to the dependencies list
    for(int j = 0; j < dependenciesCount; j++){
        int length = strlen(tempList[j]);
        currTarget->dependencies[j] = calloc_w(length, sizeof(char));
        strcpy(currTarget->dependencies[j], tempList[j]);
        free(tempList[j]);         
    }
    free(tempList);
    //return the newly initialized target
    return currTarget;
}

/*
 * Parse the command line and save it into the cmdStruct
 */
int parseCommand(char *cmdLine, Command *cmdStruct){
    printf("parse command\n");//DELETE
    char *cmdLineCp = calloc_w(strlen(cmdLine)+1 ,sizeof(char));
    const char delim[2] = " ";
    strncpy(cmdLineCp, cmdLine, strlen(cmdLine));
    printf("parse command2\n");//DELETE
    //get the execute file name
    int argc = 0;
    int length = strlen(cmdLine);
    char *buff[length];
    char *arg = strtok(cmdLineCp,delim);
    printf("parse command3\n");//DELETE
    while(NULL != arg){
        printf("the parsed arg: %s\n", arg);//DELETE
        char *argTmp = calloc_w(strlen(arg) + 1, sizeof(char));
        strncpy(argTmp, arg, strlen(arg));
        buff[argc] = argTmp;
        argc++;
        arg = strtok(NULL, delim);
    }
    free(cmdLineCp);
    if(argc <= 0){
        return 0;
    }
    printf("parse command4\n");//DELETE
    cmdStruct->args = calloc_w(argc - 1, sizeof(char*));
    cmdStruct->argSize = argc - 1;
    printf("parse command5\n");//DELETE
    //copy the args to the Command struct
    for(int i = 0; i < argc;i++){
        if(0 == i){
            printf("copy from buff: %s\n", buff[i]);//DELETE
            cmdStruct->command = buff[i];
            continue;
        }
        printf("copy from buff: %s\n", buff[i]);//DELETE
        (cmdStruct->args)[i - 1] = buff[i];
    }
    printf("parse command6\n");//DELETE
    return 1;
}

/*
 * process a Makefile line based on its type(a blank line, a target, a command or a comment)
 * add information to the currTarget
 */
Target *processLine(char *line, Target *currTarget, int lineCount){
    if (NULL == line)
        return NULL;
    if('#' == line[0])//if it is a comment line
        return NULL;        
    if(1 == isBlankLine(line))
        return NULL;
    //if it is a command line
    if('\t' == line[0]){
        char *command = line + 1;
        //save the command to the list of commands
        if(NULL == (currTarget->commandList)){
            Command *next = initCommand();
            if(0 == parseCommand(command, next)){
                fprintf(stderr,
                    "%d: Error parsing command line: \"%s\"\n", lineCount,line);
                exit(1);
            }
            currTarget->commandList = next;
            currTarget->endC = currTarget->commandList;
        }
        else{
            Command *next = initCommand();
            if(0 == parseCommand(command, next)){
                fprintf(stderr,
                    "%d: Error parsing command line: \"%s\"\n", lineCount,line);
                exit(1);
            }
            (currTarget->endC)->next = next;
            currTarget->endC = next;
        }
        
        Command *currC = currTarget->commandList;
        int count = 0;
        while(NULL != currC){
            count++;
            currC = (currC->next);
        }
        return NULL;   
    }
    //if it is a target line
    else if(' ' != line[0]){
        currTarget = processTargetLine(line, lineCount);
        return currTarget;
    }
    else{//invalid format
        fprintf(stderr, "%d: Unexpected space at beginning of line: \"%s\"\n", lineCount, line);
        exit(1);
    }
}

/*
 * parse makefile and generate a list of Target
 */
TargetList *parseFile(FILE *file){
    TargetList *start = NULL;
    TargetList *end = NULL;
    Target *currTarget = NULL;    
    Target *returnT;
    char buff[4096];
    int lineCount = 0;
    //read from file by line
    while(fgets(buff, BUFFSIZE , file)!=NULL){
        lineCount++;
        int inputLength = strlen(buff);
        //check if the buffer overflows or there is a NULL byte in the line
        if('\n' != buff[inputLength - 1]){
            if(inputLength == BUFFSIZE){//buffer overflow
                fprintf(stderr,"%d: Size of line exceeds the buffer size limit.\n", lineCount);
                exit(1);
            }
            else{//NULL byte exist in line
                fprintf(stderr,"%d: Detect NULL byte in the line \n", lineCount);
                exit(1);
            }
        }
        //replace the new line with null symbol
        buff[inputLength - 1] = '\0';
        returnT = processLine(buff, currTarget, lineCount);
        if(NULL != returnT){
            //add the target to the target list    
            if(NULL == start && end == NULL){
                start = initTargetList(returnT);
                end = start;
            }
            else{
                end->next = initTargetList(returnT);
                end = end->next;
            }
            currTarget = returnT;
        }
    }
    return start;
}



