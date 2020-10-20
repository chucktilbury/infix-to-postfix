/*
 *  This routine accepts a string and tokenizes it. It works similar
 *  to the standard tokstr() library routine but it does not destroy
 *  the input string.
 *
 *  Only decimal integers and one character operators are supported.
 *  Unary '-' operator is supported.
 */
#include "common.h"

char buffer[1024];
int buf_head = 0;

/*
 *  Internal function that actually scans the string and returns tokens.
 */
static int scan(char* str, size_t len) {
// need buffer checks.

    int str_idx = 0;
    int state = 0;
    memset(str, 0, len);
    int retv = -1;
    int finished = 0;

    while(!finished) {
        switch(state) {
            case 0:
                switch(buffer[buf_head]) {
                    case 0:
                    case '\n':
                        state = 4;
                        break;
                    case ' ':
                    case '\t':
                    case '\r':
                        buf_head++;
                        state = 1;  // skip spaces
                        break;
                    default:
                        state = 2;  // have a character
                        break;
                }
                break;
            case 1:
                if(buffer[buf_head] == 0) {
                    state = 4;
                }
                else if(isspace(buffer[buf_head])) {
                    buf_head++;
                }
                else {
                    state = 2;
                }
                break;
            case 2:
                switch(buffer[buf_head]) {
                    case '+':
                        str[0] = '+';
                        retv = ADD;
                        state = 4;
                        break;
                    case '-':
                        str[0] = '-';
                        retv = SUB;
                        state = 4;
                        break;
                    case '/':
                        str[0] = '/';
                        retv = DIV;
                        state = 4;
                        break;
                    case '*':
                        str[0] = '*';
                        retv = MUL;
                        state = 4;
                        break;
                    case '(':
                        str[0] = '(';
                        retv = OPAREN;
                        state = 4;
                        break;
                    case ')':
                        str[0] = ')';
                        retv = CPAREN;
                        state = 4;
                        break;
                    default:
                        if(isdigit(buffer[buf_head])) {
                            str[str_idx] = buffer[buf_head];
                            str_idx++;
                            retv = VALUE;
                            state = 3;
                        }
                        else {
                            fprintf(stderr, "unknown character encountered: '%c' (0x%02X)\n",
                                        buffer[buf_head], buffer[buf_head]);
                            exit(1);
                        }
                }
                buf_head++;
                break;
            case 3:
                if(isdigit(buffer[buf_head])) {
                    str[str_idx] = buffer[buf_head];
                    str_idx++;
                    buf_head++;
                }
                else {
                    state = 4;
                }
                break;
            case 4:
                finished++;
                break;
        }
    }
    return retv;
}

/*
 *  Call this with a string for the first token, then call it with NULL
 *  for subsequent tokens. Where there are no more tokens, then this
 *  returns NULL.
 */
int token(char* init, char* tstr, size_t len) {

    int retv;

    if(init) {
        strncpy(buffer, init, sizeof(buffer));
        buf_head = 0; //buf_tail = 0;
        retv = scan(tstr, len);
    }
    else {
        retv = scan(tstr, len);
    }

    return retv;
}

