#include <stdio.h>
#include "calculator.h"

int main() {

    char infix[100];
    char postfix[100];

    printf("Input: ");
    fgets(infix, sizeof(infix), stdin);

    infixToPostfix(infix, postfix);

    evalPostfix(postfix);

    return 0;
}
