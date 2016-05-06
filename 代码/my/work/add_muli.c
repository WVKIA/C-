#include <stdio.h>
int add_mul();
int main()
{
    add_mul();
    return 0;

}

int add_mul(void)
{
    int i,temp;
    int a,b;
    printf("enter low and upper integer limits:\n");
    scanf("%d %d",&a,&b);
    int temp1 = 0;
    for(i = a; i <= b; i++)
    {
        temp1 =temp1 + i * i; 
    }
    printf("the sum of the squares from %d to %d is %d\n",a*a,b*b,temp1);

}



