#include <stdlib.h>
#include <stdio.h>
struct node
{
    int n;
    struct node *next;
};
void showlist(struct node *p)
{
    while(NULL != p)
    {
        printf("%d  ",p->n);
        p = p->next;

    }
    printf("\n");
    return ;
}

struct node * find_n(struct node *p,int x)
{
  
    while(p != NULL)
    {
        if(p->n == x)
        {
            return p;
        }
        p = p->next;
    }
}
void rever(struct node **p)
{
    struct node *pcurrent = *p;
    struct node *pnew = NULL;
    struct node *pold = NULL;
    while(pcurrent != NULL)
    {
        pold = pcurrent->next;
        pcurrent->next = pnew;
        pnew = pcurrent;
        pcurrent = pold;
    }
    *p = pnew;

}
void del(struct node **pt,int x)
{
    struct node *p = *pt;
    struct node *pre = NULL;
    if(NULL == *pt)
    {
        fprintf(stderr,"can't del empty\n");
        return ;
    }
 if(p->n = x)
 {
     pre = *pt;
     *pt = (*pt)->next;
     free(pre);
     return ;
 }
 else{
    for(pre = p;p != NULL; pre = p,p = p->next)
    {
        
        if(p->n == x)
        {
           pre->next  = p->next;
           free(p);
           return ;
        }

     
    }
    printf("can't find the x\n");
    return ;
 }
}

void insert(struct node **pt,int x)
{
    struct node *p = *pt;
    struct node *ptmp = malloc(sizeof(struct node));
    ptmp->next = NULL;
    ptmp->n = x;
    if(NULL == *pt)
    {
        
        *pt = ptmp;
        return ;
    }
    while(p->next!= NULL)
    {
       p = p->next;
    }
    p->next = ptmp;
    return ;
}
void destroy(struct node *p)
{
    struct node *q = NULL;
    if(!p)
    {
        return ;
    }
    while(p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
}
void jion(struct node *p,struct node *q,struct node **m)
{
    while(p != NULL && q != NULL)
    {
    if(p->n < q->n)
    {
        p = p->next;
    }
    else if(p->n == q->n)
    {
        insert(m,p->n);
        p = p->next;
        q = q->next;
    }
    else
    {
        q = q->next;
    }
    }
}
void bing(struct node *p,struct node *q,struct node **t)
{
    struct node *m = NULL;
    struct node *ptmp = NULL;
    jion(p,q,&m);
    for(ptmp = p;ptmp != NULL;ptmp = ptmp->next)
    {
        insert(t,ptmp->n);
    }
    for(ptmp = m;ptmp!= NULL;ptmp = ptmp->next)
    {
        del(t,ptmp->n);
    }
    for(ptmp = q;ptmp!= NULL;ptmp=ptmp->next)
    {
        insert(t,ptmp->n);
    }
}
int main()
{
    int i;
    int *n = NULL;
    struct node *q = NULL;
    struct node *p = NULL;
    struct node *m = NULL;
    struct node *t = NULL;
    for(i = 0;i < 8;i++)
    {
        n = malloc(sizeof(int));
        *n = i;
     insert(&p,*n);
    }
    for(i = 4;i < 10;i ++)
    {
        n = malloc(sizeof(int));
        *n = i;
        insert(&q,*n);
    }
    *n = 7;
    showlist(p);
    showlist(q);
    jion(p,q,&m);
    bing(p,q,&t);
    showlist(t);
    showlist(m);
    rever(&m);
    showlist(m);
    del(&m,*n);
    showlist(m);
    destroy(t);
    destroy(p);
    destroy(m);
    destroy(q);
   
    
}
