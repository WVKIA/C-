#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "msg.h"
#include "chain.h"

int fillfds(struct pollfd *fds,struct allclient *a)
{
    int n = 0;
    struct cnode *p = a->phead;
    while(NULL != p)
    {
        fds[n].fd = p->fd;
        fds[n].events = POLLIN;
        n++;
        p = p->next;
    }
    return n;
}
int notiClient(int fd,int type,int ctype)
{
    struct msgHead head;
    head.type = htonl(type);
    head.ctype = htonl(ctype);
    strcpy(head.sname,"");
    strcpy(head.dname,"");
    head.msgLen = 0;
    send(fd,&head,HEADLEN,0);
    return 0;
}
int notiClientAll(struct allclient *a,int fd)
{
    struct cnode *pclient = a->phead;
    struct msgHead head;
    head.type = htonl(T_USER);
    head.ctype = htonl(C_USERUP);
    strcpy(head.dname,"");
    head.msgLen = 0;
    while(NULL != pclient)
    {
        if(pclient->fd != fd)
        {
            strcpy(head.sname,pclient->cname);
            send(fd,&head,HEADLEN,0);
        }
        pclient=pclient->next;
    }
    return 0;
}

int notiOthers(struct allclient *a,char *name,int ctype)
{
    struct cnode *pclient = a->phead;
    struct msgHead head;
    head.type = htonl(T_USER);
    head.ctype = htonl(ctype);
    strcpy(head.dname,"");
    strcpy(head.sname,name);
    head.msgLen = 0;
    while(NULL != pclient)
    {
        if(strcmp(pclient->cname,name) != 0)
        {
            send(pclient->fd,&head,HEADLEN,0);
        }
        pclient=pclient->next;
    }
    return 0;
}
int notiOthersByfd(struct allclient *a,int fd,int ctype)
{
    struct cnode *p = a->findbyfd(a,fd);
    if(NULL != p)
    {
        notiOthers(a,p->cname,ctype);
    }
    else
    {
        fprintf(stderr,"can not find by fd:%d\n",fd);
    }
    return 0;
}

int proc_regist(char *buf,int fd,struct allclient *a)
{
    struct msgHead *pMsg = (struct msgHead *)buf;
    struct cnode *pclient = NULL;
    pclient = a->findbyname(a,pMsg->sname);
    if(NULL != pclient)
    {
        notiClient(fd,T_REGIST,C_REGERR);
        return 0;
    }
    pclient = a->findbyfd(a,fd);
    if(NULL == pclient)
    {
        fprintf(stderr,"no this fd\n");
        return -1;
    }
    strcpy(pclient->cname,pMsg->sname);
    printf("%s register now\n",pMsg->sname);
    notiClient(fd,T_REGIST,C_REGOK);
    notiClientAll(a,fd);
    notiOthers(a,pMsg->sname,C_USERUP);
    return 0;
}
int proc_bcast(char *buf,int fd,struct allclient *a)
{
    struct msgHead *pMsg = (struct msgHead *)buf;
    struct cnode *p = a->phead;
    unsigned int m;
    int n = 0;
    m = ntohl(pMsg->msgLen);
    if(m > 0)
    {
        n = recv(fd,buf+HEADLEN,m,MSG_WAITALL);
    }
    while(NULL != p)
    {
        if(fd != p->fd)
        {
            send(p->fd,buf,HEADLEN+m,0);
        }
        p = p->next;
    }
    return 0;
}
int proc_scast(char *buf,int fd,struct allclient *a)
{
    struct msgHead *pMsg = (struct msgHead *)buf;
    struct cnode *p = NULL;
    unsigned int m;
    int n;
    m = ntohl(pMsg->msgLen);
    if(m > 0)
    {
        n = recv(fd,buf+HEADLEN,m,MSG_WAITALL);
    }
    p = a->findbyname(a,pMsg->dname);
    if(NULL != p)
    {
        send(p->fd,buf,HEADLEN+m,0);
    }
    return 0;
}

int procMsg(char *buf,int fd,struct allclient *a)
{
    int rt = 0;
    struct msgHead *pMsg = (struct msgHead *)buf;
    unsigned int type = ntohl(pMsg->type);
    switch(type)
    {
        case T_REGIST:
            rt = proc_regist(buf,fd,a);
            break;
        case T_BCAST:
            rt = proc_bcast(buf,fd,a);
            break;
        case T_SCAST:
            rt = proc_scast(buf,fd,a);
            break;
        default:
            rt = -1;
            fprintf(stderr,"you nerver see this\n");
            break;
    }
    return rt;
}

int main(int argc,char *argv[])
{
    int sfd;
    int nfd;
    int len;
    char buf[4096];
    struct msgHead *pMsg = (struct msgHead *)buf;
    int n;
    int rt;
    int i;
    int j;
    struct sockaddr_in saddr;
    struct sockaddr_in caddr;
    struct pollfd  fds[1024];
    int nfds;
    int mfds;
    struct allclient all;
    init_allclient(&all);
    unsigned short sport = 3000;
    if(argc>=2)
    {
        sport = (unsigned short)atoi(argv[1]);
    }
    sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd < 0)
    {
        fprintf(stderr,"can not create socket\n");
        return -1;
    }
    saddr.sin_family = AF_INET;
    saddr.sin_port   = htons(sport);
    saddr.sin_addr.s_addr = INADDR_ANY;
    memset(saddr.sin_zero,0,8);
    len = sizeof(struct sockaddr_in);
    rt = bind(sfd,(struct sockaddr *)&saddr,len);
    if(rt < 0)
    {
        close(sfd);
        fprintf(stderr,"can not bind\n");
        return -1;
    }
    rt = listen(sfd,100);
    if(rt < 0)
    {
        close(sfd);
        fprintf(stderr,"can not listen\n");
        return -1;
    }
    fds[0].fd = sfd;
    fds[0].events = POLLIN;
    nfds = 1;
    while(1)
    {
        nfds=1;
        nfds += fillfds(fds+1,&all);
        printf("wait.....nfds:%d\n",nfds);
        rt = poll(fds,nfds,-1);
        if(rt <= 0)
        {
            fprintf(stderr,"poll err\n");
            continue;
        }
        for(i=0;i<nfds;i++)
        {
            if(POLLIN == fds[i].revents)
            {
                if(0 == i)
                {
                    nfd = accept(sfd,(struct sockaddr *)&caddr,&len);
                   if(-1 == nfd)
                   {
                       fprintf(stderr,"accept fail\n");
                       continue;
                   }
                   inet_ntop(AF_INET,&caddr.sin_addr,buf,1024);
                   printf("1 client connected port:%d ip:%s\n",ntohs(caddr.sin_port),buf);
                   all.add(&all,"",nfd);
                }
                else
                {
                    n = recv(fds[i].fd,buf,HEADLEN,MSG_WAITALL);
                    if(n<=0)
                    {
                        close(fds[i].fd);
                        notiOthersByfd(&all,fds[i].fd,C_USERDOWN);
                        all.del(&all,fds[i].fd);
                        continue;
                    }
                    procMsg(buf,fds[i].fd,&all);
                }
            }
        }
    }
    close(sfd);
    return 0;
}
