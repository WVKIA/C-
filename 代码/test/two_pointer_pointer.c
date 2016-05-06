#include <stdio.h>
int fun( int **ch,int b);
int main(void)
{
    int *ch = NULL;
    int a = 9;
    ch = &a;
    int b = 8;
    fun(&ch,b);
    printf("%d\n",*ch);
    return 0;

}
int fun(int **ch,int b)
{
    *ch = &b;
    
}

