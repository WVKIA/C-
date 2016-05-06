#include <stdio.h>
int main()
{
    char name[11],name1[11];
    int count;

    printf("please enter 2 names\n");
    count = scanf("%5s %10s",name,name1);
    printf(" i read the %d names %s and %s\n",count,name,name1);

    return 0;
}
