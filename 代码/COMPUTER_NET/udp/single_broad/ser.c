#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
    char buf[1024];
    struct sockaddr_in sin;
    struct sockaddr_in cin;
    unsigned short sport = 0;
    int sfd = 0;
    int nfd = 0;
    int len = 0;
    int n = 0;
    int rt = 0;

    if(argc < 2)
    {
        sport = 2000;
        printf("use default port 2000\n");
    }
    else
    {
        sport = (unsigned short)atoi(argv[1]);
    }
    if(sport <= 0)
    {
        fprintf(stderr,"arg err:%s\n",argv[1]);
        return -1;
    }

    sfd = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == sfd)
    {
        fprintf(stderr,"can't create socket\n");
        return -1;
    }

    sin.sin_family = AF_INET;
    sin.sin_port = htons(sport);
    sin.sin_addr.s_addr = INADDR_ANY;
    memset(sin.sin_zero,0,8);
    len = sizeof(struct sockaddr_in );

    rt = bind(sfd,(struct sockaddr *)&sin,len);
    if(0 != rt)
    {
        fprintf(stderr,"can't bind port %d\n",sport);
        close(sfd);
        return -1;
    }
    while(1)
    {
        n = recvfrom(sfd,buf,1024,0,(struct sockaddr *)&cin,&len);
        if(0 == n)
        {
            break;
        }
        printf("recvform ip %s port %d\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port));
        fflush(stdout);
        write(STDOUT_FILENO,buf,n);
        strcpy(buf,"message arrived\n");
      
        sendto(sfd,buf,strlen(buf)+1,0,(struct sockaddr*)&cin,len);
        printf("%s",buf);
    }
    close(sfd);
    return 0;
}

