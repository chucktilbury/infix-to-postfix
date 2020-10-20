#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>
typedef void* stack;

int push_stack(stack, void*);
int pop_stack(stack, void*);
int peek_stack(stack, void*);
int stack_is_empty(stack);
stack create_stack(size_t);
int destroy_stack(stack);

#endif