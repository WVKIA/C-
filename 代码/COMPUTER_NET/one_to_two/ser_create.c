#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include "head.h"

void regist(char *,struct cnode **,int);
void single(char *,struct cnode *);
void broad(char *,struct cnode *);

int main(int argc,char *argv[])
{
    int sfd;
    int nfd;
    int len;
    char buf[1024+HEADLEN];
    struct head *msg = (struct head *)buf;
    char tmp_buf[1024];
    struct pollfd fds[100];
    int n;
    int rt;

    int nds;
    int mds;
    int i;
    int j;

    struct cnode *phead = NULL;
    struct cnode *node = NULL;

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
        mds = nds;
        for(i = 0;i < nds;i++)
        {
            if(fds[i].revents == POLLIN)
            {
                if(i == 0)
                {
                    nfd = accept(sfd,(struct sockaddr*)&caddr,&len);
                    if(-1==nfd)
                    {
                        fprintf(stderr,"accept fail]n");
                        continue;
                    }
                    inet_ntop(AF_INET,&caddr.sin_addr,buf,1024);
                    printf("one client connected port :%d ip:%s\n",ntohs(caddr.sin_port),buf);
                    fds[nds].fd = nfd;
                    fds[nds].events = POLLIN;
                    mds++;
                    add(&phead,nfd);
                }
                else
                {
                    n = recv(fds[i].fd,buf,HEADLEN,MSG_WAITALL);
                    if(n == 0)
                    {
                        for(j = i;j < nds-1;j++)
                        {
                            fds[j] = fds[j+1];
                        }
                        close(fds[i].fd);
                        mds--;
                        nds--;
                        i--;
                        node = find_by_fd(phead,fds[i].fd);
                        del(&phead,node);
                       
                    }
                    if(msg->type == ntohl(T_REGIST))
                    {
                        regist(buf,&phead,fds[i].fd);
                        show(phead);
                    }
                    else if(msg->type == ntohl(T_SCAST))
                    {
                        n = recv(fds[i].fd,buf+HEADLEN,ntohl(msg->msglen),MSG_WAITALL);
                        printf("this is single cast\n");
                        single(buf,phead);
                    }
                    else if(msg->type == ntohl(T_BCAST))
                    {
                        n = recv(fds[i].fd,buf+HEADLEN,ntohl(msg->msglen),MSG_WAITALL);
                        printf("this is broadcast\n");
                        broad(buf,phead);
                    }
                    
                }
            }
        }
        nds = mds;
    }
    close(sfd);
    return 0;
}
void regist(char *buf,struct cnode **phead,int fd)
{
    struct head *msg = (struct head *)buf;
    struct cnode *p =  *phead;
    struct cnode *ptmp = find_by_fd(p,fd);
    strcpy(ptmp->name,msg->sname);
    printf("the name is %s has regist\n",msg->sname);
}
void single(char *buf,struct cnode *phead)
{
    struct head *msg = (struct head *)buf;
    int m = ntohl(msg->msglen);
    printf("single name is %s\n",msg->dname);
    struct cnode *p = find_by_name(phead,msg->dname);
    printf("msg->dname:%s\n",msg->dname);
    send(p->fd,buf,HEADLEN+m,0);
}
void broad(char *buf,struct cnode *phead)
{
    struct head *msg = (struct head*)buf;
    int m = ntohl(msg->msglen);
    struct cnode *p = find_by_name(phead,msg->sname);
    struct cnode *ptmp = phead;
    while(ptmp != NULL)
    {
        if(ptmp->fd != p->fd)
        {
            send(ptmp->fd,buf,HEADLEN+m,0);
        }
        ptmp = ptmp->next;
    }
}
