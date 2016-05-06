#include "MyAgent.h"

MyAgent::MyAgent(MyMainWindow *mWin)
{
    mWindow = mWin;
    sfd = -1;
    pidrecv = 0;
    connected = false;
    saddr.sin_family = AF_INET;
    saddr.sin_port   = htons(0);
    saddr.sin_addr.s_addr = 0;
    memset(saddr.sin_zero,0,8);
    addrLen = sizeof(struct sockaddr_in);
}
MyAgent::~MyAgent()
{
    int rt = 0;
    //agentStop();
    if(sfd > 0)
    {
        shutdown(sfd,SHUT_RDWR);
        close(sfd);
        sfd = -1;
    }
    connected = false;
}
bool MyAgent::setServerAddr(QString ip,QString port)
{
    bool ok = false;
    QHostAddress haddr(ip);
    unsigned short up = port.toUShort(&ok);
    if(!ok)
    {
        return false;
    }
    if(haddr.protocol() != QAbstractSocket::IPv4Protocol)
    {
        return false;
    }
    saddr.sin_port = htons(up);
    saddr.sin_addr.s_addr = htonl(haddr.toIPv4Address());
    return true;
}
bool MyAgent::regName(QString name)
{
    int rt = 0;
    struct msgHead head;
    if(!connected)
    {
        return false;
    }

    head.type = htonl(T_REGIST);
    head.ctype = htonl(0);
    head.msgLen = htonl(0);
    strcpy(head.dname,"");
    strcpy(head.sname,name.toStdString().c_str());
    rt = send(sfd,&head,HEADLEN,0);
    if(rt < 0)
    {
        return false;
    }
    rt = recv(sfd,&head,HEADLEN,MSG_WAITALL);
    if(rt <= 0)
    {
        return false;
    }
    if((head.type != htonl(T_REGIST)) || (head.ctype != htonl(C_REGOK)))
    {
        return false;
    }
    rt = pthread_create(&pidrecv,NULL,recvThread,this);
    if(0 != rt)
    {
        return false;
    }
    myName= name;
    return true;
}
bool MyAgent::sendMsg(struct msgHead *msg)
{
    int rt = 0;
    int m = ntohl(msg->msgLen);
    if(!connected)
    {
        return false;
    }
    strcpy(msg->sname,myName.toStdString().c_str());
    rt = send(sfd,msg,HEADLEN+m,0);
    return true;
}

bool MyAgent::agentStart(void)
{
    int rt = 0;
    if(!connected)
    {
        sfd = socket(AF_INET,SOCK_STREAM,0);
        if(sfd < 0)
        {
            return false;
        }
        cout<<"soketwwwww "<<sfd<<"len:"<<addrLen<<endl;
        cout<<inet_ntoa(saddr.sin_addr)<<endl;
        cout<<ntohs(saddr.sin_port)<<endl;
        rt = ::connect(sfd,(struct sockaddr *)&saddr,addrLen);
        if(-1 == rt)
        {
            shutdown(sfd,SHUT_RDWR);
            close(sfd);
            sfd = -1;
            return false;
        }
        connected = true;
    }
    return true;
}
bool MyAgent::agentStop(void)
{
    int rt;
    if(-1 != sfd)
    {
        shutdown(sfd,SHUT_RDWR);
        close(sfd);
        sfd = -1;
    }
    connected = false;
    return true;
}
void *MyAgent::recvThread(void *arg)
{
    MyAgent *pagent = (MyAgent *)arg;
    int m = 0;
    int rt = 0;
    struct msgHead head;
    char *buf = NULL;
    while(1)
    {
        rt = recv(pagent->sfd,&head,HEADLEN,MSG_WAITALL);
        if(rt <= 0)
        {
            break;
        }
        m = ntohl(head.msgLen);
        buf = new char[HEADLEN+m];
        if(m > 0)
        {
            rt = recv(pagent->sfd,buf+HEADLEN,m,MSG_WAITALL);
            if(rt <= 0)
            {
                delete[] buf;
                break;
            }
        }
        memcpy(buf,&head,HEADLEN);
        QApplication::postEvent((QMainWindow *)pagent->mWindow,new MyEvent((struct msgHead*)buf,QEvent::User),0);
    }
    return NULL;
}
