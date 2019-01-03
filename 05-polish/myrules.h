#define MAX_EXPRESSIONS 100
#define MAX_LENGTH 400
#define MAX_T 10

//stack structure for operators + brackets
typedef struct stack
{
    char stack_array[MAX_LENGTH];
    int top;
}
stack;

//node structure for input, stack + output
typedef struct node
{
    char input_array[MAX_LENGTH];
    stack node_stack;
    char output_array[MAX_LENGTH];
}
node;

//function that checks for operators + assigns them values
int is_operator(char c)
{
    if (c == '^')
    return 3;

    else if (c == '/' || c == '*')
    return 2;

    else if (c == '+' || c == '-')
    return 1;

    else return 0;
}

//function that pops values from the stack
char pop(stack* pop_stack)
{
    char pop_ch = pop_stack->stack_array[pop_stack->top - 1];
    pop_stack->top--;
    return pop_ch;
}

//function that pushes values to the stack
void push(stack* push_stack, char push_ch)
{
    push_stack->stack_array[push_stack->top] = push_ch;
    push_stack->top++;
    return;
}