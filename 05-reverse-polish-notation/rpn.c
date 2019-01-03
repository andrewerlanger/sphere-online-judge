#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

//push, pop + is_operator functions
int is_operator(char c);
void push(stack* push_stack, char push_ch);
char pop(stack* pop_stack);

int main(void)
{
    //initialize some variables
    int t = 0, value = 0, q_counter = 0;
    char* number = malloc(sizeof(char)*MAX_T);

    //prompt user for t expressions
    fgets(number, MAX_T, stdin);

    //convert t to int, then free memory
    t = atoi(number);
    free(number);

    //check t falls within required range
    if (t < 1 || t > 100)
    {
        return 1;
    }

    //initialize array
    node array[t];

    //INPUT: capture expressions from user + convert to RPN
    for (int i = 0; i < t; i++)
    {
        //set stack top to zero + reset q counter
        array[i].node_stack.top = 0;
        q_counter = 0;

        //capture expression from user + calculate string length
        fgets(array[i].input_array, MAX_LENGTH, stdin);
        int input_array_length = strlen(array[i].input_array);

        //append null terminator to string
        array[i].input_array[input_array_length - 1] = '\0';

        //convert expression to RPN
        for (int j = 0; j < input_array_length - 1; j++)
        {
            //value of is_operator
            value = is_operator(array[i].input_array[j]);

            //break for null terminator
            if (array[i].input_array[j] == '\0')
            {
                break;
            }

            //dealing with characters
            else if (isalpha(array[i].input_array[j]))
            {
                array[i].output_array[q_counter] = array[i].input_array[j];
                q_counter++;
            }

            //dealing with operators
            else if (value > 0)
            {
                //pop operators from stack with greater precedence
                while (array[i].node_stack.top > 0 && is_operator(array[i].node_stack.stack_array[array[i].node_stack.top - 1]) > value)
                {
                    array[i].output_array[q_counter] = pop(&array[i].node_stack);
                    q_counter++;
                }
                //push current operator onto stack
                push(&array[i].node_stack, array[i].input_array[j]);
            }

            //dealing with left brackets
            else if (array[i].input_array[j] == '(')
            {
                push(&array[i].node_stack, array[i].input_array[j]);
            }

            //dealing with right brackets
            else if (array[i].input_array[j] == ')')
            {
                //while not left bracket: pop operators to output
                while (array[i].node_stack.stack_array[array[i].node_stack.top - 1] != '(')
                {
                    array[i].output_array[q_counter] = pop(&array[i].node_stack);
                    q_counter++;
                }
                pop(&array[i].node_stack);
            }

            //dealing with unexpected characters
            else
            {
                printf("unexpected character in expression number %d:\n", i + 1);
                printf("\n\'%c\'\n\n", array[i].input_array[j]);
                return 1;
            }
        }

        //pop remaining operators to output
        while (array[i].node_stack.top > 0)
        {
            if (is_operator(array[i].node_stack.stack_array[array[i].node_stack.top - 1]) > 0)
            {
                array[i].output_array[q_counter] = pop(&array[i].node_stack);
                q_counter++;
            }
            else
            {
                pop(&array[i].node_stack);
            }
        }
        //append NUL terminator
        array[i].output_array[q_counter] = '\0';
    }

    //OUTPUT: print converted expression
    for (int k = 0; k < t; k++)
    {
        printf("%s\n", array[k].output_array);
    }

    //success
    return 0;
}

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

//function that pushes values to the stack
void push(stack* push_stack, char push_ch)
{
    push_stack->stack_array[push_stack->top] = push_ch;
    push_stack->top++;
    return;
}

//function that pops values from the stack
char pop(stack* pop_stack)
{
    char pop_ch = pop_stack->stack_array[pop_stack->top - 1];
    pop_stack->top--;
    return pop_ch;
}