#ifndef __LIST_H__
#define __LIST_H__
struct list
{
    struct list *pre;
    struct list *next;
};
void list_add(struct list *phead,struct list *p);
void list_del(struct list *p);
#endif

