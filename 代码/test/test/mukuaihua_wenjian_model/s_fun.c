#include "s_fun.h"
#include <stdio.h>
static int add1(int a, int b)
{
    int temp = a + b;
    printf("%d\n",temp);
}
void init_jia(struct func * pst)
{
    pst->jia = add1; 
}
