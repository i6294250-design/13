#include <stdio.h>
#include <string.h>
#include "calculator.h"
#include "ArrayStack.h"

int precedence(char op) {

    switch (op)
    {
    case '*':
    case '/':
        return 2;

    case '+':
    case '-':
        return 1;

    case '(':
        return 0;

    default:
        return 0;
    }
}

void printOperatorStack(ArrayStack* stack) {

    for (int i = 0; i <= stack->top; i++) {
        printf("%c", stack->array[i]);

        if (i != stack->top)
            printf(" ");
    }
}

void printValueStack(ArrayStack* stack) {

    for (int i = 0; i <= stack->top; i++) {
        printf("%d", stack->array[i]);

        if (i != stack->top)
            printf(" ");
    }
}

void printPostfix(char* postfix, int length) {

    for (int i = 0; i < length; i++) {
        printf("%c ", postfix[i]);
    }
}

void infixToPostfix(char* infix, char* postfix) {

    ArrayStack* opStack = createArrayStack(100, CHARACTER);

    int j = 0;

    printf("\nTransform:\n\n");

    for (int i = 0; infix[i] != '\0'; i++) {

        char token = infix[i];

        if (token == ' ')
            continue;

        // 숫자
        if (token >= '0' && token <= '9') {

            postfix[j++] = token;
        }

        // 여는 괄호
        else if (token == '(') {

            pushArrayStack(opStack, token);
        }

        // 닫는 괄호
        else if (token == ')') {

            while (!emptyArrayStack(opStack)) {

                char op = popArrayStack(opStack);

                if (op == '(')
                    break;

                postfix[j++] = op;
            }
        }

        // 연산자
        else {

            while (!emptyArrayStack(opStack)) {

                char topOp = peekArrayStack(opStack);

                if (precedence(token) <= precedence(topOp)) {

                    postfix[j++] = popArrayStack(opStack);
                }
                else {
                    break;
                }
            }

            pushArrayStack(opStack, token);
        }

        printf("- Postfix: ");
        printPostfix(postfix, j);

        printf("| Stack: ");
        printOperatorStack(opStack);

        printf("\n");
    }

    while (!emptyArrayStack(opStack)) {

        postfix[j++] = popArrayStack(opStack);

        printf("- Postfix: ");
        printPostfix(postfix, j);

        printf("| Stack: ");
        printOperatorStack(opStack);

        printf("\n");
    }

    postfix[j] = '\0';

    printf("\n- Result: ");
    printPostfix(postfix, j);
    printf("\n");
}

int evalPostfix(char* postfix) {

    ArrayStack* valueStack = createArrayStack(100, INTEGER);

    printf("\nEval:\n\n");

    printf("- Postfix: ");

    for (int i = 0; postfix[i] != '\0'; i++) {
        printf("%c ", postfix[i]);
    }

    printf("\n");

    for (int i = 0; postfix[i] != '\0'; i++) {

        char token = postfix[i];

        if (token >= '0' && token <= '9') {

            pushArrayStack(valueStack, token - '0');
        }
        else {

            int op1 = popArrayStack(valueStack);
            int op2 = popArrayStack(valueStack);

            switch (token)
            {
            case '+':
                pushArrayStack(valueStack, op2 + op1);
                break;

            case '-':
                pushArrayStack(valueStack, op2 - op1);
                break;

            case '*':
                pushArrayStack(valueStack, op2 * op1);
                break;

            case '/':
                pushArrayStack(valueStack, op2 / op1);
                break;
            }
        }

        printf("- Current: %c | Stack: ", token);

        printValueStack(valueStack);

        printf("\n");
    }

    int result = popArrayStack(valueStack);

    printf("\n- Result: %d\n", result);

    return result;
}
