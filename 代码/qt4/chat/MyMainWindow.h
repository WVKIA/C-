#ifndef __MYMAINWINDOW_H__
#define __MYMAINWINDOW_H__

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
#include <QFont>
#include <QSize>
#include <QBrush>
#include "MyLoginDlg.h"
#include "MyAgent.h"
#include "MyChatDlg.h"
#include <QByteArray>
#include <stdlib.h>
class MyMainWindow:public QMainWindow
{
    Q_OBJECT
protected:
    map<QString,MyChatDlg *> chatDlgs;
    QListWidget *mylist;

    map<QString,queue<struct msgHead *> *> myque;
    MyLoginDlg  *login;
    MyAgent     agent;
    
     
    bool event(QEvent *event);
public slots:
    int itemDClicked(QListWidgetItem *item);
    int logok(QString ip,QString port,QString name);

    void recvMsg(MyChatDlg *,QString &);
public:
    MyMainWindow(QWidget *parent = 0,Qt::WindowFlags flags = 0);

    virtual ~MyMainWindow();
    void msgRecved(QString &);
    void large(int row);
    void small(int row);

};
#endif
