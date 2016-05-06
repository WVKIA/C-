#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>

int main(int argc ,char *argv[])
{
    int n;
    int i;
    int j;
    int rt;
    int len;
    int sfd;
    int nfd;
    char buf[1024];
    struct sockaddr_in saddr;
    struct sockaddr_in caddr;
    struct pollfd fds[1024];
    int nfds;
    int mfds;
    unsigned short sport= 3000;
    if(argc>=2)
    {
        sport=(unsigned short)atoi(argv[1]);
    }
    sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd<0)
    {
        fprintf(stderr,"faile\n");
        return -1;
    }
    saddr.sin_family=AF_INET;
    saddr.sin_port= htons(sport);
    saddr.sin_addr.s_addr=INADDR_ANY;
    memset(saddr.sin_zero,0,8);

    len=sizeof(struct sockaddr_in);
    rt=bind(sfd,(struct sockaddr *)&saddr,len);
    if(rt<0)
    {
        close(sfd);
        fprintf(stderr,"not bind\n");
        return -1;
    }
    rt=listen(sfd,100);
    if(rt<0)
    {
        close(sfd);
        fprintf(stderr,"not listen\n");
        return -1;
    }
    fds[0].fd=sfd;
    fds[0].events=POLLIN;
    nfds=1;
    while(1)
    {
        printf("wait.....nfds:%d\n",nfds);
        rt=poll(fds,nfds,-1);
        if(rt<=0)
        {
            fprintf(stderr,"poll failed\n");
            continue;
        }
        mfds=nfds;
        for(i=0;i<nfds;i++)
        {
            if(POLLIN==fds[i].revents)
            {
                if(0==i)
                {
                    nfd=accept(sfd,(struct sockaddr *)&caddr,&len);
                    if(-1==nfd)
                    {
                        fprintf(stderr,"accept fail\n");
                        continue;
                    }
                    inet_ntop(AF_INET,&caddr.sin_addr,buf,1024);
                    printf("one accept port:%d,ip:%s\n",ntohs(caddr.sin_port),buf);
                    fds[nfds].fd=nfd;
                    fds[nfds].events=POLLIN;
                    mfds++;            
                }
                else
                {
                    n=recv(fds[i].fd,buf,1024,0);
                    if(0==n)
                    {
                        close(fds[i].fd);
                        for(j=i;j<nfds-1;j++)
                        {
                            fds[j]=fds[j+1];
                        }
                        mfds--;
                        nfds--;
                        i--;
                    }
                    /*for(k=1;k<nfds-1;k++)
                    {

                    }
                    //*/printf("recv:%s\n",buf);

                }   
            }
        }
        nfds=mfds;
    }
    close(sfd);
    return 0;
}
