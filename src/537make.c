
//the main progarm file
//it will looks for the make file, and pass the File obj to the parser
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "executor.h"
int main(int argc, char **argv){
    FILE *file;
    FILE *file_user = NULL;
    char *targetName = NULL;
    int opt = getopt(argc, argv, "f:");
    if ('f' == opt){
        file_user = fopen(optarg, "r"); 
    }
    if(optind < argc){
        //get the build target name
        targetName = argv[optind];
    }
    FILE *file_m = fopen("makefile","r");
    FILE *file_M = fopen("Makefile","r");
    //check if there is an user specified file
    if(NULL != file_user){
        file = file_user;
    }
    //check if there is a makefile 
    else if(NULL != file_m){
        file = file_m;
    }
    //check if there is a Makefile
    else if (NULL != file_M){
        file = file_M;
    }
    //no makefile exists, return error
    else{
        fprintf(stderr,"ERROR: no makefile exists\n");
        exit(1);
    }
    //pass the file obj to the parser
    TargetList *list = parseFile(file);    
    //pass the start TargetList to validator
    validateTargets(list);      
    //process the commands and build the target
    processCommands(list, targetName);
}
