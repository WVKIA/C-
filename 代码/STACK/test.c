#include <stdio.h>
#include "mystack.h"
#include <stdlib.h>
int main()
{
    int i;
    int *p = NULL;
    struct mystack  mysk ;
    init_mystack(&mysk);
    scanf("%s",buf);
    for(i = 0;i < strlen(buf);i++)
    {
        if(isdigit(buf[i]))
        {
            *p = buf[i];
            printf("%d",*p);
            push(&mysk,p);
        }
        else
        {
            ch = 
        }
    }
    while(!empty(&mysk))
    {
        p = mysk.pop(&mysk);
        printf("%d\n",*p);
        free(p);
    }
    return 0;
    


}
