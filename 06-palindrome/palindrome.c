#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define DIGIT_MAX 1000000
#define T_MAX 100

int no_zero(char* string, int end);
void category(char* string, int left, int right, int end);
void non_pal(char* string, int original_left, int left, int right, int end);
void non_nine(char* string, int left, int right);
void all_nine(char* string);

int main(void)
{
    //declare arrays for t1
    char t1[T_MAX + 1];

    //prompt user for t value
    fgets(t1, T_MAX, stdin);
    if (!isdigit(t1[0]))
    {
        return 1;
    }

    //check for ints
    for (int a = 0; a < T_MAX; a++)
    {
        if (!isdigit(t1[a]))
        {
            t1[a] = '\0';
            break;
        }
    }

    //convert to to int + declare array
    int t2 = atoi(t1);
    char* array[t2];

    //MAIN INPUT
    for (int b = 0; b < t2; b++)
    {
        //(re)initialize temp array
        char temp[DIGIT_MAX + 1] = {'\0'};

        //get number from user
        //fgets(temp, DIGIT_MAX + 1, stdin);
        fflush(stdin);
        scanf("%s", temp);

        //calculate int length + end
        int length = strlen(temp);
        int end = length - 1;

        //clean up non-digits from end of number
        for (int c = end; c >= 0; c--)
        {
            if (!isdigit(temp[c]))
            {
                temp[c] = '\0';
                end--;
            }

            else break;
        }

        //allocate memory for array[b]
        array[b] = malloc(sizeof(char) * (end + 3));
        if (!array[b])
        {
            return 2;
        }

        //copy temp to array[b] + nul terminate final value
        strncpy(array[b], temp, end + 3);

        //remove leading zeros + update end
        end = no_zero(array[b], end);
        if (end < 0)
        {
            return 3;
        }
        array[b][end + 1] = '\0';

        //calculate left + right
        int left = end / 2;
        int right;

        //odd number (left = right)
        if (end % 2 == 0)
        {
            right = left;
        }

        //even number (left < right)
        else
        {
            right = left + 1;
        }

        //determine category + convert
        category(array[b], left, right, end);
    }

    //MAIN OUTPUT: print palindromes + free memory
    for (int d = 0; d < t2; d++)
    {
        printf("%s\n", array[d]);
        free(array[d]);
    }

    //success
    return 0;
}

int no_zero(char* string, int end)
{
    //initialize counter
    int counter = 0;

    //calculate zeros before number
    while (string[counter] == 48)
    {
        counter++;
    }

    //case 1: no leading zeros or single zero
    if (counter <= 1 || end == 0)
    {
        return end;
    }

    //case 2: number is all zeros
    else if (counter > 1 && end > 0 && !isdigit(string[counter]))
    {
        //set nul terminator as second digit
        string[1] = '\0';
        end = 0;
        return end;
    }

    //case 3: leading zeros followed by number
    if (counter > 0 && end > 0 && isdigit(string[counter]))
    {
        //move non-zero digits into first array positions
        int pos = 0;
        while (isdigit(string[counter]))
        {
            string[pos] = string[counter];
            counter++;
            pos++;
        }

        string[pos] = '\0';
        end = pos - 1;
        return end;
    }

    //case 4: error
    else
    {
        return -1;
    }
}

void category(char* string, int left, int right, int end)
{
    //initialize all_nine
    bool nines = true;

    //initialize original left + right
    int original_left = left;
    int original_right = right;

    //scan number from inside out
    while (string[left] == string[right] && left >= 0 && right <= end)
    {
        //search for non-nine
        if (string[left] != 57 || string[right] != 57)
        {
            nines = false;
        }
        left--;
        right++;
    }

    //case 1: number is non-palindrome
    if (left >= 0 && right <= end)
    {
        non_pal(string, original_left, left, right, end);
        return;
    }

    //case 2: non-nine palindrome
    else if (left < 0 && right > end && nines == false)
    {
        non_nine(string, original_left, original_right);
        return;
    }

    //case 3: nine-palindrome
    else
    {
        all_nine(string);
        return;
    }

}

void non_pal(char* string, int original_left, int left, int right, int end)
{
    //perform initial converstion if right > left
    if (string[right] > string[left])
    {
        //update left value
        left = original_left;

        //dealing with nines
        while (string[left] == 57 && left >= 0)
        {
            string[left] = 48;
            left--;
        }

        //updating number
        string[left]++;
    }

    //mirror left side on right
    for (int a = 0; a <= original_left; a++)
    {
        string[end - a] = string[a];
    }

    return;
}

void non_nine(char* string, int left, int right)
{
    //dealing with zeros
    while (string[left] == 57 && string[right] == 57)
    {
        string[left] = 48;
        string[right] = 48;
        left--;
        right++;
    }

    //updating numbers
    if (left != right)
    {
        string[right]++;
    }
    string[left]++;

    return;
}

void all_nine(char* string)
{
    //converstion step 1: set first digit to 1
    string[0] = 49;

    //converstion step 2: set middle digits to 0
    int counter = 1;
    while (string[counter] == 57)
    {
        string[counter] = 48;
        counter++;
    }

    //converstion step 3: set final digit to 1 and adjust nul pointer
    string[counter] = 49;
    string[counter + 1] = '\0';

    //return true
    return;
}