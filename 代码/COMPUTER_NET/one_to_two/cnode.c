#include <stdio.h>
#include "head.h"
#include <string.h>
#include <stdlib.h>
void add(struct cnode **phead,int nfd)
{
    struct cnode *node = malloc(sizeof(struct cnode));
    node->fd = nfd;
    strcpy(node->name,"");
    node->next = NULL;

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
struct cnode *find_by_fd(struct cnode *p,int fd)
{
    struct cnode *phead = p;
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
struct cnode * find_by_name(struct cnode *p,char *name)
{
    struct cnode *phead = p;
    while(phead != NULL)
    {
        if(strcmp(name,phead->name) == 0)
        {
            return phead;
        }
        phead = phead->next;
    }
    printf("%s can't find the name\n",name);
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
    if(*phead == node)
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
            if(p == node)
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
void show(struct cnode *p)
{
    struct cnode *phead = p;
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
