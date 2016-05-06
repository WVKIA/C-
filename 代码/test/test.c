#include <stdio.h>
int func(int *p)
{
    printf("func\n");
    return 0;
}
int sum(int * a)
{
    return 0;
}
int main()
{
    int ( * temp [10])(int *) = {func , sum};
    int (*(* a)[10])(int *) = &temp;
    (*a[0][0])(NULL);


    int a;
    int *a;
    short a[10];
    short * a[10];
    int * ((*a)(int *));
    short (*a)[10];
    short * (*a[10])(short *);
    l


    return 0;
}
