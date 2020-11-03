typedef struct Command{
    char *curr;
    struct Command *next;
} Command;

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

Target *getTargetFromList(TargetList *list, char *targetName);

TargetList *parseFile(FILE *file); 
