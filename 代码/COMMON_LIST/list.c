#include "list.h"

void add_listhead_pre(struct listhead *phead,struct listhead *pstu)
{
    phead->pre->next = pstu;
    pstu->pre = phead->pre;
    pstu->next = phead;
    phead->pre = pstu;
}

void add_list_next(struct listhead *phead,struct listhead *pstu)
{
    phead->next->pre = pstu;
    pstu->next = phead->next;
    pstu->pre = phead;
    phead->next = pstu;
}
void list_del(struct listhead *pdel)
{
    pdel->pre->next = pdel->next;
    pdel->next->pre = pdel->pre;
}

