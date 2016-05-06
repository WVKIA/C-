#include <stdio.h>
#include <stdlib.h>
#define M 20
struct stack 
{
    void * data[M];
    int top;
};
void init_stack(struct stack *p)
{
    p->top = -1;
    return ;
}
int empty(struct stack *p)
{
    if(p->top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void push(struct stack *p,void *x)
{
    if(p->top == M-1)
    {
        return ;
    }
    else
    {
        p->top += 1;
        p->data[p->top] = x;
        return ;
    }
}
void * pop(struct stack *p)
{
    void *x = NULL;
    if(empty(p))
    {
        fprintf(stderr,"empty\n");
        return NULL;
    }
    x = p->data[p->top];
    p->top--;
    return x;
}
void destroy(struct stack *p)
{
    if(p)
    {
        free(p);
    }
    p = NULL;
    return ;
}
int main()
{
    int i;
    int *n = NULL;
    struct stack *p = malloc(sizeof(struct stack));
    init_stack(p);
    for(i = 0;i < 8;i++)
    {
        n = malloc(sizeof(int));
        *n = i;
        push(p,n);
    }
    while(!empty(p))
    {
        n = pop(p);
        printf("%d  ",*n);
    }
    destroy(p);

}
