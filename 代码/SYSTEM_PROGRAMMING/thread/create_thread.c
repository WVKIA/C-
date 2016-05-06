#include <stdio.h>
#include <pthread.h>

void *start(void * arg)
{
    int * p = arg;
    while(0 != *p)
    {
        printf("thread \n");
        sleep(2);
    }
    printf("thread end\n");
    return NULL;
}
int main()
{
    int rt;
    pthread_t pt;
    int quit = 1;
    rt = pthread_create(&pt,NULL,start,&quit);
    if(0 != rt)
    {
        fprintf(stderr,"can't create thread\n");
        return -1;
    }
    while(1)
    {
        scanf("%d",&quit);
        if(0 == quit)
        {
            break;
        }
    }
    pthread_join(pt,NULL);
    return 0;
}

