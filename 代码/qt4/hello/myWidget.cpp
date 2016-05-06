
#include "myWidget.h"

myWidget::myWidget(QWidget *p,Qt::WindowFlags f):QWidget(p,f)
{
    b1.setText(QString("yes"));
    b2.setText(QString("no"));
    
    mlay.addWidget(&t1);
    mlay.addWidget(&t2);

    slay.addWidget(&b1);
    slay.addWidget(&b2);
    mlay.addLayout(&slay);
    
    setLayout(&mlay);
    QObject::connect(&b1,SIGNAL(clicked()),this,SLOT(yes()));
    QObject::connect(&b2,SIGNAL(clicked()),this,SLOT(no()));
    //信号和槽机制
}
void myWidget::yes(void)
{
    QString s = t2.toPlainText();
    t1.append(s);
}
void myWidget::no(void)
{
    t2.setText(QString(""));
}
