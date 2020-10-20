/*
 *  This is a solver for a RPN converted expression. It returns the
 *  value that was solved.
 */
#include "common.h"
#include "stack.h"
#include "solve.h"

int solve(queue q) {

    int litem, ritem;
    expr_item item;
    stack vstack = create_stack(sizeof(int));
    int result;

    reset_queue(q);

    while(!read_queue(q, &item)) {
        if(item.type == VALUE) {
            push_stack(vstack, &item.data);
        }
        else {
            switch(item.type) {
                case UNARYPLUS:
                    if(pop_stack(vstack, &ritem)) {
                        fprintf(stderr, "syntax error: stack underflow unary plus\n");
                        exit(1);
                    }
                    result = +ritem;
                    push_stack(vstack, &result);
                    break;

                case UNARYMINUS:
                    if(pop_stack(vstack, &ritem)) {
                        fprintf(stderr, "syntax error: stack underflow unary minus\n");
                        exit(1);
                    }
                    result = -ritem;
                    push_stack(vstack, &result);
                    break;

                case ADD:
                    if(pop_stack(vstack, &ritem)) {
                        fprintf(stderr, "syntax error: stack underflow add right\n");
                        exit(1);
                    }

                    if(pop_stack(vstack, &litem)) {
                        fprintf(stderr, "syntax error: stack underflow add left\n");
                        exit(1);
                    }

                    result = litem + ritem;
                    push_stack(vstack, &result);
                    break;

                case SUB:
                    if(pop_stack(vstack, &ritem)) {
                        fprintf(stderr, "syntax error: stack underflow sub right\n");
                        exit(1);
                    }

                    if(pop_stack(vstack, &litem)) {
                        fprintf(stderr, "syntax error: stack underflow sub left\n");
                        exit(1);
                    }

                    result = litem - ritem;
                    push_stack(vstack, &result);
                    break;

                case MUL:
                    if(pop_stack(vstack, &ritem)) {
                        fprintf(stderr, "syntax error: stack underflow mul right\n");
                        exit(1);
                    }

                    if(pop_stack(vstack, &litem)) {
                        fprintf(stderr, "syntax error: stack underflow mul left\n");
                        exit(1);
                    }

                    result = litem * ritem;
                    push_stack(vstack, &result);
                    break;

                case DIV:
                    if(pop_stack(vstack, &ritem)) {
                        fprintf(stderr, "syntax error: stack underflow div right\n");
                        exit(1);
                    }

                    if(pop_stack(vstack, &litem)) {
                        fprintf(stderr, "syntax error: stack underflow div left\n");
                        exit(1);
                    }

                    if(litem == 0) {
                        fprintf(stderr, "syntax error: divide by zero encountered\n");
                        exit(1);
                    }

                    result = litem / ritem;
                    push_stack(vstack, &result);
                    break;
            }
        }
    }
    if(pop_stack(vstack, &result)) {
        fprintf(stderr, "syntax error: stack underflow for result\n");
        exit(1);
    }
    return result;
}