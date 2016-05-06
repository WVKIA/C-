
#include "list.h"

void list_add_pre(struct listhead *phead,struct listhead *pnew)
{
    phead->next->pre = pnew;
    pnew->next = phead->next;
    pnew->pre  = phead;
    phead->next = pnew;
}
void list_add_tail(struct listhead *phead,struct listhead *pnew)
{
    phead->pre->next = pnew;
    pnew->pre = phead->pre;
    pnew->next = phead;
    phead->pre = pnew;
}
void list_del(struct listhead *pdel)
{
    pdel->pre->next = pdel->next;
    pdel->next->pre = pdel->pre;
}
