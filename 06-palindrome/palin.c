#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_DIGITS 1000000
#define MAX_T 100

//node structure
typedef struct struct_node
{
    char* P;
    bool found;
}
struct_node;

//functions
void check(struct_node* ch_node, int start, int end);
void convert(struct_node* con_node, int start, int end);
bool all_nine(struct_node* nine_node, int start, int end);
void palin(struct_node* pal_node, int start, int end);
void mirror(struct_node* mir_node, int start, int end);

int main(void)
{
    //initialize t as char array
    char t_array[MAX_T + 1];
    char temp[MAX_DIGITS + 1];

    //prompt user for t + clean up
    fgets(t_array, MAX_T + 1, stdin);

    //convert to t to int
    int t = atoi(t_array);

    //declare node array
    struct_node node[t];

    //MAIN INPUT
    for (int i = 0; i < t; i++)
    {
        //get input from user
        fgets(temp, MAX_DIGITS + 1, stdin);

        //count digits + swap '\n'
        int end = strlen(temp) - 2;
        temp[end + 1] = '\0';

        //check user input for non-numbers
        for (int z = end; z >= 0; z--)
        {
            if (!isdigit(temp[z]))
            {
                temp[z] = '\0';
                end--;
            }

            else break;
        }

        //transfer temp to node
        node[i].P = malloc(sizeof(char) * (end + 3));
        strncpy(node[i].P, temp, end + 3);

        //clear leading zeros
        int zeros = 0, nums = 0;
        for (int y = 0; y <= end; y++)
        {
            if (node[i].P[y] == 48)
            {
                zeros++;
            }

            else break;
        }

        //if all zeros
        if (zeros == (end + 1) && end > 0)
        {
            node[i].P[1] = '\0';
            end = 0;
        }

        //else if numbers in there
        else if (zeros > 0 && end > 0)
        {
            for (int x = zeros; x <= end + 1; x++)
            {
                node[i].P[nums] = node[i].P[x];
                nums++;
            }
            end = nums - 2;
        }

        //perform converstion
        convert(&node[i], 0, end);
    }

    //MAIN OUTPUT
    for (int j = 0; j < t; j++)
    {
        printf("%s\n", node[j].P);
        free(node[j].P);
    }

    //success
    return 0;

}

void convert(struct_node* con_node, int start, int end)
{
    //check for palindrome
    con_node->found = false;
    check(con_node, start, end);
    if (con_node->found == true)
    {
        //case 1: all nines
        if (all_nine(con_node, start, end))
        {
            //set first digit to 1
            con_node->P[start] = 49;

            //set middle digits to zero
            int temp = start + 1;
            while (con_node->P[temp] != '\0')
            {
                con_node->P[temp] = 48;
                temp++;
            }

            //set final digit to 1 + add nul terminator
            con_node->P[temp] = 49;
            con_node->P[temp + 1] = '\0';
        }

        //case 2: all other palindromes
        else
        {
            palin(con_node, start, end);
        }
    }

    //case 3: non-palindromes
    else
    {
        mirror(con_node, start, end);
    }

}

bool all_nine(struct_node* nine_node, int start, int end)
{
    if (nine_node->P[start] == 57)
    {
        //okay first number is 9, let's check the rest
        int temp = start + 1;
        while (nine_node->P[temp] == 57)
        {
            temp++;
        }

        //if they're all 9, return true
        if (temp >= end)
        {
            return true;
        }
    }

    return false;
}

void palin(struct_node* pal_node, int start, int end)
{
    //declare some variables
    int left = 0, right = 0;

    //even number of digits
    if ((end + 1) % 2 == 0)
    {
        //assign values to left and right
        right = (end + 1) / 2;
        left = right - 1;
    }

    //odd number of digits
    else
    {
        right = (end + 1) / 2;
        left = right;
    }

    //keep searching for nines
    while (pal_node->P[left] == 57 && left >= start && right <= end)
    {
        if (left != right)
        {
            pal_node->P[left] = 48;
        }

        pal_node->P[right] = 48;
        left--;
        right++;
    }

    //adjust other values
    if (left != right)
    {
        pal_node->P[left]++;
    }

    pal_node->P[right]++;

    //return to main
    return;
}

void mirror(struct_node* mir_node, int start, int end)
{
    //declare some variables
    int left = 0, right = 0;
    int l, r;

    //even number of digits
    if ((end + 1) % 2 == 0)
    {
        //assign values to left and right
        right = (end + 1) / 2;
        left = right - 1;
    }

    //odd number of digits
    else
    {
        right = (end + 1) / 2;
        left = right;
    }

    //save original variables
    int original_left = left;
    int original_right = right;

    //search for point at which numbers don't match
    while (mir_node->P[left] == mir_node->P[right] && left >= start && right <= end)
    {
        left--;
        right++;
    }

    //case 1: left side is bigger
    if (mir_node->P[left] > mir_node->P[right])
    {
        for (l = left, r = right; l >= start; l--, r++)
        {
            mir_node->P[r] = mir_node->P[l];
        }
    }

    //case 2: right side is bigger
    else
    {
        //reset left + right values
        right = original_right;
        left = original_left;

        //check for nine
        if (mir_node->P[right] == 57)
        {
            while (mir_node->P[right] == 57 && right <= end)
            {
                mir_node->P[right] = 48;
                mir_node->P[right + 1]++;
                mir_node->P[left - 1]++;
                right++;
                left++;
            }
        }

        //increase middle number(s) if no nine found
        else
        {
            mir_node->P[left]++;
            for (l = left, r = right; l >= start; l--, r++)
            {
                mir_node->P[r] = mir_node->P[l];
            }
        }

        //perform mirror operation
        for (l = original_left, r = original_right; l >= start; l--, r++)
        {
            mir_node->P[r] = mir_node->P[l];
        }
    }

}

void check(struct_node* ch_node, int start, int end)
{
    if (end <= start)
    {
        ch_node->found = true;
        return;
    }

    else if (ch_node->P[start] == ch_node->P[end])
    {
        check(ch_node, start + 1, end - 1);
    }

    return;
}