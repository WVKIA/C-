#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

int main()
{
    int i;
    struct myqueue myque;
    int * p = NULL;
    init_myqueue(&myque);
    for(i = 0; i < 10; i++)
    {
        p = malloc(sizeof(int));
        *p = i;
        myque.put(&myque,p);
    }
    while(!empty(&myque))
    {
        p = myque.get(&myque);
        printf("%d\n",*p);
        free(p);
    }
    return 0;
}
