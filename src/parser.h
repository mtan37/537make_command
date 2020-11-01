typedef struct CommandList{
    char *curr;
    char *next;
} CommandList;

typedef struct Target{
    char *fileName;
    CommandList *commandList; 
    char **dependencies; 
    short isOutOfDate;
} Target;

typedef struct TargetList{
    Target *curr;
    Target *next;
}
void parseFile(FILE *file); 
