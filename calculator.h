#ifndef CALCULATOR_H
#define CALCULATOR_H

int precedence(char op);

void infixToPostfix(char* infix, char* postfix);

int evalPostfix(char* postfix);

#endif
