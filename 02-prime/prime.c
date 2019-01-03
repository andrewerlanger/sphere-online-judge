#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_DIGITS 7

bool isprime(int a);

FILE* file_ptr;

int main(int argc, char* argv[])
{
    //check argc equals 2
    if (argc != 2)
    {
        printf("correct usage: ./prime number\n");
        return 1;
    }

    //convert argv[1] to int
    int t = atoi(argv[1]);

    //check 0 < t < 11
    if (t < 1 || t > 10)
    {
        printf("please select a number between 1 and 10, inclusive\n");
        return 1;
    }

    //prompt user for n
    unsigned int n;
    printf("int n: ");
    scanf("%d", &n);

    //prompt user for m
    unsigned int m;
    printf("int m: ");
    scanf("%d", &m);

    //check correct usage
    if (n >= m || n < 1 || m > 1000000000 || n - m <= 100000)
    {
        printf("correct usage: 1 <= m <= n <= 1000000000\nn - m <= 100000\n");
        return 1;
    }

    //prompt user for test cases
    int test[t];
    for (int i = 0; i < t; i++)
    {
        printf("test case #%d: ", i + 1);
        scanf("%d", &test[i]);
    }

    //prepare user for output
    printf("\nokay. here are your primes:\n\n");

    //adjust n to odd number if necessary
    if (n % 2 == 0)
    {
        n++;
    }

    //print 2 if necessary
    if (n == 1 || n == 3)
    {
        printf("%d\n", 2);
    }

    //open primes.txt
    file_ptr = fopen("primes.txt", "r");
    if (file_ptr == NULL)
    {
        printf("error opening file.\n");
    }

    //check for primes in range
    for (int j = n; j <= m; j += 2)
    {
        if (isprime(j) == true)
        {
            printf("%d\n", j);
        }
    }
    printf("\n");

    //print test cases
    rewind(file_ptr);
    for (int z = 0; z < t; z++)
    {
        if (isprime(test[z]) == true)
        {
            printf("%d\n", test[z]);
        }
    }

    //close primes.txt
    fclose(file_ptr);

    //success
    return 0;
}

bool isprime(int a)
{
    //return false for (less than or equal to) 1
    if (a <= 1)
    {
        return false;
    }

    //return false for even numbers above 2
    else if (a > 2 && a % 2 == 0)
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
            //read file + check for number
            unsigned int buffer;
            while (fscanf(file_ptr, "%d", &buffer))
            {
                if (feof(file_ptr))
                {
                    return false;
                }

                else if (buffer > a)
                {
                    fseek(file_ptr, -sizeof(buffer), SEEK_CUR);
                    return false;
                }

                else if (buffer == a)
                {
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}