#include <stdio.h>

int main(void)
{
    int primes[5] = { 42 };
    int numprimes = 0;

    primes[numprimes++] = 2;

    for (int i = 0; i < 5; i++)
    {
        printf("primes[%d] = %d\n", i, primes[i]);
    }

    printf("numprimes = %d\n", numprimes);

    return 0;
}