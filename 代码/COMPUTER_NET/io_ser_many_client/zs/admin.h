#ifndef __ADMIN_H_
#define __ADMIN_H_

struct admin
{
    char cname[20];
    int fd;
    struct admin *next;
};
struct alladmin
{
    struct admin *phead;
    unsigned int num;
};
extern int addadmin(struct alladmin *admin,struct admin *adm);
extern struct admin *findbyname(struct alladmin *admin,char *name);
extern void showadmin(struct alladmin *admin);
extern struct admin *findbyfds(struct alladmin *admin,int fd);
extern int deladmin(struct alladmin *admin,struct admin *adm);
extern int init_alladmin(struct alladmin *admin);
#endif


