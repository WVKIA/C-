#include <stdio.h>
int main()
{

}
void radix(int a[],int num,int min,int max)
{
    int b[num];
    while(max != 0)
    {
        max = max/10;
        i++;
    }
    for(t= 0;t<i;t++)
    {
        for(i = 0;i < num;i++)
        {
            int tmp = a[i]%pow(10,t)/ pow(10,t-1);
            b[tmp] = a[i];
        }
        
    }
}
