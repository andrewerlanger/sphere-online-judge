#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STR_LEN 10
#define SUB_LEN 5
#define INPUT_LINES 3

typedef struct node
{
    char string[STR_LEN + 1];
    char substring[SUB_LEN + 1];
    bool found;
}
node;

int main(void)
{
    //initialize string + substring
    node array[INPUT_LINES];
    char flush;

    //INPUT: prompt user for strings + store values
    for (int i = 0; i < INPUT_LINES; i++)
    {
        //get string + substring from user
        scanf("%s", array[i].string);
        scanf("%s", array[i].substring);

        //flush 'enter' input in buffer
        while ((flush = getchar()) != '\n' && flush != EOF)
        {}

        //set found to false
        array[i].found = false;

        //search for substring within string
        for (int j = 0; j <= SUB_LEN; j++)
        {
            if (strncmp(array[i].string + j, array[i].substring, SUB_LEN) == 0)
            {
                array[i].found = true;
            }
        }
    }

    //OUTPUT: print true + false values
    for (int k = 0; k < INPUT_LINES; k++)
    {
        if (array[k].found == true)
        {
            printf("1\n");
        }
        else
        {
            printf("0\n");
        }
    }

    //success
    return 0;
}