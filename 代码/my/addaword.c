#include <stdio.h>
#include <stdlib.h>
#define MAX 40

int main()
{
    FILE * fp;
    char words[MAX];

    if((fp = fopen("words","a+")) == NULL)
    {
        fprintf(stdout,"can't open\"word\"file\n");
        exit(1);
    }
    puts("enter words to add to thefile ;press the enter");
    puts("key at the beganingng of a line to terminate");
    while(gets(words) == NULL &&  words[0] != '\0')
    {
        fprintf(fp,"%s",words);
    }
    puts("file contents: ");
    rewind(fp);
    while(fscanf(fp,"%s",words) == 1)
    {
        puts(words);
    }
    if(fclose(fp) != 0)
    {
        fprintf(stderr, "error closing file\n");
    }
    return 0;
}
