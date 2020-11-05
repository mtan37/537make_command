// Authors: Marvin Tan(mtan37) (marvin.tan@wisc.edu), Joseph Martin(jrmartin4) (jrmartin4@wisc.edu)
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
//defining error check function wrappers for library functions
/*
 * error handling for calloc
 */
void *calloc_w(size_t num, size_t size){
    void *returnVal = calloc(num,size);
    if(NULL == returnVal){
        fprintf(stderr,"Error: Can't allocate more memory in heap.\n");
        exit(1);
    }
    return returnVal;
}


/*
 * only free the ptr if it is not equal to NULL
 */
void free_w(void *ptr){
    if(NULL != ptr)
        free(ptr);
}

