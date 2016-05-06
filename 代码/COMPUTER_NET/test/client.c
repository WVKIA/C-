#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include "head.h"
void *start(void *arg)
{
    printf("why do this\n");
    char cast[20];
    char buf[1024+HEADLEN];
    struct head *msg = (struct head *)buf;
    int *fd = arg;
    int n;
    while(1)
    {
        n = recv(*fd,buf,HEADLEN,MSG_WAITALL);
        if(n <= 0)
        {
            break;
        }

        n = recv(*fd,buf+HEADLEN,ntohl(msg->msglen),MSG_WAITALL);
        if(ntohl(msg->type) == T_SCAST)
        {
            strcpy(cast,"single cast");
        }
        else
        {
            strcpy(cast,"board cast");
        }
        printf("%s use %s to send me %s\n",msg->sname,cast,msg+HEADLEN);
    }
}
int main(int argc,char *argv[])
{
    int cfd;
    int nfd;
    int len;
    char dname[20];
    char local_name[20];
    char buf_tmp[100];
    char buf[1024+HEADLEN];
    struct head *msg = (struct head*)buf;
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
    saddr.sin_addr.s_addr = INADDR_ANY;
    memset(saddr.sin_zero,0,8);
    len = sizeof(struct sockaddr_in);
    printf("put your name:\n");
    scanf("%s",local_name);
    strcpy(msg->sname,local_name);
    strcpy(msg->dname,"");
    msg->type = htonl(T_REGIST);
    msg->msglen = 0;
    rt = connect(cfd,(struct sockaddr *)&saddr,len);
    if(-1 == rt)
    {
        close(cfd);
        fprintf(stderr,"");
        return -1;
    }
  
    send(cfd,buf,HEADLEN,0);
    printf("%s %d %s\n",msg->sname,msg->type,msg->dname);

    pthread_t pt;
    rt = pthread_create(&pt,NULL,start,&cfd);
    while(1)
    {
        printf("choose your operation %d single cast %d board cast 3 quit\n",T_SCAST,T_BCAST);
        scanf("%d",&rt);
        fgets(buf_tmp,100,stdin);
        if(rt == T_SCAST)
        {
            printf("please enter the name you send:\n");
            scanf("%s",dname);
            strcpy(msg->dname,dname);
            strcpy(msg->sname,local_name);
            printf("Please put the message:\n");
            n = read(0,buf+HEADLEN,1023);
            buf[n] = '\0';
            msg->type = htonl(T_SCAST);
            send(cfd,buf,HEADLEN+n+1,0);
        }
        else if(rt == T_BCAST)
        {
            printf("enter masseage:\n");
            strcpy(msg->dname,"");
            strcpy(msg->sname,local_name);
            n = read(0,buf+HEADLEN,1023);
            buf[n]= '\0';
            msg->type = htonl(T_BCAST);
            send(cfd,buf,HEADLEN+n+1,0);
        }
        else
        {
            break;;
        }
    }
    close(cfd);
    return 0;
}
