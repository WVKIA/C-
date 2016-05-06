#include <stdio.h>
#include <stdlib.h>
/*
char  * int2str( int a);
int main(void)
{
    int a = 1234;
    char *pa = int2str(a);
    printf("%s\n",pa);
    
    free(pa);
    return 0;
}

char * int2str( int a)
{
    char ch[100] = {0};
    
    int temp = a;
    int b ;
    int i = 0;
    int n = 1;
    while(a > n)
    {
        n *= 10;
        i++;
    }
    for(j = 0; j < i/2; j++)
    {
        b = ch[j];
        ch[j] = ch[i];
        ch[i] = b;
    }
    return ch;
}
*/
char * int2str(int a)
{
    char buf[100];
    int i = 0;
    int n = 0;
    char * p = NULL;                      // int n =1; 
    while( 0 != a)                       //while(a >= n)
    
    {
        i = a%10;
        i += '0';
        buf[n] = (char)i;
        n ++;
        a /= 10;
    }
    p = malloc(n + 1);
    if(NULL == p)
    {
        return NULL;

    }
    for (i = 0; i < n; i++)
    {
        p[i] = buf[n - 1 - i];
    }
    p[n] = '\0';
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

