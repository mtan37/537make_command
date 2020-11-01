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
        printf("Error: Can't allocate more memory in heap.\n");
        exit(1);
    }
    return returnVal;
}

/*
 * error handling for pthread_create
 */
void pthread_create_w(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg){
    int returnVal = pthread_create(thread,attr,start_routine,arg);
    if(0 != returnVal){
        printf("Error: pthread_create() failed. Error code: %d\n",returnVal);
        exit(1);
    }
}

/*
 * error handling for pthread_join
 */
void pthread_join_w(pthread_t thread, void **retval){
    int returnVal = pthread_join(thread,retval);
    if (0 != returnVal){
        printf("Error: pthread_join() failed. Error code: %d\n",returnVal);
        exit(1);
    }
}

/*
 * only free the ptr if it is not equal to NULL
 */
void free_w(void *ptr){
    if(NULL != ptr)
        free(ptr);
}

