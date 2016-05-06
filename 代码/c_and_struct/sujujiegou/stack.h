#ifndef __STACK_H__
#define __STACK_H__

struct node
{
    void * data;
    struct node *next;
};
struct stack
{
    struct node *top;

};
struct stack *creat(void);
int empty(struct stack *);
int push(struct stack *,void *);
void *pop(struct stack *);
void *peek(struct stack *);
void destroy(struct stack *);
#endif
