#include <stdio.h>
int main()
{
    char ch;
    char buf[20];
    printf("enter the file name");
    scanf("%s",&buf);
    FILE * fp = fopen(buf,"r");
    ch = getc(fp);
    while(ch != EOF)
    {
        putchar(ch);
        ch = getc(fp);
    }
    return 0;
    
}
