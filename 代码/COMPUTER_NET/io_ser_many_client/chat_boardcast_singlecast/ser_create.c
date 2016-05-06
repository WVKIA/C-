#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include "head.h"
struct cnode * regist(int nfd)
{
    struct cnode *node = malloc(sizeof(struct cnode));

    int n;
    int fd = nfd;
    char buf[HEADLEN];
    struct head * msg = (struct head *)buf;
    n = recv(fd,buf,HEADLEN,MSG_WAITALL);
    strcpy(node->name,msg->sname);
    node->fd = fd;
    printf("The %s has regist!\n",node->name);
    return node;
}
void singlecast(struct head *msg,struct cnode *phead,int n)
{
    char name[20];
    strcpy(name,msg->dname);
    struct cnode *ptmp = NULL;
    ptmp = find_by_name(phead,name);
    if(NULL == ptmp)
    {
        return ;
    }
    int fd = ptmp->fd;
    send(fd,msg,n+HEADLEN,0);
}
void boardcast(struct head *msg,struct cnode *phead,int n)
{
    struct cnode *p = find_by_name(phead,msg->sname);
    int fd_send = p->fd;
    int fd_recv;
    while(phead != NULL)
    {
        fd_recv = phead->fd;
        if(fd_recv != fd_send)
        {
            send(fd_recv,msg,n+HEADLEN,0);
        }
        phead = phead->next;
    }
}

int main(int argc,char *argv[])
{

    struct cnode *phead = NULL;
    struct cnode *node = NULL;
    int sfd;
    int nfd;
    int len;
    char buf[1024+HEADLEN];
    struct head *msg =(struct head *)buf;
    int n;

    int m;
    int i;
    int k;
    int j;
    int rt;

    int nds;
    int mds;

    struct sockaddr_in saddr;
    struct sockaddr_in caddr;
    struct pollfd fds[1024];
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
    memset(saddr.sin_zero,0,0);
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
    fds[0].events =POLLIN;
    nds = 1;
    while(1)
    {
        printf("wait %d\n",nds);
        n = poll(fds,nds,-1);
        printf("this is poll after\n");
        if(n < 0)
        {

            fprintf(stderr,"can't poll\n");
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
                    if(nfd < 0)
                    {
                        fprintf(stderr,"can't accept\n");
                        continue;
                    }
                    fds[nds].fd = nfd;
                    fds[nds].events = POLLIN;
                    mds++;
                    node = regist(nfd);
                    add(&phead,node);
                    show(phead);
                    printf("add\n");
                } 
                else
                {
                    n = recv(fds[i].fd,buf,HEADLEN,MSG_WAITALL);
                    
                        if(n==0)
                        {

                            node = find_by_fd(phead,fds[i].fd);
   
                            del(&phead,node);
                            show(phead);
                            printf("del\n");
                            close(fds[i].fd); 
                            for(j = i;j < nds-1;j++)
                            {
                                fds[j] = fds[j+1];
                            }
                            i--;
                            nds--;
                            mds--;
                            continue;
                        }
                     m = ntohl(msg->type);
                     n = recv(fds[i].fd,buf+HEADLEN,ntohl(msg->msglen),MSG_WAITALL);
                    if(m == T_SCAST)
                    {
                        singlecast(msg,phead,n);
                    }
                    else if(m == T_BCAST)
                    {
                        boardcast(msg,phead,n);   
                    }
                }
            }
        }
        nds = mds;
    }
    close(sfd);
    return 0;
}
