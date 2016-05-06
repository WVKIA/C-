#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
void * start(void *arg)
{
    int n;
    char buf[1024];
    int len  = sizeof(struct sockaddr_in);
    struct sockaddr_in cin;
    int *cfd = arg;
    while(1)
    {
        n = recvfrom(*cfd,buf,1024,0,(struct sockaddr *)&cin,&len);
        if(0 == n)
        {
            break ;
        }
        fflush(stdout);
        write(STDOUT_FILENO,buf,n);
    }
}
int main(int argc,char *argv[])
{
    char buf[1024];
    struct sockaddr_in cin;
    unsigned short sport = 0;
    int cfd = 0;
    int len= 0;
    int n= 0;
    int rt = 0;

    if(argc < 3)

    {
        printf("usage:./client ip port\n");
        return -1;
    }
    sport = (unsigned short)atoi(argv[2]);
    if(sport == 0)
    {
        fprintf(stderr,"can't cover %s\n",argv[2]);
        return -1;
    }

    cfd = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == cfd)
    {
        fprintf(stderr,"can't create socket\n");
        return -1;
    }
    len = sizeof(struct sockaddr_in);

    cin.sin_family = AF_INET;
    cin.sin_port   = htons(sport);
    cin.sin_addr.s_addr = inet_addr(argv[1]);
    memset(cin.sin_zero,0,8);
    pthread_t pt;
    rt = pthread_create(&pt,NULL,start,&cfd);
    while(1)
    {
        n = read(STDIN_FILENO,buf,1023);
        if(0 == n)
        {
            break;
        }
        rt = sendto(cfd,buf,n,0,(struct sockaddr *)&cin,len);
        if(rt != n)
        {
            fprintf(stderr,"rt %d errno %d \n",rt,errno);
        }
    }
    close(cfd);
    return 0;
}
