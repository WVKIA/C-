#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
struct stack* creat(void)
{
    struct stack *p = malloc(sizeof(struct stack));
    if(NULL != p)
    {
        p->top = NULL;
    }
    return p;
}
int empty(struct stack *p)
{
    return p->top == NULL;
}

int push(struct stack *p,void * x)
{
    struct node *ptmp = malloc(sizeof(struct node));
    if(!ptmp)
    {
        fprintf(stderr,"can't create\n");
        return -1;
    }
    ptmp->data = x;
    ptmp->next = p->top;
    p->top = ptmp;
    return 1;
}
void * pop(struct stack *p)
{
    struct node * q = NULL;
    void * x = NULL;
    if(!empty(p))
    {
        x = p->top->data;
        q = p->top;
        p->top = p->top->next;
        free(q);
    }
    return x;
}
void * peek(struct stack *p)
{
    void * x= NULL;
    if(!empty(p))
    {
        x = p->top->data;
    }
    return x;
}
void destroy(struct stack *p)
{
    struct node *ptmp = NULL;
    struct node *q = NULL;
    if(p)
    {
        q = p->top;
        while(q)
        {
            ptmp = q;
            q = q->next;
            free(ptmp);
        }
        free(p);
    }
    p = NULL;
}
