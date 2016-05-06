#include "mystack.h"
#include <stdlib.h>
int push(struct mystack *mysk, void *data)
{
    struct node *p = NULL;
    p = malloc(sizeof(struct node));
    if(NULL == p)
    {
        printf("no memory\n");
        return -1;
    }
    p->data = data;
    p->next = mysk->phead;
    mysk->phead = p;
    return 0;


}
void * pop(struct mystack *mysk)
{
    void * p = NULL;
    struct node * tmp = NULL;
    if(empty(mysk))
    {
        return NULL;
    }
    tmp = mysk->phead;
    mysk->phead = mysk->phead->next;
    p = tmp->data;
    free(tmp);
    return p;

}
int empty(struct mystack *mysk)
{
    return NULL == mysk->phead;
}

void * peek(struct mystack *mysk)
{
    void * p = NULL;
    if(empty(mysk))
    {
        printf("err \n");
        return NULL;
    }
    p = mysk->phead->data;
    return p;
}

int clear(struct mystack *mysk)
{
    while(!empty(mysk))
    {
        pop(mysk);
    }
}
int init_mystack(struct mystack *mysk)
{
    mysk->phead = NULL;
    mysk->pop = pop;
    mysk->push = push;
    mysk->empty = empty;
    mysk->clear = clear;
    mysk->peek = peek;
}

