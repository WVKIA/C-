#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include "msg.h"
enum
{
    C_BCAST,
    C_SCAST,
    F_GROUP,
    F_SINGL,
    T_QUIT,
    NONE
    
};
char *cmdstring[]={
    "chatg",
    "chats",
    "fileg",
    "files",
    "quit"



};
int getCmdno(char *cmd)
{
    int i;
    int n=sizeof(cmdstring)/sizeof(char *);
    for(i=0;i<n;i++)
    {
        if(strcmp(cmd,cmdstring[i])==0)
        {
            break;
        }
    }
    return i;
}
int quit;
void randfile(char *strid,int length)
{
    int i=0;
    srand((unsigned) time(NULL));
    for (i = 0; i < length - 5; i++)
    {
        strid[i] = 'a' + rand() % 26;

    }
    strid[length - 5] = '.';
    strid[length - 4] = 'd';
    strid[length - 3] = 'a';
    strid[length - 2] = 't';
    strid[length - 1] = '\0';
    return;
}
void *start(void *arg)
{
    char fname[9];
    int a=9;
    int wdl;
    char buf[1076];
    int n;
    int m;
    int k;
    struct msgHead *mhead=(struct msgHead *)buf;
    int *cfd=arg;
    while(1)
    {
        n=recv(*cfd,mhead,HEADLEN,MSG_WAITALL);
        if(n<=0)
        {

            break;
        }   

        m=ntohl(mhead->msglen);
        n=0;
        if(m>0)
        {
            n=recv(*cfd,buf+HEADLEN,m,MSG_WAITALL);
        }
        if(mhead->type==ntohl(T_BCAST))
        {
            if(mhead->ctype==ntohl(C_MSG))
            {
                printf("%s send msg to everyone:%s\n",mhead->sname,buf+HEADLEN);
            }
            else
            {
                if(mhead->ctype==ntohl(C_FSTART))
                {

                    randfile(fname,a);
                    wdl=open(fname,O_WRONLY|O_CREAT|O_TRUNC,0664);
                    k=write(wdl,buf+HEADLEN,m);
                }
                else if(mhead->ctype==ntohl(C_FILE))
                {
                    k=write(wdl,buf+HEADLEN,m);
                }
                else
                {
                    printf("%s send a group file:%s\n",mhead->sname,fname);
                    close(wdl);
                }
            }
        }

        else
        {
            if(mhead->ctype==ntohl(C_MSG))
            {
                printf("%s send Private msg to me:%s\n",mhead->sname,buf+HEADLEN);
            }
            else
            {
                if(mhead->ctype==ntohl(C_FSTART))
                {

                    randfile(fname,a);
                    wdl=open(fname,O_WRONLY|O_CREAT|O_TRUNC,0664);
                    k=write(wdl,buf+HEADLEN,m);
                }
                else if(mhead->ctype==ntohl(C_FILE))
                {
                    k=write(wdl,buf+HEADLEN,m);
                }
                else
                {
                    printf("%s send a Private file:%s\n",mhead->sname,fname);
                    close(wdl);
                }
            }

        }

    }
    return NULL;
}


int main(int argc,char*argv[])
{
    char sname[20];
    char dname[20];
    char buf[1076];
    char fname[20];
    char cmd[20];
    int cmdno;
    int flag;
    int fdl;
    int n;
    int q;
    int rt;
    int st;
    int cfd;
    int nfd;
    int len;
    pthread_t pt;
    struct msgHead *mhead=(struct msgHead *)buf;

    struct sockaddr_in saddr;
    if(argc<3)
    {
        fprintf(stderr,"please input information\n");
        return -1;
    }
    unsigned short sport=(unsigned short)atoi(argv[1]);
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
    printf("please input your nane:");
    scanf("%s",sname);
    rt=connect(cfd,(struct sockaddr *)&saddr,len);
    if(-1==rt)
    {
        close(cfd);
        fprintf(stderr,"connect fail");
        return -1;
    }

    mhead->type=htonl(T_REGIST);
    mhead->ctype=htonl(C_MSG);
    strcpy(mhead->sname,sname);
    strcpy(mhead->dname,"");
    mhead->msglen=0;
    send(cfd,buf,HEADLEN,0);


    st=pthread_create(&pt,NULL,start,&cfd);
    if(0!=st)
    {
        close(cfd);
        fprintf(stderr,"create fail");
        return -1;
    }
    while(quit==0)
    {
        printf("please input chatg(B_CAST):chats(S_CAST):fileg(F_GROUP):files(F_SINGL):quit(QUIT)\n");
        
        fgets(cmd,1024,stdin);
        cmd[strlen(cmd)-1] = '\0';
        cmdno=getCmdno(cmd);
        switch(cmdno)
        {
            case C_BCAST:
                while(1)
                {
                    mhead->type=htonl(T_BCAST);
                    mhead->ctype=htonl(C_MSG);
                    n=read(STDIN_FILENO,buf+HEADLEN,1024);
                    buf[HEADLEN+n]='\0';
                    if(strcmp(buf+HEADLEN,"end\n")==0)
                    {
                        break;
                    }
                    if(strcmp(buf+HEADLEN,"quit\n")==0)
                    {
                        quit=1;
                        break;
                    }
                    strcpy(mhead->sname,sname);
                    strcpy(mhead->dname,"");
                    mhead->msglen=htonl(n+1);
                    send(cfd,buf,HEADLEN+n+1,0);
                }

                break;
            case C_SCAST:
                while(1)
                {
                    mhead->type=htonl(T_SCAST);
                    mhead->ctype=htonl(C_MSG);
                    printf("please input name:");
                    scanf("%s",dname);
                    while(1)
                    {
                        n=read(STDIN_FILENO,buf+HEADLEN,1024);
                        buf[HEADLEN+n]='\0';
                        if(strcmp(buf+HEADLEN,"end\n")==0)
                        {
                            break;
                        }
                        if(strcmp(buf+HEADLEN,"quit\n")==0)
                        {
                           quit=1;
                           break;
                        }
                        strcpy(mhead->sname,sname);
                        strcpy(mhead->dname,dname);
                        mhead->msglen=htonl(n+1);
                        send(cfd,buf,HEADLEN+n+1,0);
                    }
                    break;
                }

                break;
            case F_GROUP:
                mhead->type=htonl(T_BCAST);
                printf("please input file name:");
                scanf("%s",fname);
                fdl=open(fname,O_RDONLY);
                flag=0;
                while(1)
                {
                    mhead->ctype=htonl(C_FILE);
                    if(0==flag)
                    {
                        printf("start send to the file\n");
                        mhead->ctype=htonl(C_FSTART);
                    }
                    n=read(fdl,buf+HEADLEN,1024);
                    if(n<=0)
                    {

                        mhead->ctype=htonl(C_END);
                        strcpy(mhead->sname,sname);
                        strcpy(mhead->dname,"");
                        mhead->msglen=htonl(0);
                        send(cfd,buf,HEADLEN+n,0);
                        printf("send end\n");
                        close(fdl);

                        break;
                    }
                    strcpy(mhead->sname,sname);
                    strcpy(mhead->dname,"");
                    mhead->msglen=htonl(n);
                    send(cfd,buf,HEADLEN+n,0);
                    flag++;
                }
                break;
            case F_SINGL:
                mhead->type=htonl(T_SCAST);
                printf("please input Receiver name:");
                scanf("%s",dname);

                printf("please input file name:");
                scanf("%s",fname);
                fdl=open(fname,O_RDONLY);
                flag=0;
                while(1)
                {
                    mhead->ctype=htonl(C_FILE);
                    if(0==flag)
                    {
                        mhead->ctype=htonl(C_FSTART);
                    }
                    n=read(fdl,buf+HEADLEN,1024);
                    if(n<=0)
                    {
                        mhead->ctype=htonl(C_END);
                        strcpy(mhead->sname,sname);
                        strcpy(mhead->dname,dname);
                        mhead->msglen=htonl(0);
                        send(cfd,buf,HEADLEN+n,0);
                        close(fdl);

                        break;
                    }
                    strcpy(mhead->sname,sname);
                    strcpy(mhead->dname,dname);
                    mhead->msglen=htonl(n);
                    send(cfd,buf,HEADLEN+n,0);
                    flag++;
                }
                break;
            case T_QUIT:
                quit=1;
                break;
            default:
                break;
        }
    }
    shutdown(cfd,SHUT_RDWR);
    pthread_join(pt,NULL);
    return 0;
}

