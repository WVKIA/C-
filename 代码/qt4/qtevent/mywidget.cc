
#include "mywidget.h"

#include <iostream>
using namespace std;

mywidget::mywidget(QWidget *parent,Qt::WindowFlags f):QWidget(parent,f)
{
    //dig = new mydialog;
    dig = NULL;
}
mywidget::~mywidget()
{
    if(dig != NULL)
    {
        delete dig;
    }
}
void mywidget::recvarg(bool ok,QString s,int r)
{
    cout<<ok<<" "<<s.toStdString()<<"r:"<<r<<endl;
}

void mywidget::mouseMoveEvent(QMouseEvent *event)
{
    /*if(event->buttons() == Qt::LeftButton)
    {
        QPoint  pos = event->pos();
        vpos.push_back(pos);
        repaint();
    }*/
    QWidget::mouseMoveEvent(event);
}
void mywidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    cout<<"hello\n";
    QString s;
    int     r;
    if(event->button() == Qt::RightButton)
    {
        vpos.clear();
        repaint();
        return;
    }
    else if(event->button() == Qt::LeftButton)
    {
        struct mydata data;
        if(NULL == dig)
        {
            dig = new mydialog;
            connect(dig,SIGNAL(digsig(bool,QString,int)),this,SLOT(recvarg(bool,QString,int)));
            dig->setModal(true);
        }
        dig->exec();
        //dig->show();
        if(dig->getarg(s,r))
        {
            data.p = event->pos();
            data.s = s;
            data.r = r;
            vpos.push_back(data);
            repaint();
        }
        return;
    }
    QWidget::mouseDoubleClickEvent(event);
}
void mywidget::paintEvent(QPaintEvent *event)
{
    QPainter p;
    p.begin(this);
    vector<struct mydata>::iterator it;
    QRectF rec;
    QPointF pos;
    struct mydata data;
    for(it = vpos.begin();it!=vpos.end();it++)
    {
        data = *it;
        pos = QPoint(data.p.x()-data.r,data.p.y()-data.r);
        rec = QRectF(pos,QSizeF(data.r*2,data.r*2));
        p.drawArc(rec,0,360*16);
        p.drawText(data.p,data.s);
    }
    p.end();
}
