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
    myName = name.toStdString();
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
    strcpy(msg->sname,myName.c_str());
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
    string fname;
    while(1)
    {
        rt = recv(pagent->sfd,&head,HEADLEN,MSG_WAITALL);
        if(rt <= 0)
        {
            break;
        }
        m = ntohl(head.msgLen);
        buf = (char *)malloc(HEADLEN+m);
        if(m > 0)
        {
            rt = recv(pagent->sfd,buf+HEADLEN,m,MSG_WAITALL);
            if(rt <= 0)
            {
                free(buf);
                break;
            }
        }
        memcpy(buf,&head,HEADLEN);
        int ctype = ntohl(head.ctype);
        if((ctype >=C_FSTART) && (ctype <= C_FEND))
        {
            pagent->recvFile((struct msgHead *)buf,fname);
            if(ctype == C_FILE)
            {
                free(buf);
                continue;
            }
            else
            {
                char *p = (char *)malloc(HEADLEN+100);
                if(NULL == p)
                {
                    free(buf);
                    continue;
                }
                memcpy(p,buf,HEADLEN);
                if(ctype == C_FSTART)
                {
                    strcpy(p+HEADLEN,"发送文件开始");
                }
                else
                {
                    QString s("发送文件结束,文件名:");
                    s += QString(fname.c_str());
                    strcpy(p+HEADLEN,s.toStdString().c_str());
                }
                ((struct msgHead *)p)->msgLen = htonl(strlen(p+HEADLEN)+1);
                free(buf);
                buf = p;
            }
        }
        QApplication::postEvent((QMainWindow *)pagent->mWindow,new MyEvent((struct msgHead*)buf,QEvent::User),0);
    }
    return NULL;
}
FILE *MyAgent::getFp(string &sname,string &outname)
{
    FILE *fp = NULL;
    static int num = 0;
    QString fname;
    while(1)
    {
        fname = QString(sname.c_str())+QString("_")+QString(myName.c_str());
        fname += QString("%1").arg(num);
        num++;
        fp = fopen(fname.toStdString().c_str(),"r");
        if(NULL == fp)
        {
            break;
        }
        fclose(fp);
    }
    outname = fname.toStdString();
    fp = fopen(outname.c_str(),"w");
    return fp;
}
bool MyAgent::recvFile(struct msgHead *msg,string &fname)
{
    static FILE *fp = NULL;
    char *buf = (char *)(msg+1);
    int ctype = ntohl(msg->ctype);
    int len = ntohl(msg->msgLen);
    string outname;
    if(ctype == C_FSTART)
    {   
        string sname(msg->sname);
        fp = getFp(sname,outname);
        fname = outname;
    }
    if(len > 0)
    {
        fwrite(buf,1,len,fp);
    }
    if(ctype == C_FEND)
    {
        fclose(fp);
        fp = NULL;
    }
    return true;
}