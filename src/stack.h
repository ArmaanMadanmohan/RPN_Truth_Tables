#define MAX_SIZE 1000

struct stack {
    int arr[MAX_SIZE];
    int top;
};

void setStack(struct stack *stack);
void push(int element, struct stack *stack);
int pop(struct stack *stack);
void clear(struct stack *stack);

