#include <stdio.h>
int var1(int a, int b);
int var(int a, int b);
int main(void)
{

    int a;
    scanf("%d",&a);
    int b;
    scanf("%d",&b);
    printf("%d %d\n",var(a,b),var1(a,b));
    return 0;
}
int var(int a, int b)
{
    int j,temp;
    if(a < b)
    {
        temp = a;
        a = b;
        b = temp;
    }

    while(1)
    {
      
        j = a% b;
        if(j == 0)
        {
            temp = b;
            break;
        }
        else 
        {
            a = b;
            b = j;
        }
    }
    return temp;
}
int var1(int a, int b)
{
      int i = var(a,b);
      int temp = (a / i) * b;
      return temp;
}
