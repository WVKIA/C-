#include <stdio.h>
#include <string.h>
int main()

{
    short a[1024] = {1,2,3,4,5,6,7};
    short *pa[2] = { a + 1, a + 5};
    short **ppa = pa;
    *ppa = a + 5;
    return 0;
}

