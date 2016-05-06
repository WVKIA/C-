#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <stdlib.h>
#include "msg.h"
#include "admin.h"


int main(int argc,char*argv[])
{
    char buf[1076];
    char sname[20];
    char dname[20];
    int n;
    int rt;
    int sfd;
    int nfd;
    int len;
    int nfds;
    int mfds;
    int i;
    int j;
    int k;
    int m;
    struct msgHead *mhead=(struct msgHead *)buf;
    struct admin *adm=NULL;
    struct alladmin admin;
    init_alladmin(&admin);
    struct sockaddr_in saddr;

    struct sockaddr_in caddr;
    struct pollfd fds[1024];
    unsigned short sport=3000;
    if(argc>1)
    {
        sport=(unsigned short)atoi(argv[1]);
    }
    sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd<0)
    {
        fprintf(stderr,"socket fail");
        return -1;
    }
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(sport);
    saddr.sin_addr.s_addr = INADDR_ANY;
    memset(saddr.sin_zero,0,0);
    len=sizeof(struct sockaddr_in);
    rt=bind(sfd,(struct sockaddr *)&saddr,len);
    if(rt<0)
    {
        close(sfd);
        fprintf(stderr,"bind fail");
        return -1;
    }
    rt=listen(sfd,100);
    if(rt<0)
    {
        close(sfd);
        fprintf(stderr,"listen fail");
        return -1;
    }
    fds[0].fd=sfd;
    fds[0].events=POLLIN;
    nfds=1;
    while(1)
    {
        printf("wait for connect %d\n",nfds);
        rt=poll(fds,nfds,-1);
        if(rt<=0)
        {
            fprintf(stderr,"poll fail");
            continue;
        }
        mfds=nfds;
        for(i=0;i<nfds;i++)
        {
            if(fds[i].revents==POLLIN)
            {
                if(0==i)
                {
                    nfd=accept(sfd,(struct sockaddr *)&caddr,&len);

                    if(-1==nfd)
                    {
                          fprintf(stderr,"acept fail");
                           continue;
                    }
                    n=recv(nfd,mhead,HEADLEN,MSG_WAITALL);
                    adm=malloc(sizeof(struct admin));
                    strcpy(adm->cname,mhead->sname);
                    adm->fd=nfd;
                    adm->next=NULL;

                    addadmin(&admin,adm);
                    showadmin(&admin);
                    inet_ntop(AF_INET,&caddr.sin_addr,buf,1024);
                    printf("one client connected port:%d ip:%s\n",ntohs(caddr.sin_port),buf);
                
                    fds[nfds].fd=nfd;
                    fds[nfds].events=POLLIN;
                    mfds++;
                }
                else
                {
                    n=recv(fds[i].fd,mhead,HEADLEN,MSG_WAITALL);
                    if(n<=0)
                    {
                        adm=findbyfds(&admin,fds[i].fd);
                        deladmin(&admin,adm);
                        showadmin(&admin);
                        close(fds[i].fd);
                        for(j=i;j<nfds-1;j++)
                        {
                            fds[j]=fds[j+1];
                        }
                        nfds--;
                        mfds--;
                        i--;
                        continue;
                    }
                    m=ntohl(mhead->msglen);
                    printf("sever:m:%d,name:%s\n",m,mhead->sname);
                    n = 0;
                    if(m>0)
                    {
                        n=recv(fds[i].fd,buf+HEADLEN,m,MSG_WAITALL);
                    }

                    if(T_BCAST==ntohl(mhead->type))
                    {
                        for(k=1;k<nfds;k++)
                        {
                            if(k!=i)
                            {
                                send(fds[k].fd,buf,HEADLEN+n,0);
                            }
                        }
                    }
                    else
                    {
                        printf("dname:%s\n",mhead->dname);
                        adm=findbyname(&admin,mhead->dname);
                        if(NULL==adm)
                        {
                            printf("no this name:%s\n",mhead->dname);
                            continue;
                        }
                        send(adm->fd,buf,HEADLEN+n,0);
                    }



                }
            }
        }
        nfds=mfds;

    }
    close(sfd);
    return 0;
}

