#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

#define MAX_INPUT 15

int minimum(long a, long b);
void sort(long numbers[], int start, int end, int size);
void merge(long numbers[], int start1, int end1, int start2, int end2, int size);


int main(void)
{
    //for flushing stdin
    char flush = '\0';

    //how many test cases?
    int t = 0;
    scanf("%d", &t);

    //flush stdin
    while ((flush = getchar()) != 10 && flush != EOF);

    //error check
    if (t < 1 || t > INT_MAX)
    {
        return 1;
    }

    //output array
    long output_array[t];

    //loop for t cases
    for (int loop = 0; loop < t; loop++)
    {
        //capture user input
        int num_stalls = 0;
        int num_cows = 0;
        scanf("%d %d", &num_stalls, &num_cows);

        //flush stdin
        while ((flush = getchar()) != 10 && flush != EOF);

        //error check
        if (num_stalls < 2 || num_stalls > 100000 || num_cows < 2 || num_cows > num_stalls)
        {
            return 1;
        }

        //fill stall_array with user input
        long stall_array[num_stalls];
        for (int b = 0; b < num_stalls; b++)
        {
            scanf("%ld", &stall_array[b]);
            while ((flush = getchar()) != 10 && flush != EOF);
        }

        //sort stall_array in ascending order
        sort(stall_array, 0, num_stalls - 1, num_stalls);

        //calculate lo
        long lo = LONG_MAX;
        for (int c = 0; c < num_stalls - 1; c++)
        {
            lo = minimum(lo, stall_array[c+1] - stall_array[c]);
        }

        //calculate hi
        long hi = (stall_array[num_stalls - 1] - stall_array[0])/(num_cows - 1);

        //while loop for binary search
        long target = 0;
        long current_max = 0;
        while (lo <= hi)
        {
            //initialize relevant variables
            target = lo + (hi-lo)/2;
            int max_cows = 1;
            long current_distance = 0;

            //calculate cows required at optimal distance
            for (int d = 1; d < num_stalls; d++)
            {
                if (current_distance + (stall_array[d] - stall_array[d - 1]) < target)
                {
                    current_distance += stall_array[d] - stall_array[d - 1];
                }
                else
                {
                    max_cows++;
                    current_distance = 0;
                }
            }

            //adjust current_max
            if (max_cows >= num_cows)
            {
                current_max = target;
            }

            //adjust lo + hi values
            if (max_cows < num_cows)
            {
                if (hi == lo)
                {
                    break;
                }
                else
                {
                    hi = target;
                }
            }
            else
            {
                lo = target + 1;
            }
        }

        //add value to output array
        output_array[loop] = current_max;
    }

    //print output
    for (int z = 0; z < t; z++)
    {
        printf("%ld\n", output_array[z]);
    }
}

int minimum(long a, long b)
{
    return (a < b) ? a : b;
}

void sort(long numbers[], int start, int end, int size)
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

void merge(long numbers[], int start1, int end1, int start2, int end2, int size)
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