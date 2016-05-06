#include <stdio.h>
#include <stdlib.h>
char * int2str(int a)
{
    char buf[100];
    int i = 0;
    int n = 1;
    int k = 0;
    char * p = NULL; 
    while(a >= n)                   //while(0 != a/10)
    {
        n *=10;
        
    }
    while( 0 != a)                       //while(a >= n)

    {
        i = a/(n/10);
        i += '0';
        buf[k] = (char)i;
        k++;
        a %= (n/10);
        n /= 10;
    }
    p = malloc(k );
    if(NULL == p)
    {
        return NULL;

    }
    for(i = 0; i <= k; i++)
    {
        p[i] = buf[i];
    }
    p[k] = '\0';
    return p;
}
int main()
{
    char *p;
    p = int2str(234);
    if(NULL == p)
    {
        printf("failed\n");
        return -1;
    }
    printf("%s\n",p);
    return 0;
}


