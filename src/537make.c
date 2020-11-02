//the main progarm file
//it will looks for the make file, and pass the File obj to the parser
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//DELETE
#include "parser.h"
void printTargetList(TargetList *list){
    while(NULL != list->next){
        Target *curr = list->curr;
        printf("-----Target info-----\n");
        printf("target filename %s,filename length: %ld \n", curr->fileName, strlen(curr->fileName));
        
        printf("Target dependencies\n");//DELETE
        for(int i = 0; i < curr->dependSize; i++){
            printf("dependecy %d: %s\n", i + 1, curr->dependencies[i]);//DELETE
        }
        Command *currC = curr->commandList;
        int count = 0;
        while(NULL != currC){
            count++;
            printf("command %d: %s\n", count, currC->curr);//DELETE
            currC = currC->next;
        }
        list = list->next; 
    }  
}

int main(){
    FILE *file;
    FILE *file_m = fopen("./makefile","r");
    file_m = fopen("./test","r");//DELETE, test only
    FILE *file_M = fopen("./Makefile","r");
    //check if there is a makefile 
    if(NULL != file_m){
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
    printTargetList(list);//DELETE
    printf("finished\n");//DELETE, test only
    //pass the start TargetList to validator
    //TODO    

}
