// Authors: Marvin Tan(mtan37) (marvin.tan@wisc.edu), Joseph Martin(jrmartin4) (jrmartin4@wisc.edu)
#ifndef UTIL_H
#define UTIL_H
#include <pthread.h>
void *calloc_w(size_t num, size_t size);
void pthread_create_w(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);
void pthread_join_w(pthread_t thread, void **retval);
void free_w(void *ptr);
#endif
