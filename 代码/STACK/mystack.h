#ifndef __MYSTACK_H__
#define __MYSTACK_H__

#include <stdio.h>
struct node
{
    void *data;
    struct node *next;
};

struct mystack
{
    struct node *phead;
    int (*push)(struct mystack *, void *);
    void *(*pop)(struct mystack *);
    int (*empty)(struct mystack *);
    void *(*peek)(struct mystack *);
    int (*clear)(struct mystack *);
};

extern int init_mystack(struct mystack *mysk);

#endif
