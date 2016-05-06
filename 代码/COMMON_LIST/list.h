#ifndef __LIST_H__
#define __LIST_H__

struct listhead
{
    struct listhead *pre;
    struct listhead *next;
};
extern void add_list_pre(struct listhead *,struct listhead *);
extern void add_list_next(struct listhead *,struct listhead *);
extern void list_del(struct listhead *);
#endif
