#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#define MAX_INPUT 15

int minimum(int a, int b);
int maximum(int a, int b);
int calc(const int stall_array[], int cow_array[], int num_cows, int current_min);
void sort(int numbers[], int start, int end, int size);
void merge(int numbers[], int start1, int end1, int start2, int end2, int size);


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

    //loop for t cases
    for (int loop = 0; loop < t; loop++)
    {
        //declare n, c + combined input
        char int_n[7] = {'\0'};
        char int_c[7] = {'\0'};
        char combined_input[MAX_INPUT];

        //capture user input
        fgets(combined_input, MAX_INPUT, stdin);

        //split combined input into n + c
        bool space_found = false;
        for (int a = 0; a < MAX_INPUT; a++)
        {
            //counters for n + c
            int n_counter = 0;
            int c_counter = 0;

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

        //initialize int max + cow_pos
        int max = 0;
        int cow_pos = num_cows - 2;

        //declare cow_array
        int cow_array[num_cows];

        //fill stall_array with user input
        int stall_array[num_stalls];
        for (int b = 0; b < num_stalls; b++)
        {
            scanf("%d", &stall_array[b]);
        }

        //flush stdin
        char flush;
        while ((flush = getchar()) != 10 && flush != EOF);

        //sort stall_array in ascending order
        sort(stall_array, 0, num_stalls - 1, num_stalls);

        //plant cows in place
        for (int a = 0; a < num_cows - 1; a++)
        {
            cow_array[a] = a;
        }
        cow_array[num_cows - 1] = num_stalls - 1;

        max = maximum(max, calc(stall_array, cow_array, num_cows, max));

        //loop until cow 1 is in it's final resting place
        while (cow_array[1] != num_stalls - (num_cows - 1))
        {
            //if cow has space ahead: move cow forward
            if (cow_array[cow_pos] + 1 < cow_array[cow_pos + 1])
            {
                cow_array[cow_pos]++;
                max = maximum(max, calc(stall_array, cow_array, num_cows, max));
            }

            //else if cow has no space ahead + we need to cycle forward
            else if (cow_array[cow_pos] != num_stalls - (num_cows - cow_pos))
            {
                //cycle forward to furthest cow that has space ahead
                while (cow_array[cow_pos] + 1 == cow_array[cow_pos + 1])
                {
                    cow_pos++;
                }
            }

            //else cow has no space ahead + we need to cycle back
            else
            {
                //cycle back to last cow that has space ahead
                while (cow_array[cow_pos] - 1 == cow_array[cow_pos - 1])
                {
                    cow_pos--;
                }
                cow_pos--;

                //move cows back if new round reached
                if (cow_array[cow_pos] == cow_pos)
                {
                    for (int b = cow_pos + 1, c = 0; b <= num_cows - 2; b++, c++)
                    {
                        cow_array[b] = cow_array[cow_pos] + c + 2;
                    }
                }
            }
        }

        //print result
        printf("%d\n", max);
    }
}

int minimum(int a, int b)
{
    return (a < b) ? a : b;
}

int maximum(int a, int b)
{
    return (a > b) ? a : b;
}

int calc(const int stall_array[], int cow_array[], int num_cows, int current_min)
{
    int min_distance = INT_MAX;

    for (int i = 0; i < num_cows - 1; i++)
    {
        //calculate minimum distance
        min_distance = minimum(min_distance, stall_array[cow_array[i+1]] - stall_array[cow_array[i]]);

        //return if minimum is less than current min
        if (min_distance <= current_min)
        {
            return min_distance;
        }
    }

    return min_distance;
}

void sort(int numbers[], int start, int end, int size)
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

void merge(int numbers[], int start1, int end1, int start2, int end2, int size)
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