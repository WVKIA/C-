#include <stdio.h>
#include <stdlib.h>
struct binnode
{
    elementtype element;
    struct binnode *leftchild;
    struct binnode *nextsibling;
};
struct collection
{
    int currentsize;
    struct binnode *thetree[maxsize];
};
struct binnode *combinetrees(struct binnode *t1,struct binnode *t2)
{
    if(t1->element > t2->element)
    {
        return combinetrees(t2,t1);
    }
    t2->nextsibling = t1->leftchild;
    t1->leftchild = t2;
    return t1;
}
struct collection * merge(struct collection * h1,struct collection *h2)
{
    struct binnode * t1;
    struct binnode *t2;
    struct binnode *carry = NULL;
    int i,j;

    if(h1->currentsize + h2->currentsize > capacity)
    {
        fprintf(stderr,"merge would exceed capacity\n");
        return NULL;
    }
    h1->currentsize += h2->currentsize;
    for(i = 0,j = 1;j <= h1->currentsize; i++, j*= 2)
    {
        t1 = h1->thetrees[i];
        t2 = h2->thetrees[i];

        switch( !!t1 + 2*!!t2 + 4 * !!carry)
        {

        }
    }
}
