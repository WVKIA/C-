#include <stdio.h>
int findint(int *pa,int n,int value,int *pr);
int main(void)
{
    int a[10] = {1,23,4,3,5,3,5,6,4,6};
    int r[10];
    int n,i;
    n = findint(a,10,0,r);
    printf("find %d dict\n",n);
    for(i = 0; i < n; i++)
    {
        printf(" the index is %d \n",r[i]);
    }
    return 0;
}

int i;
int counter = 0;

for(i = 0;i < n; i ++)
{
    if(pa[i] == value)
    {

        pr[counter] = i;
        counter++;
    }
}
return counter;
}

