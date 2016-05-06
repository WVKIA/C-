#ifndef __HEAD_H__
#define __HEAD_H__
enum
{
    T_BCAST,
    T_SCAST,
    T_REGIST
};
struct cnode
{
    int fd;
    char name[20];
    struct cnode *next;
};
struct head
{
    char sname[20];
    char dname[20];
    unsigned int type;
    unsigned int msglen;

};

#define HEADLEN (sizeof(struct head))

void add(struct cnode **,struct cnode *);
void del(struct cnode **,struct cnode *);
void destroy(struct cnode **);
void show(struct cnode *);
struct cnode *find_by_fd(struct cnode *phead,int);
struct cnode *find_by_name(struct cnode *phead,char *);
#endif
