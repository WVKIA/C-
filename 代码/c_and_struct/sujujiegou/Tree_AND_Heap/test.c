#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int data;
    struct node *next;
};
void insert(struct node **phead,int data)
{
    struct node *ptmp = *phead;
    struct node *p = malloc(sizeof(struct node));
    p->data = data;
    p->next = NULL;
    if(NULL == *phead)
    {
        *phead = p;
        return ;
    }
    while(NULL != ptmp->next)
    {
        ptmp = ptmp->next;
    }
    ptmp->next = p;
}
void destroy(struct node *phead)
{
    struct node *q = NULL;
    struct node *p = phead;
    while(p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    phead = NULL;
}
struct node* revese(struct node *phead)
{
    struct node *new = NULL;
   
    if(phead->next == NULL || phead == NULL)
    {
        
        return phead;
    }
    else
    {
        new = revese(phead->next);
        phead->next->next = phead;
        phead->next = NULL;
        return new;
    }

}
void show(struct node *phead)
{
    while(phead != NULL)
    {
        printf("%d   ",phead->data);
        phead = phead->next;
    }
}
int main()
{
    struct node *phead = NULL;
    insert(&phead,9);
    insert(&phead,90);
    insert(&phead,8);
    insert(&phead,56);
    show(phead);
    phead = revese(phead);
    show(phead);
}

