#include <stdio.h>

void move(int n,char s, char d, char temp)
{
    if(n == 1)
    {
        printf("%c ========> %c\n",s,d);
    }
    if(n > 1)
    {
        move(n-1,s,temp,d);
        move(1,s,d,temp);
        move(n-1,temp,d,s);
    }
}
int sum(int n)
{
    int temp;
    if( 1 == n)
    {
        temp = 1;
    }
    if(n > 1)
    {
        temp  = sum(n - 1) + n;
    }

    return temp;
}
int factorial(int n)
{
    int temp;
    if( 1 == n)
    {
        temp = 1;
    }
    if(n > 1)
    {
        temp = factorial(n - 1) * n;
    }
    return temp;
}

int fibonacci(int n)
{
    int temp = 0;
    if((0 == n) ||( 1 == n))
    {
        temp = 1;                 //return 1;
    }
    if(n >= 2)
    {
        temp = fibonacci(n-2) + fibonacci(n - 1);           //   return  fibonacci( n - 1) + fibonacci(n - 2)

    }
    return temp;

}


void rshow(int a[],int n)
{
    if(1 == n)
    {
        printf("%d  ",a[0]);
    }
    if( n > 1)
    {
        printf("%d  ",a[n-1]);
        rshow(a,n-1);
    }
}

void to_binary(unsigned int n)
{
    int rt;
    rt  = n%2;
    if(n >= 2)
    {
    to_binary(n / 2);
    }
    putchar('0' + rt);
    
}

int main()
{
    // int n;
    // scanf("%d",&n);
    // int b = sum(n);
    //int a=factorial(n);
    //printf("natural_sum is%d,factorial_ is %d\n",b,a);
    //int temp = fibonacci(n);
    //printf("%d \n",temp);
   // int a[10] = {1,2,3,4,5,6,7,8,9,10};
    //rshow(a,10);
    unsigned int n = 5;
    to_binary(n);
    return 0;
}
