
#include "myDialog.h"
myDialog::myDialog(QWidget *p,Qt::WindowFlags f):QDialog(p,f),b1(QString("yes")),b2(QString("no"))
{
    spbox.setRange(10,200);
    slder.setRange(10,200);
    spbox.setValue(100);
    slder.setValue(100);
    slder.setOrientation(Qt::Horizontal);
    //b1.setText(QString("yes"));
    //b2.setText(QString("no"));
    
    toplay.addWidget(&spbox);
    toplay.addWidget(&slder);
    bottomlay.addWidget(&b1);
    bottomlay.addWidget(&b2);
    mlay.addLayout(&toplay);
    mlay.addLayout(&bottomlay);
    setLayout(&mlay);
    
    QObject::connect(&spbox,SIGNAL(valueChanged(int)),&slder,SLOT(setValue(int)));
    QObject::connect(&slder,SIGNAL(valueChanged(int)),&spbox,SLOT(setValue(int)));
    QObject::connect(&spbox,SIGNAL(valueChanged(int)),this,SLOT(valueChang(int)));
    QObject::connect(&slder,SIGNAL(valueChanged(int)),this,SLOT(valueChang(int)));
    //QObject::connect(&b1,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(&b2,SIGNAL(clicked()),this,SLOT(reject()));
    QObject::connect(&b1,SIGNAL(clicked()),this,SLOT(valueUpdate()));
}
void myDialog::valueUpdate(void)
{
    r = spbox.value();
    accept();
}
void myDialog::valueChang(int v)
{
    emit valueChanged(v);
}
int myDialog::getValue(void)
{
    return r;
}
bool myDialog::setValue(int r)
{
    spbox.setValue(r);
    slder.setValue(r);
    this->r = r;
    return true;
}