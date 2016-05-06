#include <stdio.h>
#define TIAOHE(x,y) (1/(  ((1/(x))+(1/(y)))/2    ))
int main()
{
    double x,y;
    x = 2;
    y = 4;
    double z = TIAOHE(x,y);
    printf("%g\n",z);
    return 0;
}
