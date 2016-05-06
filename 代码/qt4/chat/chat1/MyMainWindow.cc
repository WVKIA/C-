#include "MyMainWindow.h"
#include <iostream>
using namespace std;
MyMainWindow::MyMainWindow(QWidget *parent,Qt::WindowFlags flags):QMainWindow(parent,flags),agent(this)
{
    QIcon icon("chat.png");
    //QIcon icon("gongying.jpg");
    QString s(tr("群"));
    QFont font;
    QColor color(Qt::black);
    QBrush brush(color);
    font.setPointSize(50);
    mylist = new QListWidget();
    QListWidgetItem *item = new QListWidgetItem(icon,s);
    msgQue[QString(tr("群"))] = new queue<struct msgHead *>;
    item->setFont(font);
    item->setForeground(brush);
    mylist->setIconSize(QSize(80,60));
    mylist->addItem(item);
    setCentralWidget(mylist);
    resize(200,400);
    QObject::connect(mylist,SIGNAL(itemDoubleClicked(QListWidgetItem *)),
                     this,SLOT(itemDClicked(QListWidgetItem *)));
    //setWindowIcon(QIcon("gongying.jpg"));
    setWindowTitle(QString(tr("共赢教育")));
    login = new MyLoginDlg();
    connect(login,SIGNAL(ok(QString,QString,QString)),
            this,SLOT(logok(QString,QString,QString)));
    login->show();
}
MyMainWindow::~MyMainWindow()
{
    delete login;
}
bool MyMainWindow::event(QEvent *event)
{
     if(event->type() == QEvent::User) 
     {
         MyEvent *myEvent = static_cast<MyEvent *>(event);
         //MyEvent *myEvent = (MyEvent *)event;
         if(myEvent->msg->type == htonl(T_USER))
         {
             if(myEvent->msg->ctype == htonl(C_USERUP))
             {
                 QIcon icon("chat.png");
                 QString sname(tr(myEvent->msg->sname));
                 QListWidgetItem *item = new QListWidgetItem(icon,sname);
                 QFont font;
                 QColor color(Qt::red);
                 QBrush brush(color);
                 font.setPointSize(50);
                 item->setFont(font);
                 item->setForeground(brush);
                 mylist->addItem(item);
                 msgQue[sname] = new queue<struct msgHead *>;
             }
             else
             {
                 int count = mylist->count();
                 QString sname(myEvent->msg->sname);
                 QListWidgetItem *item = NULL;
                 for(int i=1;i<count;i++)
                 {
                     if(mylist->item(i)->text().compare(sname) == 0)
                     {
                         item = mylist->takeItem(i);
                         break;
                     }
                 }
                 if(NULL != item)
                 {
                     map<QString,MyChatDlg *>::iterator it;
                     it = chatDlgs.find(sname);
                     if(it != chatDlgs.end())
                     {
                         MyChatDlg *pchat = it->second;
                         QObject::disconnect(pchat,SIGNAL(sendMsg(MyChatDlg *,QString &)),0,0);
                         chatDlgs.erase(it);
                         delete pchat;
                     }
                     delete item;
                     item = NULL;
                     queue<struct msgHead *> *q = msgQue[sname];
                     msgQue.erase(msgQue.find(sname));
                     while(!q->empty())//队列有消息，还应该释放消息
                     {
                         struct msgHead *pmsg = q->front();
                         q->pop();
                         free(pmsg);
                     }
                     delete q;
                 }
             }
             free(myEvent->msg);
         }//用户上线下线
         else if(myEvent->msg->type == htonl(T_BCAST))
         {
             queue<struct msgHead *> *q = NULL;
             QString tmp(tr("群"));
             q = msgQue[tmp];
             q->push(myEvent->msg);
             msgRecved(tmp);
        }//广播
         else
         {
             QString src(myEvent->msg->sname);
             map<QString,queue<struct msgHead*> *>::iterator it;
             it = msgQue.find(src);
             if(it == msgQue.end())
             {
                 QMessageBox box;
                 box.setText(tr("未知的私聊消息"));
                 box.exec();
             }
             else
             {
                 it->second->push(myEvent->msg);
                 msgRecved(src);
             }
         }//单播
         return true;
     }
     return QMainWindow::event(event);
}
int MyMainWindow::logok(QString ip,QString port,QString name)
{
    cout<<ip.toStdString()<<port.toStdString()<<name.toStdString()<<endl;
    if(!agent.setServerAddr(ip,port))
    {
        QMessageBox box;
        box.setText("非法ip或端口号");
        box.exec();
        return 0;
    }
    if(!agent.agentStart())
    {
        QMessageBox box;
        box.setText("连接服务器失败");
        box.exec();
        return 0;
    }
    if(!agent.regName(name))
    {
        QMessageBox box;
        box.setText("姓名冲突");
        box.exec();
        agent.agentStop();
        return 0;
    }
    show();
    login->hide();
    QString s = windowTitle();
    s += "-";
    s += name;
    setWindowTitle(s);
    return 1;
}
bool MyMainWindow::sendFile(QString &dname,QString &fname)
{
    int n = 0;
    FILE *fp = fopen(fname.toStdString().c_str(),"r");
    if(NULL == fp)
    {
        return false;
    }
    bool first = true;
    struct msgHead *head = (struct msgHead *)malloc(HEADLEN+1024);
    char *buf = (char *)(head+1);
    if(NULL == head)
    {
        fclose(fp);
        return false;
    }
    if(dname.compare(QString("群")) == 0)
    {//群发
        head->type = htonl(T_BCAST);
        strcpy(head->dname,"");
    }
    else
    {//单发
        head->type = htonl(T_SCAST);
        strcpy(head->dname,dname.toStdString().c_str());
    }
    while(1)
    {
        n = fread(buf,1,1024,fp);
        if(first)
        {
            head->ctype = htonl(C_FSTART);
            first = false;
        }
        else
        {
            head->ctype = htonl(C_FILE);
        }
        if(0 == n)
        {
            head->ctype = htonl(C_FEND);
        }
        head->msgLen = htonl(n);
        agent.sendMsg(head);
        if(0 == n)
        {
            break;
        }
    }
    fclose(fp);
    free(head);
    return true;
}
bool MyMainWindow::sendMsg(QString &dname,QString &msg)
{
    int len = strlen(msg.toStdString().c_str())+1;
    struct msgHead *head = (struct msgHead *)malloc(HEADLEN+len);
    if(NULL == head)
    {
        QMessageBox box;
        box.setText(QString(tr("获取动态内存失败")));
        box.exec();
        return false;
    }
    head->ctype = htonl(C_MSG);
    head->msgLen = htonl(len);
    strcpy((char *)(head+1),msg.toStdString().c_str());
    if(dname.compare(QString(tr("群"))) == 0)
    {//群聊
        head->type = htonl(T_BCAST);
        strcpy(head->dname,"");
    }
    else
    {//私聊
        head->type = htonl(T_SCAST);
        strcpy(head->dname,dname.toStdString().c_str());
    }
    agent.sendMsg(head);
    free(head);
    //判断群聊或者私聊
}
void MyMainWindow::send(MyChatDlg *dlg,QString &msg,bool flag)
{//flag==true sendfile  false sendMsg
    int len;
    QString dname = dlg->windowTitle();
    map<QString,MyChatDlg *>::iterator it;
    it = chatDlgs.find(dname);
    if(it == chatDlgs.end())
    {
        QMessageBox box;
        box.setText(tr("找不到朋友"));
        box.exec();
        return;
    }
    if(flag)
    {
        sendFile(dname,msg);
    }
    else
    {
        sendMsg(dname,msg);
    }
}
void MyMainWindow::msgRecved(QString &sname)
{
    int row = -1;
    int count = mylist->count();
    for(int i=0;i<count;i++)
    {
        if(mylist->item(i)->text().compare(sname) == 0)
        {
            row = i;
            break;
        }
    }
    
    map<QString,MyChatDlg *>::iterator it;
    it = chatDlgs.find(sname);
    if(it != chatDlgs.end())
    {
        MyChatDlg *dlg = it->second;
        queue<struct msgHead *> *q = msgQue[sname];
        struct msgHead *msg = NULL;
        if(dlg->isVisible())
        {
            while(!q->empty())
            {
                msg = q->front();
                q->pop();
                QString src(msg->sname);
                if(0 == row)
                {
                    src += QString(" broad:\n");
                }
                else
                {
                    src += QString(" send:\n");
                }
                src += QString((char *)(msg+1));
                dlg->showMsg(src);
                free(msg);
            }
            //return;
        }
    }
    large(row);
}
int MyMainWindow::itemDClicked(QListWidgetItem *item)
{
    int row = mylist->row(item);
    MyChatDlg *pChat;
    QString dname(item->text());
    map<QString,MyChatDlg *>::iterator it;
    it = chatDlgs.find(dname);
    if(it == chatDlgs.end())
    {
        pChat = new MyChatDlg;
        chatDlgs[dname] = pChat;
        pChat->setWindowTitle(dname);
        QObject::connect(pChat,SIGNAL(sendMsg(MyChatDlg *,QString &,bool)),
                         this,SLOT(send(MyChatDlg *,QString &,bool)));
    }
    else
    {
        pChat = it->second;
    }
    small(row);
    queue<struct msgHead *> *q = msgQue[dname];
    struct msgHead *msg = NULL;
    while(!q->empty())
    {
        msg = q->front();
        q->pop();
        QString src(msg->sname);
        if(0 == row)
        {
            src += QString(" broad:\n");
        }
        else
        {
            src += QString(" send:\n");
        }
        src += QString((char *)(msg+1));
        pChat->showMsg(src);
        free(msg);
    }
    pChat->show();
    return 0;
}
void MyMainWindow::small(int row)
{
    QListWidgetItem *item = mylist->item(row);
    QBrush brush = item->foreground();
    QFont font;
    brush.setColor(Qt::black);
    font.setPointSize(50);
    item->setFont(font);
    item->setForeground(brush);
}
void MyMainWindow::large(int row)
{
    QListWidgetItem *item = mylist->item(row);
    QBrush brush = item->foreground();
    QFont font;
    brush.setColor(Qt::red);
    font.setPointSize(100);
    item->setFont(font);
    item->setForeground(brush);
}