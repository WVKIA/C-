#include <stdio.h>
#include <stdlib.h>
#include "head.h"
#include <sys/socket.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>
void send_t(int sfd,char *dname,char *local_name,int n,int m,struct head *msg);
void *start(void *arg)
{
    char cast[20];
    int m,n;
    char buf[1024+HEADLEN];
    struct head *msg = (struct head *)buf;
    int *sfd = arg;
    while(1)
    {
        n = recv(*sfd,buf,HEADLEN,MSG_WAITALL);
        m = ntohl(msg->msglen);
        n = recv(*sfd,buf+HEADLEN,m,MSG_WAITALL);
        if(n =0)
        {
            close(*sfd);
            break;
        }
        if(ntohl(msg->type) == T_SCAST)
        {
            strcpy(cast,"single cast");
        }
        else
        {
            strcpy(cast,"board cast");
        }
        printf("%s use %s send me %s\n",msg->sname,cast,buf+HEADLEN);
    }
}
int main(int argc,char *argv[])
{


    char buf[1024 + HEADLEN];

    char local_name[20];
    char name[20];
    char dname[20];
    int sfd,len;
    int quit= 0;
    int rt,n,m,operation;
    struct head *msg = (struct head *)buf;
    struct sockaddr_in saddr;
    unsigned short port = 3000;
    if(argc >= 2)
    {
        port = (unsigned short)atoi(argv[1]);
    }
    sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd < 0)
    {
        return ;
    }
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = inet_addr(argv[2]);
    memset(saddr.sin_zero,0,0);
    len = sizeof(struct sockaddr_in);

    printf("put you name\n");
    strcpy(local_name,"xiao8");
    printf("%s",local_name);
    strcpy(msg->sname,local_name);
    strcpy(msg->dname,"");
    msg->msglen = 0;
    msg->type = htonl(T_REGIST);
    printf("9");
    rt = connect(sfd,(struct sockaddr*)&saddr,len);
    printf("4");
    send(sfd,buf,HEADLEN,0);
    pthread_t pt;
    printf("1");
    rt = pthread_create(&pt,NULL,start,&sfd);
    
    while(quit == 0)
    {
        printf("enter you operation \n");
        printf("%d is single cast, %d is board cast ,3 is quit\n",T_SCAST,T_BCAST);
        scanf("%d",operation);
        switch(operation)
        {
            case T_SCAST:
                printf("Enter the name you want to send\n");
                scanf("%s",dname);
                printf("enter the message:\n");
                n = read(0,buf+HEADLEN,1024);
                send_t(sfd,dname,local_name,n,htonl(T_SCAST),msg);
                break;
            case T_BCAST:
                strcpy(dname,"");
                printf("enter the message:\n");
                n = read(0,buf+HEADLEN,1024);
                send_t(sfd,dname,local_name,n,htonl(T_BCAST),msg);
                break;
            default:
                quit = 1;
                break;
        }
    }
}
void send_t(int sfd,char *dname,char *local_name,int n,int m,struct head *msg)
{
    strcpy(msg->sname,local_name);
    strcpy(msg->dname,dname);
    msg->msglen = n;
    msg->type = m;
    send(sfd,msg,HEADLEN+n+1,0);
}
