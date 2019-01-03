#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int fact(int x);

int main(void)
{
    int n;
    char number[20];
    do
    {
        //prompt user for number + check
        printf("number: ");
        fgets(number, sizeof(number), stdin);

        if (sscanf(number, "%d", &n) != 1)
        {
            printf("that's not a number. try again.\n\n");
            for (int i = 0; i < 3; i++)
            {
                sleep(1);
                printf(". ");
            }
            printf("\n\n");
            sleep(1);
            n = -1;
        }
    }

    while (n == -1);

    //calculate + print factorial
    unsigned long long final = fact(n);
    printf("\n ***factorial of %d: %llu*** \n\n", n, final);

    //success
    return 0;
}

int fact(int x)
{
    if (x < 1)
    {
        return 0;
    }
    else if (x == 1)
    {
        return 1;
    }
    else
    {
        return (x * fact(x - 1));
    }
}