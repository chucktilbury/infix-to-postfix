#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct __op_prec {
    int op;
    int prec;
} op_prec;

enum {NONE, VALUE, OPAREN, CPAREN, ADD, SUB, MUL, DIV, UNARY};
#define tokstr(t) (t==NONE)?"NONE": \
                    (t==VALUE)?"VALUE": \
                    (t==OPAREN)?"OPAREN": \
                    (t==CPAREN)?"CPAREN": \
                    (t==ADD)?"ADD": \
                    (t==SUB)?"SUB": \
                    (t==MUL)?"MUL": \
                    (t==DIV)?"DIV": \
                    (t==UNARY)?"UNARY":"Unknown"

#endif