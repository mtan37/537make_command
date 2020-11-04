//this module handles the build and validation of dependecies 
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "graphBuilder.h"
#include "util.h"
void validateTarget(Target *currTarget, ChainMap *map, TargetList *targets){
    //get the ChainMapNode corresponds to this target
    ChainMapNode *targetNode = getMapNode(currTarget->fileName, map);
    //if the validating field has already been set to 1, return an error)
    if(1 == targetNode->validating){
        fprintf(stderr, "Error: Detect a cycle in the dependency chain\n");
        exit(1);
    }
    //set validating field to 1
    targetNode->validating = 1;
    //return if this target has already been validated
    if(1 == targetNode->validated){
        targetNode->validating = 0;
        return;
    }
    //if the target has no dependencies, set the isOutOfDate to 1
    if(0 == currTarget->dependSize){
        currTarget->isOutOfDate = 1;
    }
    //loop through its dependecies
    for(int i = 0; i < currTarget->dependSize; i++){
        char *dependency = (currTarget->dependencies)[i];
        Target *tmpT;
        struct stat tmpStat;
        //if it is a target
        tmpT = getTargetFromList(targets, dependency);
        
        if(NULL != tmpT){
            //call validateTarget
            validateTarget(tmpT, map, targets);
            //check if it is outdated
            if(1 == tmpT->isOutOfDate){
               currTarget->isOutOfDate = 1; 
            }
        }
        //if it is a file
        else if(-1 != stat(dependency, &tmpStat)){
            struct stat targetStat; 
            //check if its modification time is more recent than the target
            //or if the target file doesn't exist
            if (-1 == stat(currTarget->fileName,&targetStat)){
                currTarget->isOutOfDate = 1;
            }
            else if (tmpStat.st_mtim.tv_sec >= targetStat.st_mtim.tv_sec){
                if(tmpStat.st_mtim.tv_sec == targetStat.st_mtim.tv_sec && 
                    tmpStat.st_mtim.tv_nsec <= targetStat.st_mtim.tv_nsec){
                    continue;
                }
                currTarget->isOutOfDate = 1;
            } 
        }
        else{
            //return error if the dependency is neither a file nor a target
            if(errno == ENOENT){
                fprintf(stderr, "ERROR: No file or target matches the dependecy \"%s\"\n", dependency);
            }
            else{
                fprintf(stderr, "ERROR: Something is wrong with the stat systerm call. errno: %d\n", errno);
            }
            exit(1);
        }
    }
    //set validated field to 1
    targetNode->validated = 1;
    //set validating field to 0
    targetNode->validating = 0;
}

void validateTargets(TargetList *targets){
    ChainMap *map = initChainMap();
    //loop through the target list and call validateTarget on each target object
    while (NULL != targets){
        Target *curr = targets->curr;
        validateTarget(curr, map, targets);
        targets = targets->next;
    }
}

