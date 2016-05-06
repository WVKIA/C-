#include <stdio.h>
int main(void)
{
    int i;
    for(i = 0; i < 5; i++)
    {
            char ch[6];
            for(j = 0; j < i; j ++)
            {
                ch[j] = '$';
            }
            for(a = 0; a < 6; a++)
            {
                printf("%c",ch[a]);
            }
    }
    return 0;
}
