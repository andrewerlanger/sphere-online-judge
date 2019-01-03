#include <stdio.h>
#include <limits.h>

void position(int cows[], int array[], int to_allocate, int first, int final);
int bigger(int a, int b);
int smaller(int a, int b);

int main(void)
{
    int min = 0;
    int num_stalls = 6;
    int num_cows = 4;
    int array[] = {1, 2, 4, 8, 9, 12};
    int cows[num_cows];
    cows[0] = array[0];
    cows[num_cows - 1] = array[stalls - 1];

    for (int i = 1; i < num_stalls - 1; i++)
    {
        for (int j = 1; j < num_cows - 1)
        {
            cows[1] = array[i];
            min = bigger(min, calc(cows, num_cows));
        }
    }

    printf("max min is: %d\n", min);

    return 0;

}
//to_allocate = 2; first = 1; final = 4
void position(int cows[], int array[], int total, int to_allocate, int first, int next_cow, int next_array, int final)
{
    //continue until all postions trialled
    while (first <= final - total + 1)
    {
        //when no cows left to allocate
        if (to_allocate == 0)
        {
            //calculate minimum
            next_array++;
        }

        //for the first cow
        else if (to_allocate == total)
        {
            cows[first_cow] = array[first_array];
            to_allocate--;
            next_cow++;
            next_array++;
        }

        //for all other cows
        else
        {
            cows[next] = array[next];
            next_cow++;
            next_array++;
        }

    }



}

int bigger(int a, int b)
{
    return (a > b) ? a : b;
}

int smaller(int a, int b)
{
    return (a < b ) ? a: b;
}


//cows_index = 1; array_index = 1; to_allocate = 3; final_index = 5
void reposition(int cows[], int array[], int to_allocate)
{
    if (to_allocate > 1)
    {
        cows[cows_index] = array[array_index];
        to_allocate--;
        cows_index++;
        array_index++;
        //cows_index = 2; array_index = 2; to_allocate = 2; final_index = 5
        position(cows, array, etc)

    }

    else if (to_allocate == 1 && array_index <= final_index)
    {
        cows[cows_index] = array[array_index]
        calculate(etc)
        position

    }