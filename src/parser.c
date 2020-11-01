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

#include <stdio>
#include <stdin>
#include "parser.h"
const size_t BUFFSIZE = 4096;

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
    curr->itOutOfDate = -1;
    return curr;
}

/*
 * Check if the line contains only spaces and tabs
 * return 1 if it is a blank line, else returns 0
 */
short isBlankLine(char *line){
    int i = 0;
    while(NULL != line && '\0' != line[i]){
        if(' ' != line[i] && '\t' != line[i])
            return 0;
    }
    return 1;
}
/*
 * process line that describe a target
 */
void processTargetLine(char *line, Target *currTarget){
    char buff[BUFFSIZE];
    char **tempList = calloc_w(BUFFSIZE, sizeof(char *));
    int i = 0;
    //get the target name
    while(i < BUFFSIZE && ':' != line[i]){
        buff[]
        i++;
    }
    //check if there exist a valid target
    if(i <= 0 || i >= BUFFSIZE){
        //return error TODO
    }
    buff[i] = '\n';
    i++;//skip char :
    currTarget->fileName = calloc_w(i - 1, sizeof(char));
    strcpy(currTarget->fileName, buff);
    //get the list of dependencies
    int dependenciesCount = 0;
    while(i < 4096 && '\n' != line[i]){
        int j = 0;
        while(' ' != line[i] && '\t' != line[i] && '\n' != line[i]){
            buff[j] = line[i]  
            j++;
            i++;
        }  
        if(j > 0){
            BUFF[j + 1] = '\n'
            tempList[dependenciesCount] = calloc(j + 1,sizeof(char));
            strcpy(tempList[dependenciesCount], buff);
            dependenciesCount++;
        }   
    }
    if(dependenciesCount == 0){//if no dependencies are listed
        //return error TODO
    }
    currTarget->dependencies = calloc_w(dependenciesCount, sizeof(char *));
    //copy the dependencies from tempList to the dependencies list
    for(int j = 0; j < dependeciesCount; j++){
        int length = strlen(tempList[j]);
        currTarget->dependencies[j] = calloc_w(length, sizeof(char));
        strcpy(currTarget->dependencies[j], tempList[j]);
        free(tempList[j]);         
    }
    free(tempList);
    return 
}
/*
 * process a Makefile line based on its type(a blank line, a target, a command or a comment)
 * add information to the currTarget
 */
void processLine(char *line, Target *currTarget){
    if (NULL == line)
        return;
    if('#' == line[0]){//if it is a comment line
        return;        
    }
    if(1 == isBlankLine(line))
        return;
    //if it is a command line
    else if('\t' == line[0]){
        //save the command to the list of commands
        if(NULL == currTarget->commandList){
            currTarget->commandList = calloc_w(1,sizeof(Command));
            (currTarget->commandList)->curr = line + 1;
            currTarget->endC = currTarget->commandList;
        }
        else{
            (currTarget->endC)->next = calloc_w(1,sizeof(Command));
            currTarget->endC = (currTarget->endC)->next;
            (currTarget->endC)->curr = line + 1; 
        }
    }
    //if it is a target line
    else if(' ' != line[0]){
        processTargetLine(line, currTarget);
    }
    else{//invalid format
        //TODO    
    }
}
/*
 * parse makefile and generate a list of Target
 */
void parseFile(FILE *file){
    TargetList *start = NULL;
    TargetList *end = NULL;
    Target *currTarget = NULL;    
    char *buff[4096];
    //read from file by line
    while(fgets(buff, BUFFSIZE , file)!=NULL){
        int inputLength = strlen(buff);
        //check if the buffer overflows or there is a NULL byte in the line
        if(buff[inputLength - 1] != '\n'){
            if(inputLength = BUFFSIZE){//buffer overflow
                fprintf(stderr,"Size of line exceeds the buffer size limit. Exit the program\n");
                exit(1);
            }
            else{//NULL byte exist in line
                fprintf(stderr,"Detect NULL byte in the line. Exit the program\n");
                exit(1);
            }
        }
        //replace the new line with null symbol
        buff[inputLength - 1] = '\0';
        currTarget = initTarget();
        processLine(buff, currTarget, list);
        //add the target to the target list    
        if(NULL == start && end == NULL){
            start = initTargetList(currTarget);
            end = start;
        }
        else{
            end->next = initTargetList(currTarget);
            end = end->next;
        }
    }    
}



