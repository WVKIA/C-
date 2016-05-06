#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chain.h"


static void listadd(struct allclient *a,struct cnode *p)
{
    p->next = a->phead;
    a->phead = p;
    a->num++;
}

static int addcnode(struct allclient *a,char *name,int fd)
{
    struct cnode *p = malloc(sizeof(struct cnode));
    if(NULL == p)
    {
        fprintf(stderr,"can not malloc\n");
        return -1;
    }
    strcpy(p->cname,name);
    p->fd = fd;
    p->next = NULL;
    listadd(a,p);
}
static int delcnode(struct allclient *a,int fd)
{
    struct cnode *pre = NULL;
    struct cnode *tmp = NULL;
    if(NULL == a->phead)
    {
        return 0;
    }
    else if(fd == a->phead->fd)
    {
        pre = a->phead;
        a->phead = a->phead->next;
        free(pre);
        pre=NULL;
        return 0;
    }
    else
    {
        pre = a->phead;
        tmp = pre->next;
        while(NULL != tmp)
        {
            if(tmp->fd == fd)
            {
                break;
            }
            pre = tmp;
            tmp = tmp->next;
        }
        if(NULL != tmp)
        {
            pre->next = tmp->next;
            free(tmp);
        }
    }
    return 0;
}
static struct cnode *findbyname(struct allclient *a,char *name)
{
    struct cnode *p = a->phead;
    while(NULL != p)
    {
        if(strcmp(p->cname,name) == 0)
        {
            break;
        }
        p=p->next;
    }
    return p;
}
static struct cnode *findbyfd(struct allclient *a,int fd)
{
    struct cnode *p = a->phead;
    while(NULL != p)
    {
        if(fd == p->fd)
        {
            break;
        }
        p=p->next;
    }
    return p;
}
int init_allclient(struct allclient *a)
{
    a->phead = NULL;
    a->num = 0;
    a->add = addcnode;
    a->del = delcnode;
    a->findbyname = findbyname;
    a->findbyfd = findbyfd;
}

