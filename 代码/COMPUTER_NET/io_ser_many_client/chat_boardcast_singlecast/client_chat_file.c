#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"


void * rec(void *arg)
{
    int n;
    char *p = NULL;
    int *cfd = arg;
    char buf[1024+HEADLEN];
    struct head *msg = (struct head *)buf;
    int m;
    while(1)
    {
        n = recv(*cfd,buf,HEADLEN,MSG_WAITALL);
        if(0 >= n)
        {
            break;
        }
        m = ntohl(msg->msglen);
        n = recv(*cfd,buf+HEADLEN,m,MSG_WAITALL);
        if(n == 0)
        {
            close(*cfd);
            return NULL;
        }

        char cast[1024];
        if(ntohl(msg->type) == 1)
        {
            strcpy(cast,"single cast");
        }
        else
        {
            strcpy(cast,"board cast");
        }
        printf("%s use the %s send me a msg:%s\n",msg->sname,cast,buf+HEADLEN);

    }
}

int main(int argc,char *argv[])
{

    int cfd;
    int nfd;
    int len;
    char tmp_buf[1024];
    int operation;
    int quit = 0;
    char local_name[20]; 
    char name[20];
    char buf[1024+HEADLEN];
    struct head *msg = buf;

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

    printf("input your name:\n");
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

    pthread_t pt;
    n = pthread_create(&pt,NULL,rec,&cfd);

    while(quit == 0)
    {
        printf("enter the operation 1 single cast 0 boardcast 3 quit\n");
        scanf("%d",&operation);
        fgets(tmp_buf,1024,stdin);
        switch (operation)
        {
            case T_SCAST:
                strcpy(msg->sname,local_name);
                printf("Enter the name you want to send message:");
                scanf("%s",name);
                printf("Enter the messeage:");
                n = read(0,buf+HEADLEN,1024);
                buf[n+HEADLEN] = '\0';
                strcpy(msg->dname,name);
                msg->type =htonl( T_SCAST);
                msg->msglen= htonl( n+1);
                send(cfd,buf,HEADLEN + n + 1,0);
                break;
            case T_BCAST:
                strcpy(msg->sname,local_name);
                strcpy(msg->dname,"");
                msg->type =htonl( T_BCAST);
                printf("Enter the messeage you want to boardcast:\n");
                n = read(0,buf+HEADLEN,1024);
                buf[n + HEADLEN]='\0';
                msg->msglen = htonl(n+1);
                send(cfd,buf,HEADLEN + n + 1,0);
                break;
            default:
                quit = 1;
                break;
        }       
    }
    return 0;
}

