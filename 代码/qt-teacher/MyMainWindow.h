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

class MyMainWindow:public QMainWindow
{
    Q_OBJECT
protected:
    map<QString,MyChatDlg *> chatDlgs;
    map<QString,queue<struct msgHead *> *> msgQue;
    QListWidget *mylist;
    MyLoginDlg  *login;
    MyAgent     agent;
    bool event(QEvent *event);
    void msgRecved(QString &sname);
    void large(int row);
    void small(int row);
public slots:
    int itemDClicked(QListWidgetItem *item);
    int logok(QString ip,QString port,QString name);
    void send(MyChatDlg *,QString &msg);
public:
    MyMainWindow(QWidget *parent = 0,Qt::WindowFlags flags = 0);
    virtual ~MyMainWindow();
};
#endif
