#include <stdio.h>
void print2(int top, int bottom);
int main()
{
    int top = 3;
    int bottom = 1;
    print2(top, bottom);
    return 0;
}
void print2(int top, int bottom)
{
    int i,a,b;
    int temp = top - bottom;
    for(i = 0; i <= temp; i++)
    {
        a = top * top;
        b = top * top * top;
        printf("-----%d-----%d-----%d\n",top,a,b);
        top --;
    }
    return ;
}
