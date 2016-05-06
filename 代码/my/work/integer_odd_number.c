#include <stdio.h>

int  main()
{
    int n;
    int even_number = 0;
    int odd_number = 0;
    int  even_sum = 0;
    int odd_sum = 0;
    while((scanf("%d",&n) == 1) && (n != 0))
    {
        if(n % 2 == 0)
        {
            even_number ++;
            even_sum += n;
        }
        else
        {
            odd_number ++;
            odd_sum += n;
        }
    }
    float temp1 = even_sum / even_number;
    float temp2 = odd_sum / odd_number;

   printf("even_number %d , mean_even %f,odd_number %d, mean_odd %f",even_number,temp1,odd_number,temp2);
    return 0;
}

