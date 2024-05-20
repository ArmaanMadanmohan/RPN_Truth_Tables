#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ttable.h"

struct stack stack;

/**
 * The main function that parses command-line arguments, validates inputs,
 * and calls the necessary functions to evaluate and print the RPN expression.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 on successful execution, 1 on error.
 */
int main(int argc, char* argv[]) { 
    int numVariables = atoi(argv[1]);
    if (validateArguments(argc, numVariables, argv[2]) == 1) {
        return 1;
    }   
    printInitial(numVariables, argv[2]);
    evalRPN(numVariables, argv[2]); 
    return 0;
}

/**
 * Prints the initial table header with variable names, expression, and result placeholders.
 *
 * @param numVar Number of variables in the RPN expression.
 * @param expression The RPN expression to evaluate.
 */
void printInitial(int numVar, char *expression) {
    //prints all variable characters.
    for (int i = 0; i < numVar; i++) {
        printf("%c ", 'a' + i);
    }
    printf(": %s : Result\n", expression);
    //BASE_CHARS represents the base number of '=' characters when printing the table header. This is increased depending on the formula provided. 
    for (int i = 0; i < BASE_CHARS + 2*numVar + (int) strlen(expression); i++) { 
        printf("=");
    }
    printf("\n");
}

/**
 * Evaluates a Reverse Polish Notation (RPN) expression and prints the truth table.
 *
 * @param numVars Number of variables in the RPN expression.
 * @param expression The RPN expression to evaluate.
 */
void evalRPN(int numVars, char *expression) {
    char *str = expression;
    setStack(&stack);

    int rows = 1 << numVars; //equivalent to 2^numVars.
    int result = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = numVars - 1; j >= 0; j--) {
            printf("%d ", (i >> j) & 1);
        }
        printf(": ");
        size_t c = 0;

        //iterate through expression
        while (str[c] != '\0') {
            if (str[c] >= 'a' && str[c] <= 'z') {
                int variable = (i >> (numVars - (str[c] - 'a') -  1) & 1); //calculates how much to bit shift the counter to obtain the value of the variable.
                printf(" ");
                push(variable, &stack);
            } else if (str[c] == '1' || str[c] == '0') {
                printf(" ");
                push((int) str[c] - '0', &stack); //'1' or '0' character is converted to 1 or 0 integer.
            } else { 
                if (str[c] == '-') { 
                    result = operation('-', pop(&stack), 0); //only pops one element for negation operator.
                } else {
                    result = operation(str[c], pop(&stack), pop(&stack));
                }
                //result is pushed back on to the stack for further use.
                push(result, &stack);
                printf("%d", result);
            }
            c++;
        }
        printf(" :   %d\n", pop(&stack));
    }
}

/**
 * Performs the specified logical operation on two operands.
 *
 * @param operator The logical operator.
 * @param operand1 The first operand.
 * @param operand2 The second operand.
 * @return The result of the logical operation. Defaults to -1.
 */
int operation(char operator, int operand2, int operand1) {
    switch (operator) {
        case ('|'):
            return operand1 | operand2;
        case('&'):
            return operand1 & operand2;
        case('-'):
            return !operand2;
        case('#'):
            return operand1 ^ operand2;
        case('='):
            return operand1 == operand2;
        case('>'): 
            return !operand1 | operand2;
        default: 
            return -1;
    }
}

/**
 * Validates command-line arguments and the RPN expression for correctness.
 *
 * @param argLength Number of command-line arguments.
 * @param numVariables Number of variables in the RPN expression.
 * @param expression The RPN expression to evaluate.
 * @return 0 if arguments are valid, 1 otherwise.
 */
int validateArguments(int argLength, int numVariables, char *expression) {
    if (argLength != 3) {
        printf("Invalid number of arguments.\n");
        return 1;
    }
    char *str = expression;
    size_t i = 0;
    int operands = 0;
    int operators = 0;

    //while loop that iterates through string.
    while (str[i] != '\0') { 
        //if the character isnt a lowercase letter, returns the default value for the operation method, and isn't '0' or '1', print an error.
        if (!(str[i] >= 'a' && str[i] <= 'z') && (operation(str[i], 0, 0) == -1) && (str[i] != '0' && str[i] != '1')) {
            printf("Invalid character.\n");
            return 1;
        } else if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] == '1' || str[i] == '0')) {
            operands++;
        } else if (str[i] != '-') { //if it is a non-negation operator then increase the counter.
            operators++;
        }
        i++;
        //checks whether the length of the string is greater than 1000.
        if (i > 1000) {
            printf("Invalid string. Must be no greater than 1000 characters.\n");
            return 1;
        }
    }
    //checks if the formula is correctly constructed.
    if (operators != (operands - 1)) {
        printf("Invalid formula.\n");
        return 1;
    }    
    //checks if the variable number is outside the range.
    if (numVariables < 1 || numVariables > 26) {
        printf("Invalid number of variables. Must be between 1-26 inclusive.\n");
        return 1;
    }
    return 0;
}
