#ifndef __CHAIN_H__
#define __CHAIN_H__

struct cnode
{
    char cname[20];
    int fd;
    struct cnode *next;
};

struct allclient
{
    struct cnode *phead;
    unsigned int num;
    int (*add)(struct allclient *a,char *name,int fd);
    int (*del)(struct allclient *a,int fd);
    struct cnode *(*findbyname)(struct allclient *a,char *name);
    struct cnode *(*findbyfd)(struct allclient *a,int fd);
};

extern int init_allclient(struct allclient *a);

#endif
