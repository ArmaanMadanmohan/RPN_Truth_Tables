#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/**
 * Initializes the given stack by setting its top index to -1.
 *
 * @param stack The stack to be initialized.
 */
void setStack(struct stack *stack) {
    stack->top = -1;
}

/**
 * Pushes the given element onto the stack, if there is space available.
 *
 * @param element The element to be pushed onto the stack.
 * @param stack   The stack onto which the element is to be pushed.
 */
void push(int element, struct stack *stack) {
    if (stack->top == MAX_SIZE-1) {
        printf("Cannot push element %d\n", element); //prints error if stack full.
        return;
    }
    //assigns element to incremented position in stack
    stack->arr[++stack->top] = element; 
}

/**
 * Clears the stack by resetting its top index to 0.
 *
 * @param stack The stack to be cleared.
 */
void clear(struct stack *stack) {
    stack->top = 0;
}

/**
 * Pops and returns the top element from the stack if available.
 *
 * @param stack The stack from which to pop an element.
 * @return      The popped element if the stack is not empty, or -1 if the stack is empty.
 */
int pop(struct stack *stack) {
    if (stack->top == -1) {
        printf("Not enough operands in expression\n"); //prints error if stack empty.
        return -1;
    }
    return stack->arr[stack->top--]; //decrements index for top element.
}
