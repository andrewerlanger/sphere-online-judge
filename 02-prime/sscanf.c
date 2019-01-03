#include <stdio.h>

int main(void)
{
    //determine number of cases (t)
    int t;
    scanf("%d", &t);

    //declare array + initialize
    int array[2][t];
    for (int i = 0; i < t; i++)
    {
        scanf("%d" "%d", &array[0][i], &array[1][i]);
    }

    //print array
    for (int j = 0; j < t; j++)
    {
        printf("array[0][%d] = %d\n", j, array[0][j]);
        printf("array[1][%d] = %d\n", j, array[1][j]);
    }

    //success
    return 0;
}