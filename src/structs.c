//this module contains abstractions of different data structures, and provide functions to access them
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "util.h"
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
    curr->command = NULL;
    curr->argSize = 0;
    curr->args = NULL;
    curr->next = NULL;
    return curr;
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
 * Initialize a ChainMapNode object and return the object
 */
ChainMapNode *initChainMapNode(char *targetName){
    ChainMapNode *node = calloc_w(1, sizeof(ChainMapNode));
    node->targetName = targetName;
    node->next = NULL;
    node->validated = 0;
    node->validating = 0;
    return node;
}

/*
 * Initialize a ChainMap object and return it
 */
ChainMap *initChainMap(){
    ChainMap *map = calloc_w(1,sizeof(ChainMap));
    map->start = NULL;
    map->end = NULL;
    return map; 
}

/*
 * Add a new node to the chain map
 */
void addToChainMap(ChainMapNode *node, ChainMap *map){
    //if the map is empty, assign the node to both start and end
    if(NULL == map->start || NULL == map->end){
        map->start = node;
        map->end = node;
    }
    //else if the map is not empty 
    else{
        (map->end)->next = node;
        map->end = node;
    }
}   

/*
 * return the ChainMapNode in the ChainMap with the targetName if one exist
 * if not, initialize a new ChainMapNode for the target, add it to the ChainMap
 * And return the node
 */
ChainMapNode *getMapNode(char *targetName, ChainMap *map){
    //lopp through the map
    ChainMapNode *curr = map->start;
    while(NULL != curr){
        if(0 == strcmp(curr->targetName,targetName)){
            return curr;
        }
        curr = curr->next;
    }
    curr = initChainMapNode(targetName);
    addToChainMap(curr,map);
    return curr;
}
