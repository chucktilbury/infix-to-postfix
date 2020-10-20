# infix-to-postfix

This is a simple infix to rpn expression converter written in C

The idea is to first convert the expression to postfix so that it does not have to be parsed repeatedly. If there were variables that could change between times that the expression is evaluated, then those can be fetched when the expression is evaluated, rather than having to parse it again, then evaluate it.

This is intended to be simple and not have any platform dependencies. This code will most likely be reused by me in other projects.
