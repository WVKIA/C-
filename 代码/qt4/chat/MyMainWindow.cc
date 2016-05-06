#include "MyMainWindow.h"
#include <iostream>
using namespace std;
MyMainWindow::MyMainWindow(QWidget *parent,Qt::WindowFlags flags):QMainWindow(parent,flags),agent(this)
{


    QIcon icon("chat.png");
    //QIcon icon("gongying.jpg");
    QString s(("qun"));
    QFont font;
    QColor color(Qt::red);
    QBrush brush(color);
    font.setPointSize(50);
    QListWidgetItem *item = new QListWidgetItem(icon,s);
    myque[QString(tr("qun"))]  = new queue<struct msgHead *>;
    item->setFont(font);
    item->setForeground(brush);
    mylist = new QListWidget();
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
     if (event->type() == QEvent::User) 
     {
         MyEvent *myEvent = static_cast<MyEvent *>(event);

         
         if(myEvent->msg->type == htonl(T_USER))
         {
             if(myEvent->msg->ctype == htonl(C_USERUP))
             {
                 QIcon icon("chat.png");
                 QString s(tr(myEvent->msg->sname));
                 QListWidgetItem *item = new QListWidgetItem(icon,s);
                 QFont font;
                 QColor color(Qt::red);
                 QBrush brush(color);
                 font.setPointSize(50);
                 item->setFont(font);
                 item->setForeground(brush);
                 mylist->addItem(item);

                 myque[s]  = new queue<struct msgHead *>;
             }
             else
             {
                 QString s((myEvent->msg->sname));
                 int count = mylist->count();
                 int row = -1;
                 QListWidgetItem *item = NULL;
                 for(int i=1;i<count;i++)
                 {
                     if(mylist->item(i)->text().compare(s) == 0)
                     {
                         item = mylist->takeItem(i);
                         
                         break;
                     }
                 }
                 if(NULL != item)
                 {
                     map<QString,MyChatDlg *>::iterator it;
                     it = chatDlgs.find(s);
                     if(it != chatDlgs.end())
                     {
                         MyChatDlg *pchat = it->second;
                         QObject::disconnect(pchat,SIGNAL(sendMsg(MyChatDlg *,QString &)) , 0,0);       
                         chatDlgs.erase(it);
                         delete pchat;
                     }
                     delete item;
                     item = NULL;

                     queue<struct msgHead *> * q = myque[s];
                     myque.erase(myque.find(s));
                     delete q;
                 }
             }
         }
         else if(myEvent->msg->type == htonl(T_BCAST))
         {
             QString ch = QString(("qun"));
            queue<struct msgHead *> *q  =myque[ch];
            q->push(myEvent->msg);
            msgRecved(ch);
         }
         else 
         {
            QString res(myEvent->msg->sname);
            map<QString,queue<struct msgHead *> *>::iterator it;
            it = myque.find(res);
            it->second->push(myEvent->msg);
            msgRecved(res);
         }

       
         return true;
     }
     return QMainWindow::event(event);
}
int MyMainWindow::logok(QString ip,QString port,QString name)
{
    cout<<ip.toStdString()<<port.toStdString()<<name.toStdString()<<endl;
    if(!agent.setServerAddr(ip,port))
    {
        cout<<"set server\n";
        return 0;
    }
    if(!agent.agentStart())
    {
         cout<<"agent start\n";
        return 0;
    }
    if(!agent.regName(name))
    {
        cout<<"reg fail\n";
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
int MyMainWindow::itemDClicked(QListWidgetItem *item)
{
    MyChatDlg *pChat;
    
    QString dname(item->text());
    int row = mylist->row(item);
    if(row < 0)
    {
        cout<<"错误的选项"<<endl;
        return -1;
    }
    map<QString,MyChatDlg *>::iterator it;
    it = chatDlgs.find(dname);
    if(it == chatDlgs.end())
    {
        pChat = new MyChatDlg;
        chatDlgs[dname] = pChat;
        pChat->setWindowTitle(dname);
        cout<<"thi sis tests2";
        QObject::connect(pChat,SIGNAL(sendMsg(MyChatDlg *,QString &)),this,SLOT(recvMsg(MyChatDlg*,QString &)));
    }
    else
    {
        pChat = it->second;
    }
    
    small(row);
    queue<struct msgHead *> *q = myque[dname];
    struct msgHead *msg = NULL;
    while(!q->empty())
    {
        msg = q->front();
        q->pop();
        QString src(msg->sname);
        if(0 == row)
        {
            src += QString("broad :");

        }
        else
        {
            src += QString("single: ");
        }
        src += QString((char *)(msg + 1));
        pChat->myappend(src);
        free(msg);
    }
    pChat->show();
    return 0;
}
void MyMainWindow::recvMsg(MyChatDlg *msg,QString &s)
{
    int m = 0;
    map<QString,MyChatDlg *>::iterator it;
    it = chatDlgs.find(QString(msg->windowTitle()));
    if(it == chatDlgs.end())
    {
        QMessageBox q;
        q.setText("can't find ");
        q.exec();
    }
    cout<<"this is test1";
    QString str = s;
    QString dname = it->second->windowTitle();
    //int len = str.size()+1;
    int len = strlen(str.toStdString().c_str()) + 1;
    struct msgHead *h = (struct msgHead *)malloc(HEADLEN + len);
    h->ctype = htonl(C_MSG);
    h->msgLen = htonl(len);
    strcpy((char *)(h+1),str.toStdString().c_str());

    if(QString((msg->windowTitle())).compare(QString(("qun"))) == 0)
    {
        h->type = htonl(T_BCAST);
        strcpy(h->dname,"");
    }
    else
    {
        h->type = htonl(T_SCAST);
        strcpy(h->dname,dname.toStdString().c_str());
    }
    cout<<"this is send";
    agent.sendMsg(h);
    free(h);
}
void MyMainWindow::msgRecved(QString &sname)
{
    int row = -1;
    int count = mylist->count();
    for(int i = 0; i < count; i++)
    {
        if(mylist ->item(i)->text().compare(sname) == 0)
        {
            row = i;
            break;
        }
    }
    map<QString ,MyChatDlg *>::iterator it;
    it = chatDlgs.find(sname);
    if(it != chatDlgs.end())
    {
        MyChatDlg *dlg = it->second;
        queue<struct msgHead *> *q = myque[sname];
        struct msgHead *msg= NULL;
        if(dlg->isVisible())
        {
            while(!q->empty())
            {
                msg = q->front();
                q->pop();
                QString s;
                if(0 == row)
                {
                    s = QString(msg->sname) + QString("broad:");

                }
                else
                {
                    s  = QString(msg->sname) + QString("single :");
                }
                s = s + QString((char *)(msg + 1));
                dlg->myappend(s);
                free(msg);
            }
        }
    }
    large(row);
    
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
void MyMainWindow::small(int row)
{
    QListWidgetItem *item  = mylist->item(row);
    QBrush brush = item->foreground();
    QFont font;
    brush.setColor(Qt::black);
    font.setPointSize(100);
    item->setFont(font);
    item->setForeground(brush);

}
