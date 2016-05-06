#include <stdio.h>
void interchange(int *, int *);
int main()
{
    int x = 5,y = 10;

    printf("priginally x = %d,and y = %d",x,y);
    interchange(&x,&y);
    printf("now x= %d and y = %d\n",x,y);
    return 0;
}

void interchange(int * u, int * v)
{
    int temp;

    temp = *u;
    *u = *v;
    *v = temp;
}


