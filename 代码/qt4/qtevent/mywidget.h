
#ifndef __MYWIDGET_H__
#define __MYWIDGET_H__

#include <QtGui>
#include <vector>
#include "mydialog.h"

struct mydata
{
    QPoint p;
    QString s;
    int r;
};

using namespace std;
class mywidget:public QWidget
{
    Q_OBJECT
    public:
        mywidget(QWidget * parent=0,Qt::WindowFlags f=0);
        ~mywidget();
    public slots:
        void recvarg(bool,QString,int);
    protected:
        void mouseDoubleClickEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void paintEvent(QPaintEvent *event);
    private:
        vector<struct mydata> vpos;
        mydialog *dig;
};


#endif
