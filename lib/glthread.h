#ifndef __GLTHREAD_H__
#define __GLTHREAD_H__

#include <stdint.h>

#define GLTHREAD_TO_PARENT_NODE_ADDR(struct_name, glthread_addr, glthread_name) \
    ((struct_name *)(((unsigned long)glthread_addr) - ((unsigned long int)(&(((struct_name *)0)->glthread_name)))))

#define BASE(glthreadptr) ((glthreadptr)->next)

#define ITERATE_OVER_GLTHREAD(glthreadptrstart, glthreadptr_itr) \
    for (glthreadptr_itr = BASE(glthreadptrstart); glthreadptr_itr != NULL; glthreadptr_itr = (glthreadptr_itr)->next)

typedef struct glthread_
{
    struct glthread_ *prev;
    struct glthread_ *next;
} glthread_t;

void glthread_add_next(glthread_t *base_glthread, glthread_t *new_glthread);

void glthread_add_before(glthread_t *base_glthread, glthread_t *new_glthread);

void glthread_remove(glthread_t *glthread);

void init_glthread(glthread_t *glthread);

void glthread_add_last(glthread_t *base_glthread, glthread_t *new_glthread);

uint64_t get_glthread_list_count(glthread_t *base_glthread);

#endif