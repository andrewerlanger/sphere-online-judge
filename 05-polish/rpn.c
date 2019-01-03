#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "myrules.h"

int main(void)
{
    //initialize some variables
    int t = 0, value = 0, q_counter = 0;
    char* number = malloc(sizeof(char)*MAX_T);

    //prompt user for t expressions
    fgets(number, MAX_T, stdin);

    //convert t to int
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
                    array[i].output_array[q_counter] = array[i].node_stack.stack_array[array[i].node_stack.top - 1];
                    array[i].node_stack.top--;
                    q_counter++;
                }
                //push current operator onto stack
                array[i].node_stack.stack_array[array[i].node_stack.top] = array[i].input_array[j];
                array[i].node_stack.top++;
            }

            //dealing with left brackets
            else if (array[i].input_array[j] == '(')
            {
                array[i].node_stack.stack_array[array[i].node_stack.top] = '(';
                array[i].node_stack.top++;
            }

            //dealing with right brackets
            else if (array[i].input_array[j] == ')')
            {
                //while not left bracket: pop operators to output
                while (array[i].node_stack.stack_array[array[i].node_stack.top - 1] != '(')
                {
                    array[i].output_array[q_counter] = array[i].node_stack.stack_array[array[i].node_stack.top - 1];
                    array[i].node_stack.top--;
                    q_counter++;
                }
                array[i].node_stack.top--;
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
                array[i].output_array[q_counter] = array[i].node_stack.stack_array[array[i].node_stack.top - 1];
                array[i].node_stack.top--;
                q_counter++;
            }
            else
            {
                array[i].node_stack.top--;
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

