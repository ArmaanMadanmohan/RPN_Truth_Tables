#define BASE_CHARS 11

void evalRPN(int numVars, char *expression);
int operation(char operator, int operand1, int operand2); 
void printInitial(int numVar, char *expression);
int validateArguments(int argLength, int numVariables, char *expression);
