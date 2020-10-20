#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int type;
    int data;
} expr_item;

enum {NONE, VALUE, OPAREN, CPAREN, ADD, SUB, MUL, DIV, UNARYPLUS, UNARYMINUS};
#define tokstr(t) (t==NONE)?"NONE": \
                    (t==VALUE)?"VALUE": \
                    (t==OPAREN)?"OPAREN": \
                    (t==CPAREN)?"CPAREN": \
                    (t==ADD)?"ADD": \
                    (t==SUB)?"SUB": \
                    (t==MUL)?"MUL": \
                    (t==DIV)?"DIV": \
                    (t==UNARYPLUS)?"UNARYPLUS": \
                    (t==UNARYMINUS)?"UNARYMINUS":"Unknown"

#endif