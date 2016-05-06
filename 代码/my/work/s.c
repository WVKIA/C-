#include <stdio.h>
int main()
{
    int i,j;
    char a;
    for( i = 0; i < 6; i++)
    {
        for(j = 0,a = 'F'; j <= i; j++, a--)
        {
            printf("%c",a);
        }
        printf("\n");
    }
    return 0;


}


