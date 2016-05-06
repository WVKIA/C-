#include <stdio.h>
int main()

{
    int counter = 0;
    char ch;

    while((ch = getchar()) != '#')
    {
        counter ++;
        if(counter % 8 != 0)
        {
           printf(" %c :%d",ch,ch);
        }
        else
        {
            printf("\n");
            printf(" %c :%d",ch,ch);
        }
    }
    return 0;
}
