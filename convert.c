/*
 *  This is the set of convert routines. It takes a string and converts it
 *  to the RPN, which it then returns.
 *
 * Operators supported:
 * '+', '-', '*', '/', unary '-'
 */
#include "common.h"
#include "scanner.h"
#include "stack.h"
#include "queue.h"

typedef struct {
    int type;
    int data;
} expr_item;

static op_prec precs[] = {
    {OPAREN, 0},
    {CPAREN, 0},
    {ADD, 1},
    {SUB, 1},
    {MUL, 2},
    {DIV, 2},
    {UNARY, 3},
    {-1, -1}
};

void show_outq(queue q) {

    expr_item item;

    printf("show outq:\n");
    while(!read_queue(q, &item)) {
        if(item.type != VALUE)
            printf("type: %-8s data: %s\n", tokstr(item.type), tokstr(item.data));
        else
            printf("type: %-8s data: %d\n", tokstr(item.type), item.data);
    }
}

/*
 *  Return the precidence value of the item given. Does not check for unary
 *  items.
 */
static int get_prec(expr_item* item) {

    int retv = -1;

    for(int i = 0; precs[i].prec > 0; i++) {
        if(precs[i].op == item->type) {
            retv = precs[i].prec;
            break;
        }
    }
    return retv;
}

/*
 *  Return if item <= top of the stack.
 */
static int comp_prec(stack s, expr_item* item) {

    expr_item tmp_item;

    peek_stack(s, &tmp_item);
    return (get_prec(item) <= get_prec(&tmp_item));
}

/*
 *  Compare the token on the top of the stack with the given token.
 */
static int comp_token(stack s, int tok) {

    expr_item tmp_item;

    peek_stack(s, &tmp_item);
    return (tmp_item.type == tok);
}

/*
 *  Transfer the operand on the top of the stack to the output queue.
 */
static void transfer(queue q, stack s) {

    expr_item item;
    pop_stack(s, &item);
    write_queue(q, &item);
}

/*
 *  When an operator is encountered, if it has a higher precidence than the top of the
 *  stack, then it is pushed on the stack. If it has a lower precidence, then transfer
 *  the higher operators to the output queue until a lower precidence operator is found
 *  on the top of the stack, the stack is empty, or a oparen is found. If an oparen is
 *  found, then stop there and push the scanned operator.
 *
 *  Add and SUB can be unary. An operator is unary if it is the first thing scanned, or
 *  if it follows another operator. A unary operator is right-associative and is
 *  translated to the correct token type by adding UNARY as the value. UNARY operators
 *  have the highest precidence.
 */
static void handle_operator(queue q, stack s, expr_item* item) {

    if(item->data == UNARY) {
        push_stack(s, item);
    }
    else {
        while(!stack_is_empty(s) && comp_prec(s, item)) {
            transfer(q, s);
        }
        push_stack(s, item);
    }
}

/*
 *  Then a CPAREN is encountered, transfer the operators on the stack to the queue until
 *  a OPAREN is encountered. If the stack goes empty before a OPAREN is found, then that
 *  is a syntax error. Discard all of the parens found.
 */
static void handle_cparen(queue q, stack s) {

    while(!stack_is_empty(s) && !comp_token(s, OPAREN)) {
        transfer(q, s);
    }

    if(!stack_is_empty(s) && !comp_token(s, OPAREN)) {
        fprintf(stderr, "syntax error\n");
        return;
    }
    else {
        pop_stack(s, NULL);
    }
}


queue convert(char* nstr) {

    int tok, ptok = NONE;
    char tstr[50];
    expr_item item;
    queue out_queue = create_queue(sizeof(expr_item));
    stack op_stack = create_stack(sizeof(expr_item));

    for(tok = token(nstr, tstr, sizeof(tstr)); tok > 0; tok = token(NULL, tstr, sizeof(tstr))) {
        switch(tok) {
            case ADD:
            case SUB:
                item.type = tok;
                if(ptok == NONE) {
                    item.data = UNARY;
                }
                else {
                    item.data = NONE;
                    ptok = NONE;
                }
                //write_queue(out_queue, &item);
                handle_operator(out_queue, op_stack, &item);
                break;

            case MUL:
            case DIV:
                // MUL and DIV are never unary. Apply the normal operator rules.
                item.type = tok;
                item.data = NONE;
                ptok = NONE;
                //write_queue(out_queue, &item);
                handle_operator(out_queue, op_stack, &item);
                break;

            case OPAREN:
                // When we see an oparen, always push it on the stack
                item.type = tok;
                item.data = NONE;
                ptok = NONE;
                //write_queue(out_queue, &item);
                push_stack(op_stack, &item);
                break;

            case CPAREN:
                // When we see a cparen, transfer everything to the output queue
                // until we find the oparen. Discard the parens.
                item.type = tok;
                item.data = NONE;
                ptok = NONE;
                //write_queue(out_queue, &item);
                handle_cparen(out_queue, op_stack);
                break;

            case VALUE:
                // Upon finding a value, put it in the output queue.
                item.type = tok;
                item.data = atoi(tstr);
                ptok = VALUE;
                write_queue(out_queue, &item);
                break;
        }
    }
    // Transfer any remain operators on the stack to the output queue.

    // The queue is now ready to solve.
    destroy_stack(op_stack);
    return out_queue;
}


// void convert(char* nstr) {

//     int tok, ptok;
//     char tstr[50];
//     expr_item item;

//     for(tok = token(nstr, tstr, sizeof(tstr)); tok > 0; tok = token(NULL, tstr, sizeof(tstr))) {
//         switch(tok) {
//             case ADD:
//             case SUB:
//             case MUL:
//             case DIV:
//                 item.type = tok;
//                 if(ptok == NONE) {
//                     item.data = UNARY;
//                 }
//                 else {
//                     item.data = NONE;
//                     ptok = NONE;
//                 }
//                 write_queue(out_queue, &item);
//                 break;

//             case OPAREN:
//                 //break;

//             case CPAREN:
//                 item.type = tok;
//                 item.data = NONE;
//                 write_queue(out_queue, &item);
//                 break;

//             case VALUE:
//                 item.type = tok;
//                 item.data = atoi(tstr);
//                 ptok = VALUE;
//                 write_queue(out_queue, &item);
//                 break;
//         }
//     }
// }

