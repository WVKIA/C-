
#include "myWidget.h"
myWidget::myWidget(QWidget *p,Qt::WindowFlags f):QWidget(p,f),left(false),pos(QPointF(0,0)),r(100)
{
    dlg=NULL;
}
myWidget::~myWidget()
{
    delete dlg;
}
void myWidget::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.drawText(pos,QString("hello world"));
    painter.drawEllipse(pos,r,r);
}
void myWidget::dlgAccept(void)
{
    r = dlg->getValue();
}
void myWidget::dlgValueChanged(int v)
{
    r = v;
    update();
}
void myWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        if(NULL == dlg)
        {
            dlg = new myDialog;
            QObject::connect(dlg,SIGNAL(rejected()),this,SLOT(dlgAccept()));
            QObject::connect(dlg,SIGNAL(accepted()),this,SLOT(dlgAccept()));
            QObject::connect(dlg,SIGNAL(valueChanged(int)),this,SLOT(dlgValueChanged(int)));
            dlg->setWindowTitle(QString("set r"));
        }
        dlg->setValue(r);
        dlg->show();
        //模式对话框，模态对话框
    }
    else
    {
        QWidget::mouseDoubleClickEvent(event);
    }
}
void myWidget::mouseMoveEvent(QMouseEvent * event)
{
    if(left)
    {
        pos = event->posF();
        update();
    }
    else
    {
        QWidget::mouseMoveEvent(event);
    }
}
void myWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        left = true;
    }
    else
    {
        QWidget::mousePressEvent(event);
    }
}
void myWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        left = false;
    }
    else
    {
        QWidget::mouseReleaseEvent(event);
    }
}
