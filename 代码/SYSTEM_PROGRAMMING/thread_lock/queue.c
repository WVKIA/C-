#include <stdlib.h>
#include "queue.h"
#include <stdio.h>
int put(struct myqueue * myque,void * data)
{
    struct node * p = malloc(sizeof(struct node));
    p->next = NULL;
    if(NULL == p)
    {
        printf("no memroy\n");
        return -1;
    }
    p->data = data;
     
    if((myque->head == NULL) && (myque->tail == NULL))
    {
        myque->tail = p;
        myque->head = p;
    }
    else
    {
        myque->tail->next =p;
        myque->tail = p;
    }
    return 0;
}
int empty(struct myqueue * myque)
{
    return NULL == myque->head;
}
void *get(struct myqueue * myque)
{
    void * p = NULL;
    struct node * tmp = NULL;
    if(empty(myque))
    {
        return NULL;
    }
    tmp = myque->head;
    myque->head = myque->head->next;
    if(NULL == myque->head)
    {
        myque->tail = NULL;
    }
    p = tmp->data;
    free(tmp);
    return p;

}
void * peek(struct myqueue * myque)
{
    void * p = NULL;
    
    if(empty(myque))
    {
        return NULL;
    }
    p = myque->head->data;
    return p;
}
int clear(struct myqueue * myque)
{
    while(!empty(myque))
    {
        get(myque);
    }
}
void init_myqueue(struct myqueue * myque)
{
    myque->head = myque->tail = NULL;
    myque->put = put;
    myque->get = get;
    myque->empty = empty;
    myque->peek = peek;
    myque->clear = clear;
    pthread_cond_init(&myque->cond,NULL);
    pthread_mutex_init(&myque->lock,NULL);
}

