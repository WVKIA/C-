#include <stdio.h>
#include <stdlib.h>
#include "admin.h"

int addadmin(struct alladmin *admin,struct admin *adm)
{
    struct alladmin *p=admin;
    if(NULL==p->phead)
    {
        p->phead=adm;
        return 0;
    }
    adm->next=p->phead;
    p->phead=adm;
    p->num++;
    return 0;
}
struct admin *findbyname(struct alladmin *admin,char *name)
{
    if(NULL==admin)
    {
        return NULL;
    }
    struct admin *adm=NULL;
    for(adm=admin->phead;NULL!=adm;adm=adm->next)
    {
        if(strcmp(adm->cname,name)==0)
        {
            return adm;
        }
    }
    return NULL;
}
struct admin *findbyfds(struct alladmin *admin,int fd)
{
    struct admin *p=NULL;
    if(admin->phead==NULL)
    {
        return NULL;
    }
    for(p=admin->phead;NULL!=p;p=p->next)
    {
        if(p->fd == fd)
        {
            return p;
        }
    }
    return NULL;
}
int deladmin(struct alladmin *admin,struct admin *adm)
{
    struct admin *p=NULL;
    if(admin->phead == adm)
    {
        admin->phead=admin->phead->next;
        free(adm);
        return 0;
    }

    for(p=admin->phead;NULL!=p;p=p->next)
    {
        if(p->next==adm)
        {
            break;
        }
    }
    if(NULL==p)
    {
        printf("NO this name\n");
        return -1;
    }
    p->next=adm->next;
    free(adm);
    return 0;
}




void showadmin(struct alladmin *admin)
{
    struct admin *adm=NULL;
    for(adm=admin->phead;NULL!=adm;adm=adm->next)
    {
        printf("name:%s\n",adm->cname);
    }
}
int init_alladmin(struct alladmin *admin)
{
    admin->phead=NULL;
    admin->num=0;
    return 0;
}
