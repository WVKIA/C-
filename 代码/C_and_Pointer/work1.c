#include <stdio.h>

int main()

{
    int ch;
    int at_begining = 1;
    int line = 0;
    while((ch = getchar()) != EOF)
    {
        if(at_begining == 1)
        {
            at_begining = 0;
            line += 1;
            printf("%d ",line);
        }

        putchar(ch);
        if( ch == '\n')
        {
            at_begining = 1;
        }


    }
   
    return 0;
}
