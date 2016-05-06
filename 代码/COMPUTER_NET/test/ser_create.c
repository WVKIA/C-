#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
#include <poll.h>
void single(struct head *,struct cnode *);
void board(struct head *,struct cnode *);
struct cnode *regist(struct head *,int );
int main(int argc,char *argv[])
{
    int sfd;
    int nfd;

    struct cnode *phead = NULL;
    struct cnode *node = NULL;
    char buf[1024+HEADLEN];
    struct head *msg = (struct head *)buf;

    struct pollfd fds[100];

    int n;
    int rt;
    int mds;
    int nds;
    int i,j;
    int m;
    int len;

    struct sockaddr_in saddr;
    struct sockaddr_in caddr;
    unsigned short sport = 3000; //duan kou hao wu fu hao duanzhengxing liangge zjie
    if(argc >= 2)
    {
        sport = (unsigned short )atoi(argv[1]);

    }
    sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd < 0)
    {
        fprintf(stderr,"can't socket\n");
        return -1;
    }
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(sport);
    saddr.sin_addr.s_addr = INADDR_ANY;
    memset(saddr.sin_zero,0,8);
    len = sizeof(struct sockaddr_in);
    rt = bind(sfd,(struct sockaddr *)&saddr,len);
    if(rt < 0)
    {
        close(sfd);
        fprintf(stderr,"can't bind\n");
        return -1;
    }

    rt = listen(sfd,100);
    if(rt < 0)
    {
        close(sfd);
        fprintf(stderr,"can't listen\n");
        return -1;
    }
    fds[0].fd = sfd;
    fds[0].events = POLLIN;
    nds = 1;
    while(1)
    {
        n = poll(fds,nds,-1);
        if(n <= 0)
        {
            continue;
        }
        mds = nds;
        for(i = 0;i < nds;i++)
        {
            if(POLLIN == fds[i].revents)
            {
                if(i == 0)
                {
                    nfd = accept(sfd,(struct sockaddr*)&caddr,&len);
                    fds[nds].fd = nfd;
                    fds[nds].events = POLLIN;
                    mds++;
                    n = recv(nfd,msg,HEADLEN,MSG_WAITALL);

                    node = regist(msg,nfd);
                    add(&phead,node);
                    show(phead);
                    printf("pollin has in\n");
                    printf("%s has regist\n",msg->sname);
                }
                else
                {
                    n = recv(fds[i].fd,msg,HEADLEN,MSG_WAITALL);
                    
                    if(n <= 0)
                    {
                       
                        node = find_by_fd(phead,fds[i].fd);
                        del(&phead,node);
                        show(phead);
                        close(fds[i].fd);
                        for(j = i;j < nds-1;j++)
                        {
                            fds[j]= fds[j+1];
                        }
                        nds--;
                        mds--;
                        i--;
                        continue;
                    }
                    printf("%s send %s a message dododo!!!\n",msg->sname,msg->dname);
                        n = recv(fds[i].fd,buf+HEADLEN,ntohl(msg->msglen),MSG_WAITALL);
                        printf("%s send %s message %s\n",msg->sname,msg->dname,buf+HEADLEN);
                    if(ntohl(msg->type) == T_SCAST)
                    {
                        printf("this is check single cast\n");
                        single(msg,phead);
                    }
                    else if(ntohl(msg->type) == T_BCAST)
                    {
                        printf("this is check boradcst\n");
                        board(msg,phead);
                    }
                }
            }
        }
        nds = mds;
    }
    close(sfd);
    return 0;
}

struct cnode *regist(struct head *msg,int nfd)
{
    printf("%s is up\n ",msg->sname);
    struct cnode *p = malloc(sizeof(struct cnode));
    strcpy(p->name,msg->sname);
    p->fd = nfd;
    p->next = NULL;
    printf("%s has regist!\n",msg->sname);
    return p;
}
void single(struct head *msg,struct cnode *phead)
{
    int m = ntohl(msg->msglen);
    struct cnode *ptmp = find_by_name(phead,msg->dname);
    int n = ptmp->fd;
    send(n,msg,HEADLEN+m,0);
}
void board(struct head *msg,struct cnode *phead)
{
    struct cnode *p = phead;
    int m = ntohl(msg->msglen);
    struct cnode *ptmp = find_by_name(phead,msg->sname);
    int n = ptmp->fd;
    while(p != NULL)
    {
        if(p->fd != n)
        {
            send(p->fd,msg,HEADLEN+m,0);
        }
        p = p->next;
    }
}
