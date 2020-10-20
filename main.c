/*
 *  This is a simple main routine to bind things together.
 */
#include <stdio.h>
#include "common.h"
#include "convert.h"
#include "solve.h"

static void show_outq(queue q) {

    expr_item item;

    printf("show outq:\n");
    while(!read_queue(q, &item)) {
        if(item.type != VALUE)
            printf("type: %-8s data: %s\n", tokstr(item.type), tokstr(item.data));
        else
            printf("type: %-8s data: %d\n", tokstr(item.type), item.data);
    }
}


static void print(char* str) {

    printf("\nexpression: \"%s\"\n", str);
    queue q = convert(str);
    show_outq(q);
    printf("result: %d\n", solve(q));
    destroy_queue(q);
}

int main(void) {

    print("4+(2-3)");
    print("4+2*3");
    print("(4+2)*3");
    print("-(4+2)*3");
    print("3*-(4+2)");
    print("- ( 123 + 4456 ) / - 50 + 8080");
    print("    123+-4456-50    *8080    ");

    return 0;
}