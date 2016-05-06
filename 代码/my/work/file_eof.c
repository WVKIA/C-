#include <stdio.h>
#include <stdlib.h>
int main()
{
    int ch;
    FILE *fp;
    char fname[50];

    puts("enter the name of file");
    scanf("%s",fname);
    fp = fopen(fname,"r");
    if(NULL == fp)
    {
        puts("filed to open file");
        exit(1);
    }
    while((ch = getc(fp)) != EOF)
    {
        putchar(ch,stdout);
    }
    fclose(fp);
    return 0;
}
