#include <stdio.h>
int main()
{
    char line[20];

    while(fgets(line,20,stdin) != NULL)
    {
        fputs(line,stdout);
    }
    return 0;
}
