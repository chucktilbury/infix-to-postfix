/*
 *  This is a simple main routine to bind things together.
 */
#include <stdio.h>
#include "convert.h"

void print(char* str) {

    printf("\nexpression: \"%s\"\n", str);
    queue q = convert(str);
    show_outq(q);
    destroy_queue(q);
}

int main(void) {

    print("- ( 123 + 4456 ) / - 50 + 8080");
    print("    123+-4456-50    *8080    ");

    return 0;
}