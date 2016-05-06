#include <stdio.h>
#include "head.h"
#include <string.h>
#include <stdlib.h>
void add(struct cnode **phead,struct cnode * node)
{
    struct cnode *p = *phead;
    if(*phead == NULL)
    {
        *phead = node;
        return ;
    }
    else
    {
        while(p->next != NULL)
        {
            p = p->next;
        }
        p->next = node;
    }
}
struct cnode *find_by_fd(struct cnode *phead,int fd)
{
    while(phead != NULL)
    {
        if(fd == phead->fd)
        {
            return phead;
        }
        phead = phead->next;
    }
    printf("can't find the fd!\n");
    return NULL;
}
struct cnode * find_by_name(struct cnode *phead,char *name)
{
    while(phead != NULL)
    {
        if(strcmp(name,phead->name) == 0)
        {
            return phead;
        }
        phead = phead->next;
    }
    printf("can't find the name\n");
    return NULL;
}
void del(struct cnode **phead,struct cnode *node)
{
    struct cnode *pre = NULL;
    struct cnode *p = *phead;
    if(NULL == node)
    {
        printf("the node you want to del NULL !\n");
        return ;
    }
    if(strcmp(p->name,node->name) == 0)
    {
        *phead = (*phead)->next;
        free(node);
        return ;
    }
    else
    {
        pre = p;
        p = p->next;
        while(p != NULL)
        {
            if(strcmp(p->name,node->name) == 0)
            {
                pre->next = p->next;
                free(p);
                p = NULL;
            }
            pre = p;
            p = p->next;
        }
    }
}
void show(struct cnode *phead)
{
    while(phead != NULL)
    {
        printf("client name is:%s  client fd:%d  \n",phead->name,phead->fd);
        phead = phead->next;
    }
}
void destroy(struct cnode **phead)
{
    struct cnode *ptmp  =NULL;
    struct cnode *p = *phead;
    while(p != NULL)
    {
        ptmp = p;
        p = p->next;
        free(ptmp);
    }
    *phead = NULL;
}
