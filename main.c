/*
 *  This is a simple main routine to bind things together.
 */
#include <stdio.h>
#include "convert.h"
#include "solve.h"

void print(char* str) {

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
    print("3*-(4+2)");
    print("- ( 123 + 4456 ) / - 50 + 8080");
    print("    123+-4456-50    *8080    ");

    return 0;
}