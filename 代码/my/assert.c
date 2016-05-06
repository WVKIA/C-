#include <stdio.h>
#define NDEBUG
#include <math.h>
#include <assert.h>
int main()
{
    double x,y,z;
    puts("enter a pari of number");
    while(scanf("%lf %lf",&x,&y) ==2 && (x != 0 || y != 0))
    {
        z = x * x - y*y;
        assert(z > 0);
        printf("answer is %lf\n",sqrt(z));
    }
    return 0;
}
