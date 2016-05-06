#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>

int main(int argc,char *argv[])
{
    int sfd;
    int nfd;
    int len;
    char buf[1024];
    int n;
    int i;
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
                    inet_ntop(AF_INET,&caddr.sin_addr,buf,1024);
                    printf("%d %s\n",ntohs(caddr.sin_port),buf);
                    fds[nds].fd = nfd;
                    fds[nds].events = POLLIN;
                    mds++;
                } 
                else
                {
                    n = recv(fds[i].fd,buf,1024,0);
                    if(n==0)
                    {
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
                    printf("%s\n",buf);
                    for(j = 1;j < nds;j++)
                    {
                        if(j != i)
                        {
                            send(fds[j].fd,buf,strlen(buf)+1,0);
                        }
                    }
                }
            }
  //          nds = mds;
        }
        nds = mds;
    }
    close(sfd);
    return 0;
}
