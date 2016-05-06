#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
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
void * start(void * arg)
{
    struct myqueue *myq = arg;
    struct mytask *p = NULL;
    while(1)
    {
        /*
        if(!myq->empty(myq))
        {
            pthread_mutex_lock(&mylock);
            p = myq->get(myq);
            pthread_mutex_unlock(&mylock);
            showtask(p);
            free(p);
        }
        */

       pthread_mutex_lock(&myq->lock);
       while(myq->empty(myq))
       {
           if(1 == quit)
           {
               pthread_mutex_unlock(&myq->lock);
               goto end;
           }
           pthread_cond_wait(&myq->cond,&myq->lock);
       }
       p = myq->get(myq);
       pthread_mutex_unlock(&myq->lock);
       showtask(p);
       free(p);
    }
end:
    
    return NULL;
}
int main()
{
    int i;
    pthread_t pt[10];
    int n;
    struct myqueue myq;
    init_myqueue(&myq);
    struct mytask *myt = NULL;
    int flag; 
    int pid = open("fifo",O_RDONLY);
    if(pid == -1)
    {
        fprintf(stderr,"can't open the file\n");
        return -1;
    }

    n = pthread_create(&pt[0],NULL,start,&myq);
    n = pthread_create(&pt[1],NULL,start,&myq);
    n = pthread_create(&pt[2],NULL,start,&myq);
    if(n != 0)
    {
        close(pid);
        fprintf(stderr,"can't create\n");
        return -1;
    }
    while(1)
    {
        myt = malloc(sizeof(struct mytask));
        n = read(pid,myt,sizeof(struct mytask));
        if(n == 0)
        {

            quit = 1;
            pthread_cond_broadcast(&myq.cond);
            close(pid);
            break;
        }
        pthread_mutex_lock(&myq.lock);
        flag = myq.empty(&myq);
        myq.put(&myq,myt);
        pthread_mutex_unlock(&myq.lock);
        if(flag)
        {
            pthread_cond_broadcast(&myq.cond);
        }
    }
    while(i<10)
    {
        pthread_join(pt[i],NULL);
        i++;
    }
    close(pid);


    return 0;
}
