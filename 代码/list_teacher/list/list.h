#ifndef __LIST_H__
#define __LIST_H__

#define offset(type,member)  ((unsigned long)(&((type *)0)->member))

#define container_of(ptr,type,member)  ((type *)((unsigned long)(ptr)-offset(type,member)))
struct listhead
{
    struct listhead *pre;
    struct listhead *next;
};

#define list_for_each(ptr,phead)  for(ptr=phead->next;ptr!=phead;ptr=ptr->next)

#define list_for_each_pre(ptr,phead)  for(ptr=phead->pre;ptr!=phead;ptr=ptr->pre)

#define list_for_each_safe(ptr,ptr1,phead)  for(ptr=phead->next,ptr1=ptr->next;ptr!=phead;ptr=ptr1,ptr1=ptr1->next)
extern void list_add_pre(struct listhead *phead,struct listhead *pnew);
extern void list_add_tail(struct listhead *phead,struct listhead *pnew);
extern void list_del(struct listhead *pdel);

#endif
