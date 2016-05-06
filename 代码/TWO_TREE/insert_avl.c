#include <stdio.h>
void insert(struct node **phead,struct node *s)
{
    struct node *q = NULL;

    struct node *a = *phead;
    struct node *f = NULL;
    
    struct node *pt = *phead;
    if(*phead == NULL)
    {
        *phead = s;
        return ;
    }
    
    while(pt!= NULL)
    {
        if(pt->bf != 0)
        {
            a = pt;
            f = q;
        }


        q  =pt;
        if(pt->data > s->data)
        {
            pt = pt->left;
        }
        else
        {
            pt = pt->right;
        }
    }
    if(q->data > s->data)
    {
        q->left = s;
    }
    else
    {
        q->right = s;
    }
    pt = a;
    while(pt != s)
    {
        if(pt->data > s->data)
        {
            pt->bf++;
            pt = pt->left;
        }
        else
        {
            pt->bf--;
            pt = pt->right;
        }
    }
    if(a->bf < 2 && a->bf >-2)
    {
        return ;
    }
    if(a->bf == 2)
    {
        b = a->left;
        if(b->bf == 1)
        {
            p = ll_rotate(a);
        }
        else
        {
            p = lr_rorate(a);
        }
    }
    else if(a->bf == -2)
    {
        b = a->right;
        if(b->bf == 1)
        {
            p = rl_rotate(a);
        }
        else
        {
            p = rr_rotate(a);
        }
    }
    if(f == NULL)
    {
        f = p;
    }
    else
    {
        if(f->left == a)
        {
            f->left = p;
        }
        else
        {
            f->rchild = p;
        }
    }
}


