#include <stdio.h>
#include <string.h>
struct matrix
{
    int a[19];
    int n;
};
int main()

{
    struct matrix x;
    struct matrix y;
    memset(&x.a[0],0,19 * sizeof(int));
    int *p;
    struct matrix *px = &x;
    p = &px -> a[1];
    printf("%d\n",*p);
    return 0;
}
