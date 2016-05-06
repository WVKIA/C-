#include <stdlib.h>
#include <stdio.h>
struct node 
{
    void * data;
    struct node *next;
};
struct queue
{
    struct node *front;
    struct node *rear;
};
void init(struct queue *p)
{
    p->front = NULL;
    p->rear = NULL;
}
int empty(struct queue *p)
{
    if(p&&p->front == NULL && p->rear == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void insert(struct queue *p,void *data)
{
    struct node * q = malloc(sizeof(struct node ));
    if(q == NULL)
    {
        fprintf(stderr,"can't craete\n");
        return ;
    }
    q->next = NULL;
    q->data = data;

    if(empty(p))
    {
        p->front = p->rear = q;
        return ;
    }
    else
    {
        p->rear->next = q;
        p->rear = q;
    }
}
void *get(struct queue *p)
{
    
    void *x = NULL;
    struct node *ptmp = NULL;
    if(empty(p))
    {
        fprintf(stderr,"empty\n");
        return NULL;
    }
    ptmp = p->front;
    p->front = p->front->next;
    x = ptmp->data;
    free(ptmp);
    return x;
}
int main()
{
    int i;
    int *n = NULL;
    int *x = NULL;
    struct queue *q = malloc(sizeof(struct queue));
    if(NULL == q)
    {
        fprintf(stderr,"can't create\n");
        return -1;
    }
    init(q);
    for(i = 0;i < 8;i++)
    {
        n = malloc(sizeof(int));
        *n = i;
        insert(q,n);

    }
    for(i = 0;i < 8;i++)
    {
        x = get(q);
        printf("%d",*x);
    }

}
