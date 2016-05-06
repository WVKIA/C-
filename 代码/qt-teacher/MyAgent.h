#ifndef __MYAGENT_H__
#define __MYAGENT_H__

#include <arpa/inet.h>
#include <sys/socket.h>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QApplication>
#include <QMainWindow>
#include <QEvent>
#include <pthread.h>
#include <iostream>
#include <queue>
#include <unistd.h>
#include "msg.h"

using namespace std;

class MyEvent:public QEvent
{
public:
    struct msgHead *msg;
    MyEvent(struct msgHead *p,QEvent::Type type):QEvent(type)
    {
        msg = p;
    }
};

class MyMainWindow;

class MyAgent
{
private:
    bool connected;
    pthread_t pidrecv;
    struct sockaddr_in saddr;
    int addrLen;
    int sfd;
    static void *recvThread(void *);
    MyMainWindow *mWindow;
    string myName;
public:
    MyAgent(MyMainWindow *mWin);
    bool setServerAddr(QString ip,QString port);
    bool agentStart(void);
    bool agentStop(void);
    bool regName(QString name);
    bool sendMsg(struct msgHead *msg);
    virtual ~MyAgent();
};


#endif