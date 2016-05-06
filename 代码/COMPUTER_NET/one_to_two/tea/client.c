#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main(int argc ,char *argv[])
{
    int n;
    int rt;
    int len;
    int cfd;
    int nfd;
    char buf[1024];
    struct sockaddr_in saddr;
    struct sockaddr_in caddr;
    unsigned short sport= 3000;
    if(argc>=2)
    {
        sport=(unsigned short)atoi(argv[1]);
    }
    cfd=socket(AF_INET,SOCK_STREAM,0);
    if(cfd<0)
    {
        fprintf(stderr,"faile\n");
        return -1;
    }
    saddr.sin_family=AF_INET;
    saddr.sin_port= htons(sport);
    saddr.sin_addr.s_addr=inet_addr(argv[2]);
    memset(saddr.sin_zero,0,8);
    len=sizeof(struct sockaddr_in);
    rt=connect(cfd,(struct sockaddr *)&saddr,len);
    if(-1==rt)
    {
        close(cfd);
        fprintf(stderr,"can not connect\n");
        return -1;
    }
    while(1)
    {
        scanf("%s",buf);
        send(cfd,buf,strlen(buf)+1,0);
        if(strcmp(buf,"quit")==0)
        {
            close(cfd);
            break;
        }
    }
    return 0;
}
