#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct queue
{
    int number;
    struct queue* next;
}
queue;

int main(void)
{
    //declare variables
    char input_string[10] = {'\0'};
    int n = 0;
    queue* head;
    queue* trav;
    queue* temp;
    queue* tail;
    queue* new_q;
    bool first_q = true;
    bool found = false;

    //take input from user
    while (fgets(input_string, sizeof(input_string), stdin) != NULL)
    {
        //check for enter
        if (strcmp(input_string, "\n") == 0)
        {
            break;
        }

        //convert string to int
        n = atoi(input_string);

        //check for correct number of digits
        if (n < -99 || n > 99)
        {
            break;
        }

        //check for 42
        if (n == 42)
        {
            found = true;
        }

        //commit number to memory only if 42 not found
        if (found == false)
        {
            //for first number
            if (first_q == true)
            {
                head = malloc(sizeof(queue));
                if (!head)
                {
                    return 1;
                }
                head->number = n;
                head->next = NULL;
                tail = head;
                first_q = false;
            }

            //for other numbers
            else
            {
                //create new queue
                new_q = malloc(sizeof(queue));
                if (!new_q)
                {
                    return 1;
                }

                //add values to queue
                new_q->number = n;
                new_q->next = NULL;

                //update tail
                tail->next = new_q;
                tail = new_q;
            }
        }
    }

    //print output for user
    trav = head;
    while (trav != NULL)
    {
        //print number
        printf("%d\n", trav->number);

        //update trav + free
        temp = trav->next;
        free(trav);
        trav = temp;
    }

    //success
    return 0;
}