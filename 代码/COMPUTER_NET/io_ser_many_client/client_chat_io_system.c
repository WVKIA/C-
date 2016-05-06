#include <stdio.h>
#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char *argv[])
{
    int cfd;
    int nfd;
    int len;
    char buf[1024];
    int n;
    int rt;
    int i;
    int quit = 0;

    struct pollfd fd[2];
    struct sockaddr_in saddr;
    unsigned short sport = 3000; //duan kou hao wu fu hao duanzhengxing liangge zjie
    if(argc >= 2)
    {
        sport = (unsigned short )atoi(argv[1]);

    }
    cfd = socket(AF_INET,SOCK_STREAM,0);
    if(cfd < 0)
    {
        fprintf(stderr,"can't socket\n");
        return -1;
    }
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(sport);
    saddr.sin_addr.s_addr = inet_addr(argv[2]);
    memset(saddr.sin_zero,0,0);
    len = sizeof(struct sockaddr_in);
    rt = connect(cfd,(struct sockaddr *)&saddr,len);
    if(-1 == rt)
    {
        close(cfd);
        fprintf(stderr,"");
        return -1;
    }
    fd[0].fd = 0;
    fd[0].events = POLLIN;
    fd[1].fd = cfd;
    fd[1].events = POLLIN;

    while(0 == quit)
    {
        rt = poll(fd,2,-1);
        if(rt < 0)
        {
            continue;
        }
        for(i = 0;i < 2;i++)
        {
            if(POLLIN == fd[i].revents)
            {
                if(i == 0)
                
                {   scanf("%s",buf);
                
                    if(strcmp(buf,"quit") == 0)
                    {
                        quit = 1;
                        break;
                    }
                    send(cfd,buf,strlen(buf)+1,0);
                }
                else
                {
                    n = recv(fd[i].fd,buf,1024,0);
                    if(n == 0)
                    {
                        quit = 1;
                        break;
                    }
                    printf("recv:%s\n",buf);
                    fflush(stdout);
                }
            }
        }
    }
    close(cfd); 
    return 0;
}
