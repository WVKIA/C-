#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <poll.h>
#include "head.h"
#include <arpa/inet.h>
struct cnode* regist(int n,char *name);
void singlecast(struct head *msg,struct cnode *phead);
void boardcast(struct head *msg,struct cnode *phead);
int main(int argc,char *argv[])
{
    int afd;
    int bfd;
    
    unsigned short port = 3000;
    if(argc >= 2)
    {
        port = (unsigned short) atoi(argv[1]);
    }
    char buf[HEADLEN + 1024];
    struct head *msg = (struct head *)buf;
    struct sockaddr_in saddr;
    struct sockaddr_in caddr;
    struct pollfd fds[100];

    struct cnode *phead = NULL;
    struct cnode *node = NULL;

    int n,m,i,j;
    int mds,nds;
    int rt;
    int len;

    saddr.sin_family = AF_INET;
    saddr.sin_port = htonl(port);
    saddr.sin_addr.s_addr = INADDR_ANY;
    memset(saddr.sin_zero,0,0);
    len = sizeof(struct sockaddr_in);

    afd = socket(AF_INET,SOCK_STREAM,0);
    if(afd < 0)
    {
        fprintf(stderr,"can't socket!\n");
        return ;
    }

    rt = bind(afd,(struct sockaddr *)&saddr,len);
    if(rt < 0)
    {
        close(afd);
        return ;
    }

    rt = listen(afd,100);
    if(rt< 0)
    {
        close(afd);
    }

    fds[0].fd = afd;
    fds[0].events=  POLLIN;
    nds = 1;
    printf("this is while befront\n");
    while(1)
    {
        n = poll(fds,nds,-1);
        if(n < 0)
        {
            continue;
        }
        printf("this is poll after\n");
        mds = nds;
        for(i = 0;i < nds; i++)
        {
            if(fds[i].revents == POLLIN)
            {
               
                if(i == 0)
                {

                    n = accept(afd,(struct sockaddr*)&caddr,&len);
                    if(n < 0)
                    {
                        continue;
                    }
                    fds[nds].fd = n;
                    fds[nds].events = POLLIN;
                    mds++;

                    n = recv(fds[i].fd,buf,HEADLEN,MSG_WAITALL);
                    node = regist(n,msg->sname);
                    add(&phead,node);
                    show(phead);
                }
                else
                {
                    n = recv(fds[i].fd,buf,HEADLEN,MSG_WAITALL);
                    if(n == 0)
                    {
                        node = find_by_fd(phead,fds[i].fd);
                        del(&phead,node);
                        close(fds[i].fd);
                        for(j = i;j <nds-1;j++)
                        {
                            fds[j] = fds[j+1];
                        }
                        mds--;
                        i--;
                        nds--;
                        continue;
                    }

                    m = ntohl(msg->msglen);
                    n = recv(fds[i].fd,buf,m,MSG_WAITALL);
                    if(T_SCAST == ntohl(msg->type))
                    {
                        singlecast(msg,phead);
                    }
                    else if(T_BCAST == ntohl(msg->type))
                    {
                        boardcast(msg,phead);
                    }
                }
            }
        
        }
        nds = mds;
    }
}
struct cnode* regist(int n,char *name)
{
    struct cnode *p = malloc(sizeof(struct cnode));
    p->fd = n;
    strcpy(p->name,name);
    p->next = NULL;
    printf("%s has regist!!!\n",name);
    return p;
}
void singlecast(struct head *msg,struct cnode *phead)
{
    struct cnode *p = phead;
    struct cnode *ptmp = find_by_name(p,msg->dname);

    int n = ptmp->fd;
    int m = ntohl(msg->msglen);
    send(n,msg,HEADLEN+m,0);  
}
void boardcast(struct head *msg,struct cnode *phead)
{
    struct cnode *p = phead;
    struct cnode *ptmp = find_by_name(p,msg->sname);
    int n = ptmp->fd;
    int m = ntohl(msg->msglen);
    int d;
    while(p != NULL)
    {
        d = p->fd;
        if(d != n)
        {
            send(d,msg,HEADLEN+m,0);
        }
        p = p->next;
    }
}
