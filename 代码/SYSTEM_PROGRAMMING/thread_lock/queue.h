#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <pthread.h>
struct node
{
    void *data;

    struct node *next;

};
struct myqueue
{
    pthread_cond_t cond;
    pthread_mutex_t lock;
    struct node * head;
    struct node * tail;
    int (*put)(struct myqueue * myque,void * data);
    void *(* get)(struct myqueue * myque);
    int (*empty)(struct myqueue * myque);
    void * (*peek)(struct myqueue * myque);
    int (*clear)(struct myqueue * myque);

};

extern void init_myqueue(struct myqueue *myque );
#endif

