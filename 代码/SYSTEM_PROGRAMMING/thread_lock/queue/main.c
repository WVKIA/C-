#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
struct mytask
{
    char c;
};
void showtask(struct mytask *p)
{
    printf("%c\n",p->c);
    sleep(1);
}

int quit;
pthread_mutex_t mylock;
void * start(void * arg)
{
    struct myqueue *myq = arg;
    struct mytask *p = NULL;
    while(quit == 0)
    {
        if(!myq->empty(myq))
        {
            pthread_mutex_lock(&mylock);
            p = myq->get(myq);
            pthread_mutex_unlock(&mylock);
            showtask(p);
            free(p);
        }
    }
    return NULL;
}
int main()
{
    pthread_t pt;
    pthread_mutex_init(&mylock,NULL);
    int n;
    int i = 0;
    struct myqueue myq;
    init_myqueue(&myq);
    struct mytask *myt = NULL;
    char ch[1024];
    n = pthread_create(&pt,NULL,start,&myq);
    if(n != 0)
    {
        fprintf(stderr,"can't create\n");
        return -1;
    }
    while(1)
    {
        i =0;
        scanf("%s",ch);
        if(strcmp(ch,"quit") == 0)
        {
            quit = 1;
            break;
        }
        
        
            while('\0' != ch[i]) 
            {
                pthread_mutex_lock(&mylock);
                myt = malloc(sizeof(struct mytask));
                myt->c = ch[i];
                myq.put(&myq,myt);
                i++;
                pthread_mutex_unlock(&mylock);
            }
        
    }
    
    return 0;
}
