#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_INPUT 15

int minimum(int a, int b);
void sort(unsigned long numbers[], int start, int end, int size);
void merge(unsigned long numbers[], int start1, int end1, int start2, int end2, int size);


int main(void)
{
    //how many test cases?
    char int_t[5];
    int t = 0;
    fgets(int_t, 5, stdin);

    //convert t to int
    if (!isdigit(int_t[0]))
    {
        return 1;
    }
    else
    {
        t = atoi(int_t);
    }

    //output array
    unsigned long output_array[t];

    //loop for t cases
    for (int loop = 0; loop < t; loop++)
    {
        //declare n, c + combined input
        char int_n[7] = {'\0'};
        char int_c[7] = {'\0'};
        char combined_input[MAX_INPUT];

        //capture user input
        fgets(combined_input, MAX_INPUT, stdin);
        int length = strlen(combined_input) - 1;

        //split combined input into n + c
        bool space_found = false;
        int n_counter = 0, c_counter = 0;
        for (int a = 0; a < length; a++)
        {
            //check for premature enter
            if (combined_input[a] == 10 && !space_found)
            {
                printf("incorrect use\n");
                return 1;
            }

            //has the space been found?
            else if (combined_input[a] == 32)
            {
                space_found = true;
            }

            //add to n if char is a digit
            else if (!space_found && isdigit(combined_input[a]))
            {
                int_n[n_counter] = combined_input[a];
                n_counter++;
            }

            //add to c if char is a digit
            else if (space_found && isdigit(combined_input[a]))
            {
                int_c[c_counter] = combined_input[a];
                c_counter++;
            }
        }

        //convert n + c to ints
        int num_stalls = atoi(int_n);
        int num_cows = atoi(int_c);

        //fill stall_array with user input
        unsigned long stall_array[num_stalls];
        for (int b = 0; b < num_stalls; b++)
        {
            scanf("%ld", &stall_array[b]);
        }

        //flush stdin
        char flush;
        while ((flush = getchar()) != 10 && flush != EOF);

        //sort stall_array in ascending order
        sort(stall_array, 0, num_stalls - 1, num_stalls);

        //calculate lo
        unsigned long lo = INT_MAX;
        for (int c = 0; c < num_stalls - 1; c++)
        {
            lo = minimum(lo, stall_array[c+1] - stall_array[c]);
        }

        //calculate hi
        unsigned long hi = stall_array[num_stalls-1] - stall_array[0];

        //while loop for binary search
        unsigned long target = 0;
        while (lo < hi)
        {
            //initialize relevant variables
            target = lo + (hi-lo)/2;
            int max_cows = 2;
            unsigned long current_distance = 0;

            //calculate cows required at optimal distance
            for (int d = 0; d < num_stalls - 1; d++)
            {
                if (current_distance < target)
                {
                    current_distance += (stall_array[d+1] - stall_array[d]);
                }
                else
                {
                    max_cows++;
                    current_distance = (stall_array[d+1] - stall_array[d]);
                }
            }

            //adjust lo + hi values
            if (max_cows <= num_cows)
            {
                hi = target;
            }

            else
            {
                lo = target + 1;
            }
        }

        //add value to output array
        output_array[loop] = target;
    }

    //print output
    for (int z = 0; z < t; z++)
    {
        printf("%ld\n", output_array[z]);
    }
}

int minimum(int a, int b)
{
    return (a < b) ? a : b;
}

void sort(unsigned long numbers[], int start, int end, int size)
{
    if (size == 1)
    {
        return;
    }
    else
    {
        int middle = (size / 2) + start - 1;
        sort(numbers, start, middle, middle - start + 1);
        sort(numbers, middle + 1, end, end - middle);
        merge(numbers, start, middle, middle + 1, end, size);
        return;
    }
}

void merge(unsigned long numbers[], int start1, int end1, int start2, int end2, int size)
{
    //declare temp array + initialize position
    int temp_array[size];
    int position = 0;
    int original_start = start1;

    //open while loop
    while (position < size)
    {
        //condition 1: start1 + start2 both valid
        if (start1 <= end1 && start2 <= end2)
        {
            if (numbers[start1] < numbers[start2])
            {
                temp_array[position] = numbers[start1];
                start1++;
            }
            else
            {
                temp_array[position] = numbers[start2];
                start2++;
            }

        }

        //condition 2: only start1 valid
        else if (start1 <= end1)
        {
            temp_array[position] = numbers[start1];
            start1++;
        }

        //condition 3: only start2 valid
        else if (start2 <= end2)
        {
            temp_array[position] = numbers[start2];
            start2++;
        }

        //update position
        position++;
    }

    //transfer numbers from temp array into numbers
    for (int j = 0; j < size; j++)
    {
        numbers[original_start] = temp_array[j];
        original_start++;
    }

    //return
    return;
}