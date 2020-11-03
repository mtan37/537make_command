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

/*
 * initialize a targetList object
 */
TargetList *initTargetList(Target *curr){
    TargetList *list = calloc_w(1, sizeof(TargetList)); 
    list->curr = curr;
    list->next = NULL;
    return list;
}

/*
 * initialize a target object
 */
Target *initTarget(){
    Target *curr = calloc_w(1,sizeof(Target));
    curr->isOutOfDate = 0;
    return curr;
}

/*
 * initialize a target object
 */
Command *initCommand(){
    Command *curr = calloc_w(1,sizeof(Command));
    curr->curr = NULL;
    curr->next = NULL;
    return curr;
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
 * give a filename, return the target object from the target list
 * if target with the filename is not found, returns NULL
 */
Target *getTargetFromList(TargetList *list, char *targetName){
    //loop through the list
    while(NULL != list){
        Target *curr = list->curr;
        if(NULL != curr && 0 == strcmp(curr->fileName, targetName)){
            return curr;
        }
        list = list->next;
    }
    return NULL;
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
        char *command = calloc_w(strlen(line), sizeof(char));
        strncpy(command, line+1, strlen(line) - 1);
        //save the command to the list of commands
        if(NULL == (currTarget->commandList)){
            currTarget->commandList = initCommand();
            
            (currTarget->commandList)->curr = command;
            currTarget->endC = currTarget->commandList;
        }
        else{
            (currTarget->endC)->next = initCommand();
            Command *next = ((currTarget->endC)->next);
            currTarget->endC = next;
            next->curr = command; 
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



