//this module is used to validate whether there is a chain in the give list of dependencies
#include "parser.h"

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

void validateTargets(TargetList *targets);
