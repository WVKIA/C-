#include <stdio.h>
#include <time.h>
#include "costomer.h"
long rand_number(p)
{
    p = p * 2 / 5;
    return p;
}
char * name_rand(long p,char  id[])
{
    int i;
    long a;
    char n;
    long b;
    for(i = 0;i < 19;i++)
    {
        a = p/26;
        n = (p % 26) + 'a';
        id[i] = n;
        if(a == 0)
        {
            break;
        }
        p = a;
    }
    if(i == 19)
    {
        id[i] = '\0';
    }
    else
    {
        id[i + 1] = '\0';
    }
}
long phone_rand(long p)
{
    return p;
}
char* id_rand(long p,char id[])
{
    int i;
    char n;
    long a,b;
    for(i = 0;i < 19;i++)
    {
        a = p/10;
        n = (p % 10) + '0';
        id[i] = n;
        if(a == 0)
        {
            break;
        }
        p = a;
        
    }
    if(i == 19)
    {
        id[i] = '\0';
    }
    else
    {
        id[i+1] = '\0';
    }
}
