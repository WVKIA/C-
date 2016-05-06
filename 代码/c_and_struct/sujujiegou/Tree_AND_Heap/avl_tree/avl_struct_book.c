#include <stdio.h>
#include <stdlib.h>
struct node 
{
    int data;
    int bf;
    struct node *lchild,*rchild;
};
struct node *ll_rotate(struct node *a)
{
    struct node *b = NULL;
    b = a->lchild;
    a->lchild = b->rchild;
    b->rchild = a;
    a->bf = b->bf = 0;
    return b;
}
struct node *rr_rotate(struct node *a)
{
    struct node *b;
    b = a->rchild;
    a->rchild = b->lchild;
    b->lchild = a;
    a->bf= b->bf = 0;
    return b;
}
struct node lr_rotate(struct node *a)
{
    struct node *b = NULL;
    struct node *c = NULL;

    b = a->lchild;
    c = b->rchild;

    a->lchild = c->rchild;
    b->rchild = c->lchild;

    c->lchild = b;
    c->rchild = a;

    if(c->bf == 1)
        {
            a->bf = -1;
            b->bf = 0;
        }
    else if(c->bf == -1)
    {
        a->bf = 0;
        b->bf = -1;
    }
    else
    {
        a->bf = 0;
        b->bf = 0;
    }
    c->bf = 0;
    return (c);
}
struct node *rl_rotate(struct node * a)
{
    struct node *b = NULL;
    struct node *c = NULL;

    b = a->rchild;
    c = b->lchild;

    a->rchild = c->lchild;
    b->lchild = c->rchild;

    c->lchild = a;
    c->rchild = b;

    if(c->bf == 1)
    {
        a->bf = 0;
        b->bf = -1;

    }
    else if(c->bf == -1)
    {
        b->bf = 0;
        a->bf = 1;
    }
    else
    {
        a->bf = b->bf = 0;
    }
    c->bf = 0;
    return c;
}

