#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

void single(char *buf,int cfd,char *);
void broad(char *buf,int cfd,char *);
void *start(void *arg)
{
    char cast[25];
    int *cfd = arg;
    int n,m;
    char buf[1024+HEADLEN];
    struct head *msg = (struct head *)buf;
    while(1)
    {
        n = recv(*cfd,buf,HEADLEN,MSG_WAITALL);
        if(n <= 0)
        {
            break;
        }
        if(ntohl(msg->type) == T_BCAST)
        {
            strcpy(cast,"broadcast");
        }
        else
        {
            strcpy(cast,"singlecast");
        }
        n = recv(*cfd,buf+HEADLEN,ntohl(msg->msglen),MSG_WAITALL);
        printf("%s use %s to send a message to you :%s\n",msg->sname,cast,buf+HEADLEN);
    }
}
int main(int argc,char *argv[])
{
    int cfd;
    int nfd;
    int len;
    int operation;
    
    char name[20];
    char tmp_buf[1024];
    char local_name[20];
    char buf[1024+HEADLEN];
    struct head *msg = (struct head *)buf; 
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
    memset(saddr.sin_zero,0,0);
    len = sizeof(struct sockaddr_in);
    rt = connect(cfd,(struct sockaddr *)&saddr,len);
    if(-1 == rt)
    {
        close(cfd);
        fprintf(stderr,"");
        return -1;
    }

    printf("Please enter your name:\n");
    scanf("%s",local_name);
    strcpy(msg->sname,local_name);
    strcpy(msg->dname,"");
    msg->type = htonl(T_REGIST);
    msg->msglen = 0;
    send(cfd,buf,HEADLEN,0);

    while(1)
    {
        printf("Please put the operation %d singlecast, %d broadcast\n",T_SCAST,T_BCAST); 
        scanf("%d",&operation);
        fgets(tmp_buf,1024,stdin);
        switch(operation)
        {
            case T_SCAST:
                printf("Enter the name you want to send\n");
                scanf("%s",name);
                strcpy(msg->dname,name);
                strcpy(msg->sname,local_name);
                msg->type = htonl(T_SCAST);
                printf("Enter the message:\n");
                n = read(0,buf+HEADLEN,1024);
                buf[n] = '\0';
                msg->msglen = htonl(n);
                send(cfd,buf,HEADLEN+n+1,0);

                break;
            case T_BCAST:
                strcpy(msg->sname,local_name);
                strcpy(msg->dname,"");
                msg->type = htonl(T_BCAST);
                printf("Enter the message:\n");
                n = read(0,buf+HEADLEN,1024);
                buf[n] = '\0';
                msg->msglen = htonl(n);
                send(cfd,buf,HEADLEN+n+1,0);
                break;
            default:
                break;
        }

    }

    return 0;
}
void single(char *buf,int cfd,char *local_name)
{
}
void broad(char *buf,int cfd,char *local_name)
{
}
