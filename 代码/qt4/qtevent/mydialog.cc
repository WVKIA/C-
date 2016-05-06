
#include "mydialog.h"
#include <iostream>
mydialog::mydialog(QWidget *parent,Qt::WindowFlags f):QDialog(parent,f)
{
    pline  = new QLineEdit;
    pr     = new QSpinBox;
    ok     = new QPushButton;
    cancel = new QPushButton;
    ok->setText("ok");
    cancel->setText("cancel");
    pr->setRange(0,100);
    pr->setValue(30);
    QHBoxLayout *toplay = new QHBoxLayout;
    QHBoxLayout *bottomlay = new QHBoxLayout;
    QVBoxLayout *lay = new QVBoxLayout;

    toplay->addWidget(pline);
    toplay->addWidget(pr);
    bottomlay->addWidget(ok);
    bottomlay->addWidget(cancel);
    lay->addLayout(toplay);
    lay->addLayout(bottomlay);
    setLayout(lay);
    connect(ok,SIGNAL(clicked()),this,SLOT(yes()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(no()));
    sure = false;
}
bool mydialog::getarg(QString &s,int &r)
{
    if(sure)
    {
        s = pline->text();
        r = pr->value();
    }
    return sure;
}
void mydialog::yes(void)
{
    std::cout<<"yes\n";
    QString s = pline->text();
    int r = pr->value();
    sure = true;
    hide();
    emit digsig(true,s,r);
}
void mydialog::no(void)
{
    std::cout<<"no\n";
    sure = false;
    hide();
    emit digsig(false,QString(""),0);
}
