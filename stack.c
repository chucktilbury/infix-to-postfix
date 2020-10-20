/*
 *  Simple implementation of a stack using linked lists, AKA a LIFO.
 *
 *  These routines manage their own memory. The out_buf parameter is a pointer to
 *  the data structure that is stored in the stack and functions like the pop and
 *  peek function copy the data into these buffers before possibly freeing it.
 *
 *  These functions return 0 for success and !0 for failure.
 */
#include <stdio.h>
#include <string.h>

#include "stack.h"

typedef struct __stack_elem {
    void* data;
    struct __stack_elem* next;
    struct __stack_elem* prev;
} __stack_elem;

typedef struct {
    size_t item_size;
    __stack_elem* base;
    __stack_elem* top;
} __stack;

int push_stack(stack stk, void* in_buf) {

    __stack* s = (__stack*)stk;

    __stack_elem* nelem = calloc(1, sizeof(__stack_elem));
    if(nelem == NULL) {
        fprintf(stderr, "Cannot allocate stack element\n");
        return 1;
    }

    nelem->data = malloc(s->item_size);
    if(nelem->data == NULL) {
        fprintf(stderr, "cannot allocate stack data\n");
        return 1;
    }

    memcpy(nelem->data, in_buf, s->item_size);
    if(s->base == NULL) {
        s->base = s->top = nelem;
        // next and prev are NULL
    }
    else {
        nelem->prev = s->top;
        s->top->next = nelem;
        s->top = nelem;
    }

    return 0;
}

int pop_stack(stack stk, void* out_buf) {

    __stack* s = (__stack*)stk;
    __stack_elem* old_elem = s->top;

    if(s->top != NULL) {
        if(out_buf != NULL) {
            memcpy(out_buf, s->top->data, s->item_size);
        }
        free(s->top->data);
        s->top = s->top->prev;
        if(s->top != NULL) {
            s->top->next = NULL;
        }
        free(old_elem);
        return 0;
    }

    return 1;
}

int peek_stack(stack stk, void* out_buf) {

    __stack* s = (__stack*)stk;

    if(s->top != NULL) {
        memcpy(out_buf, s->top->data, s->item_size);
        return 0;
    }

    return 1;
}

/*
 *  Returns TRUE if stack is empty.
 */
int stack_is_empty(stack stk) {

    __stack* s = (__stack*)stk;

    return (s->top == NULL);
}

stack create_stack(size_t size) {

    __stack* stk = calloc(1, sizeof(__stack));

    if(stk == NULL) {
        fprintf(stderr, "Cannot allocate stack\n");
        return NULL;
    }

    stk->item_size = size;
    // base and top are NULL
    return (stack)stk;
}

int destroy_stack(stack stk) {

    __stack* s = (__stack*)stk;
    __stack_elem* crnt;
    __stack_elem* next;

    if(stk != NULL) {
        for(crnt = s->base; crnt != NULL; crnt=next) {
            next = crnt->next;
            if(crnt->data != NULL) {
                free(crnt->data);
            }
        }
        free(stk);
        return 0;
    }
    return 1;
}

