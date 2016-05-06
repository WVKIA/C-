#include "list.h"
void list_add(struct list *phead,struct list *p)
{
    phead->next->pre = p;
    p->next = phead->next;
    p->pre = phead;
    phead ->next  = p;
}
void list_del(struct list *p)
{
    p->pre->next = p->next;
    p->next->pre = p->pre;
}

