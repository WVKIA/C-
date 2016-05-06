#include <stdio.h>
int main()
{
    double pa[8];
    int i ;
    int j;
    for( i = 0; i < 8; i++)
    {
        printf("enter you number:");
        scanf("%lf",&pa[i]);
    }
    double pb[8];
    double temp;

    for( i = 0; i < 8; i++)
    {
        temp = 0;
        for(j = 0; j <= i; j++)
        {
            temp = temp + pa[j];
        }
        pb[i] = temp;
    }

    for( i = 0; i < 8; i++)
    {
        printf("%lf ",pa[i]);
        printf("%lf ",pb[i]);
    }
    return 0;
}


