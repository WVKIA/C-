#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
//#include <pthread.h>
#include <poll.h>


int main(int argc,char*argv[])
{
    char buf[1024];
    int i;
    int n;
    int rt;
    int st;
    int cfd;
    int quit=0;
    int nfd;
    int len;
    struct pollfd fds[2];
    struct sockaddr_in saddr;
    //struct sockaddr_in caddr;
    unsigned short sport=3000;
    if(argc>2)
    {
        sport=(unsigned short)atoi(argv[1]);
    }
    cfd=socket(AF_INET,SOCK_STREAM,0);
    if(cfd<0)
    {
        fprintf(stderr,"socket fail");
        return -1;
    }
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(sport);
    saddr.sin_addr.s_addr = inet_addr(argv[2]);
    memset(saddr.sin_zero,0,0);
    len=sizeof(struct sockaddr_in);
    rt=connect(cfd,(struct sockaddr *)&saddr,len);
    if(-1==rt)
    {
        close(cfd);
        fprintf(stderr,"connect fail");
        return -1;
    }
    fds[0].fd=0;
    fds[0].events=POLLIN;
    fds[1].fd=cfd;
    fds[1].events=POLLIN;
    while(0==quit)
    {
        rt=poll(fds,2,-1);
        if(rt<=0)
        {
            fprintf(stderr,"poll fail");
            continue;
        }
        for(i=0;i<2;i++)
        {
            if(POLLIN==fds[i].revents)
            {
                if(0==i)
                {
                    scanf("%s",buf);
                    send(cfd,buf,strlen(buf)+1,0);
                    if(strcmp(buf,"quit")==0)
                    {
                        quit=1;
                        break;
                    }
                }
                else
                {
                    n=recv(fds[i].fd,buf,1024,0);
                    if(0==n)
                    {
                        quit=1;
                        break;
                    }
                    printf("recv:%s \n",buf);
                    fflush(stdout);
                
                }
            }
        }
    }
    close(cfd);
    return 0;
}

