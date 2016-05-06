#include <stdio.h>
int main()
{
    int i,j;
    char a,b,c;
    scanf("%c",&a);
    int temp = a - 'A';
    for(i = 0; i <= temp; i++)
    {
        for(j = temp - i; j >= 0; j--)
        {
            printf(" ");
        }
        for(b = 'A';b <'A' + i; b++)
        {
            printf("%c",b);

        }
        for(c = 'A' + i; c >= 'A'; c--)
        {
            printf("%c",c);
        }
        printf("\n");
    }
    return 0;
}
