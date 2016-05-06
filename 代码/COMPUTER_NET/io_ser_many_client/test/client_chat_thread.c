#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
void * rec(void *arg)
{
    char cast[100];
    int n;
    int m;
    int *cfd = arg;
    char buf[1024+HEADLEN];
    struct head *msg =(struct head*) buf;
    while(1)
    {
        n = recv(*cfd,buf,HEADLEN,MSG_WAITALL);
        if(n <= 0)
        {
            break;
        }
        m = ntohl(msg->msglen);
        n = recv(*cfd,buf+HEADLEN,m,MSG_WAITALL);
        if(ntohl(msg->type) == T_BCAST)
        {
            strcpy(cast,"board cast\n");
        }
        else
        {
            strcpy(cast,"single cast\n");
        }
        printf("%s use %s send me a message:%s",msg->sname,cast,buf+HEADLEN);

    }
    close(*cfd);
}
int main(int argc,char *argv[])
{
    int cfd;
    int nfd;
    int len;
    char sname[20];
    char dname[20];
    char tmp_buf[100];
    char buf[1024+HEADLEN];
    struct head *msg =(struct head *) buf;

    int n;
    int quit = 0;
    int operation;
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



    printf("Enter your name:\n");
    scanf("%s",sname);
    strcpy(msg->sname,sname);
    strcpy(msg->dname,"");
    msg->type = 3;
    msg->msglen = 0;
    send(cfd,buf,HEADLEN,0);


    pthread_t pt;
    n = pthread_create(&pt,NULL,rec,&cfd);
    while(quit == 0)
    {
        printf("enter the operation 1 single 0 broeadcast 3 quit\n");
        scanf("%d",&operation);
        fgets(tmp_buf,1024,stdin);
        switch (operation)
        {
            case T_BCAST:
                printf("enter the name you send:\n");
                scanf("%s",dname);
                printf("enter the message you send:\n");
                n = read(cfd,buf+HEADLEN,1024);
                buf[HEADLEN+n] = '\0';
                strcpy(msg->sname,sname);
                strcpy(msg->dname,dname);
                msg->type = htonl(T_BCAST);
                msg->msglen = htonl(n+1);
                send(cfd,buf,HEADLEN+n+1,0);
                break;
            case T_SCAST:
                printf("enter the message you boardcast:\n");
                n = read(cfd,buf+HEADLEN,1024);
                buf[HEADLEN+n] = '\0';
                strcpy(msg->sname,sname);
                strcpy(msg->dname,"");
                msg->type = htonl(T_SCAST);
                msg->msglen = htonl(n+1);
                send(cfd,buf,HEADLEN+n+1,0);
                break;
            default:
                quit = 1;
                break;
        }
    }
    
    return 0;
}
