typedef struct Command{
    char *curr;
    char *next;
} CommandList;

typedef struct Target{
    char *fileName;
    Command *commandList;//start of command list
    Command *endC;//end of command list 
    char **dependencies; 
    short isOutOfDate;
} Target;

typedef struct TargetList{
    Target *curr;
    Target *next;
}
void parseFile(FILE *file); 
