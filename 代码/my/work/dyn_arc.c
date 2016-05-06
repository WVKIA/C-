#include <stdio.h>
#include <stdlib.h>

int main()
{
    double * ptd;
    int max;
    int number;
    int i = 0;

    puts("what is the maximum number of type double entries?");
    scanf("%d",&max);
    ptd = (double *)malloc(max * sizeof(double));
    if(ptd == NULL)
    {
        puts("memory allocation failed googdbye!");
        exit(EXIT_FAILURE);
    }
    puts("enter the value (q to quit):");
    while(i < max && scanf("%lf",&ptd[i]) == 1)
    {
        i ++;
    }
    printf("here are your %d entries :\n",number = i);

    for( i = 0; i < number; i++)
    {
        printf("%7.2f ",ptd[i]);
        if(i % 6 == 0)
        {
            putchar('\n');
        }
    }
    if(i % 7 != 0)
    {
        putchar('\n');
    }
    puts("done!");
    free(ptd);

    return 0;
}
