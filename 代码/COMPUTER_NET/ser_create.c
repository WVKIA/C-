#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
    int sfd;
    int nfd;
    int len;
    char buf[1024];
    int n;
    int rt;
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

    while(1)
    {
        nfd = accept(sfd,(struct sockaddr*)&caddr,&len);
        printf("client connect\n");
        if(-1==nfd)
        {
            fprintf(stderr,"accept fail]n");
            continue;
        }
        while(1)
        {

            n = recv(nfd,buf,1024,0);
            if(n == 0)
            {
                close(nfd);
                break;
            }
            printf("recv  %s\n",buf);
        }
    }
    close(sfd);
    return 0;
}
