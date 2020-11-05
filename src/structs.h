// Authors: Marvin Tan(mtan37) (marvin.tan@wisc.edu), Joseph Martin(jrmartin4) (jrmartin4@wisc.edu)
#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct Command{
    char *command;
    char **argv;
    int argc;
    struct Command *next;
} Command;

//struct represents each target
typedef struct Target{
    char *fileName;
    Command *commandList;//start of command list
    Command *endC;//end of command list 
    char **dependencies; 
    int dependSize;
    short isOutOfDate;
} Target;

typedef struct TargetList{
    Target *curr;
    struct TargetList *next;
} TargetList;

//structs used sole for dependency validation
typedef struct ChainMapNode{
    char *targetName;
    struct ChainMapNode *next;
    short validated;
    short validating;
}ChainMapNode;

typedef struct ChainMap{
    ChainMapNode *start;
    ChainMapNode *end;
}ChainMap;


TargetList *initTargetList(Target *curr);

Target *initTarget();

Command *initCommand();

Target *getTargetFromList(TargetList *list, char *targetName);

ChainMapNode *initChainMapNode(char *targetName);

ChainMap *initChainMap();

void addToChainMap(ChainMapNode *node, ChainMap *map);

ChainMapNode *getMapNode(char *targetName, ChainMap *map);

#endif
