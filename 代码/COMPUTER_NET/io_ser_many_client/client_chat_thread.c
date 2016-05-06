#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
void * rec(void *arg)
{
    int n;
    int *cfd = arg;
    char buf[1024];
    while(1)
    {
     n = recv(*cfd,buf,1024,0);
     if(n == 0)
     {
         close(*cfd);
         return NULL;
     }
     printf("%s\n",buf);
    
    }
}
int main(int argc,char *argv[])
{
    int cfd;
    int nfd;
    int len;
    char buf[1024];
    int n;
    int rt;
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
    pthread_t pt;
    n = pthread_create(&pt,NULL,rec,&cfd);
    while(1)
    {
        scanf("%s",buf);
        send(cfd,buf,strlen(buf)+1,0);
        if(strcmp(buf,"quit") == 0)
        {

            shutdown(cfd,SHUT_RDWR);
            break;
        }
    }
    
    return 0;
}
