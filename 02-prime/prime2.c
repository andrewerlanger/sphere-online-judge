#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MIN 0
#define MAX 1
#define SIZE 2
#define START 3

bool isprime(int a);

int main(void)
{
    //get t from user + check
    int t;
    scanf("%d", &t);
    if (t < 0 || t > 10)
    {
        return 1;
    }

    //declare 2D-array + fill
    unsigned int array[SIZE][t];
    for (int i = 0; i < t; i++)
    {
        //assign user-generated min + max to array
        scanf("%d" "%d", &array[MIN][i], &array[MAX][i]);

        //check correct usage
        if (array[MIN][i] >= array[MAX][i] || array[MIN][i] < 1 ||
        array[MAX][i] > 1000000000 || array[MIN][i] - array[MAX][i] <= 100000)
        {
            return 1;
        }
    }

    //run isprime function on each test case
    for (int j = 0; j < t; j++)
    {
        //add line-break
        printf("\n");

        //initialize temp min + max
        int min = array[MIN][j];
        int max = array[MAX][j];

        //print 2 if necessary
        if (min <= 2)
        {
            printf("%d\n", 2);
        }

        //adjust min to odd number if necessary
        if (min % 2 == 0)
        {
            min++;
        }

        //print primes in range
        for (int k = min; k <= max; k += 2)
        {
            if (isprime(k) == true)
            {
                printf("%d\n", k);
            }
        }
    }

    //that's all folks
    return 0;

}

bool isprime(int a)
{
    //return false for (less than or equal to) 1
    if (a <= 1)
    {
        return false;
    }

    //return true for 2 or 3
    else if (a == 2 || a == 3)
    {
        return true;
    }

    //check whether number takes form 6 * k ± 1
    else
    {
        int k = round((double)a/6);
        if (6 * k + 1 == a || 6 * k - 1 == a)
        {
            //check whether number has factors other than itself and 1
            int root = sqrt(a);
            for (int m = START; m <= root; m += 2)
            {
                if (a % m == 0)
                {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}