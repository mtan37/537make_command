//check the following
//1)whether there is a chain in the dependencies. If there is, return an error
//2)whether the dependecies are all existing files or targets
//3)whether the dependencies are out of date
#include <stdlib.h>
#include "validator.h"

typedef struct ChainMap{
    ChainMapNode *start;
    ChainMapNode *end;
}ChainMap;

typedef struct ChainMapNode{
    char *targetName;
    ChainMapNode **dependencies
    short validated;
    short validating;
}ChainMapNode;

/*
 * Add a new node to the chain map
 */
void addToChainMap(ChainMapNode *node, ChainMap *map){


}

/*
 * return the ChainMapNode in the ChainMap with the targetName if one existe
 * if not, initialize a new ChainMapNode for the target, add it to the ChainMap, and return the node
 */
ChainMapNode *getMapNode(char *targetName, ChainMap *map){

}

short validateTarget(Target *currTarget, ChainMap *map){
    //get the ChainMapNode corresponds to this target
    //return if this target has already been validated
    //if the validating field has already been set to 1, return an error(detect a cycle in dependencies)
    //set validating field to 1
    //loop through its dependecies
        //if it is a target: call validate Target on it
            //check if it is outdated(checked the isOutdated field of the target object)
        //if it is a file, check if its modification time is more recent than the target
        //return error if the dependency is neither a file nor a target
    //note if the target has no dependencies, set the isOutdated to 1
    //set validated field to 1
    //set validating field to 0
}

short validateTargets(TargetList *targets){
    ChainMap *map = calloc_w(1, sizeof(ChainMap));
    //loop through the target list and call validateTarget on each target object
}

