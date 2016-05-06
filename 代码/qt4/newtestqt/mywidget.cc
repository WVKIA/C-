

#include "mywidget.h"
#include <iostream>
using namespace std;
mywidget::mywidget(QWidget *parent,Qt::WindowFlags f):QWidget(parent,f)
{
    int i;
    int j;
    QString s("%1");
    QString s1;
    pdisplay = new QLineEdit;
    pmlayout = new QVBoxLayout;
    ptoplayout = new QHBoxLayout;
    pbottomlayout = new QHBoxLayout;
    pllayout = new QGridLayout;
    prlayout = new QVBoxLayout;
    for(i=0;i<16;i++)
    {
        pbutton[i] = new QPushButton;
    }
    for(i=0;i<10;i++)
    {
        s1 = s.arg(i);
        pbutton[i]->setText(s1);
    }
    s1="AC";
    pbutton[10]->setText(s1);
    s1="=";
    pbutton[11]->setText(s1);
    s1="+";
    pbutton[12]->setText(s1);
    s1="-";
    pbutton[13]->setText(s1);
    s1="*";
    pbutton[14]->setText(s1);
    s1="/";
    pbutton[15]->setText(s1);
    for(i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
        {
            pllayout->addWidget(pbutton[i*3+j],i,j);
        }
    }
    for(i=12;i<16;i++)
    {
        prlayout->addWidget(pbutton[i]);
    }
    ptoplayout->addWidget(pdisplay);
    pmlayout->addLayout(ptoplayout);
    pmlayout->addLayout(pbottomlayout);
    pbottomlayout->addLayout(pllayout);
    pbottomlayout->addLayout(prlayout);
    setLayout(pmlayout);
    connect(pbutton[0],SIGNAL(clicked(bool)),this,SLOT(pressbutton0(bool)));
    connect(pbutton[1],SIGNAL(clicked(bool)),this,SLOT(pressbutton1(bool)));
    connect(pbutton[2],SIGNAL(clicked(bool)),this,SLOT(pressbutton2(bool)));
    connect(pbutton[3],SIGNAL(clicked(bool)),this,SLOT(pressbutton3(bool)));
    connect(pbutton[4],SIGNAL(clicked(bool)),this,SLOT(pressbutton4(bool)));
    connect(pbutton[5],SIGNAL(clicked(bool)),this,SLOT(pressbutton5(bool)));
    connect(pbutton[6],SIGNAL(clicked(bool)),this,SLOT(pressbutton6(bool)));
    connect(pbutton[7],SIGNAL(clicked(bool)),this,SLOT(pressbutton7(bool)));
    connect(pbutton[8],SIGNAL(clicked(bool)),this,SLOT(pressbutton8(bool)));
    connect(pbutton[9],SIGNAL(clicked(bool)),this,SLOT(pressbutton9(bool)));
    connect(pbutton[10],SIGNAL(clicked(bool)),this,SLOT(pressbuttonac(bool)));
    connect(pbutton[11],SIGNAL(clicked(bool)),this,SLOT(pressbuttoneq(bool)));
    connect(pbutton[12],SIGNAL(clicked(bool)),this,SLOT(pressbuttonadd(bool)));
    connect(pbutton[13],SIGNAL(clicked(bool)),this,SLOT(pressbuttondec(bool)));
    connect(pbutton[14],SIGNAL(clicked(bool)),this,SLOT(pressbuttonmul(bool)));
    connect(pbutton[15],SIGNAL(clicked(bool)),this,SLOT(pressbuttondiv(bool)));
    connect(this,SIGNAL(bclicked(int)),this,SLOT(pressbutton(int)));
}

void mywidget::pressbutton(int who)
{
    if(10 == who)
    {
        pdisplay->setText("0");
    }
    else if(11 == who)
    {
        QString s = pdisplay->text();
        cout<<s.toStdString()<<endl;
        pdisplay->setText("0");
    }
    else
    {
        QString s = pdisplay->text();
        if(s == QString("0"))
        {
            s = pbutton[who]->text();
        }
        else
        {
            s += pbutton[who]->text();
        }
        pdisplay->setText(s);
    }
}

void mywidget::pressbutton0(bool check)
{
    emit bclicked(0);
}
void mywidget::pressbutton1(bool check)
{
    emit bclicked(1);
}
void mywidget::pressbutton2(bool check)
{
    emit bclicked(2);
}
void mywidget::pressbutton3(bool check)
{
    emit bclicked(3);
}
void mywidget::pressbutton4(bool check)
{
    emit bclicked(4);
}
void mywidget::pressbutton5(bool check)
{
    emit bclicked(5);
}
void mywidget::pressbutton6(bool check)
{
    emit bclicked(6);
}
void mywidget::pressbutton7(bool check)
{
    emit bclicked(7);
}
void mywidget::pressbutton8(bool check)
{
    emit bclicked(8);
}
void mywidget::pressbutton9(bool check)
{
    emit bclicked(9);
}
void mywidget::pressbuttonac(bool check)
{
    emit bclicked(10);
}
void mywidget::pressbuttoneq(bool check)
{
    emit bclicked(11);
}
void mywidget::pressbuttonadd(bool check)
{
    emit bclicked(12);
}
void mywidget::pressbuttondec(bool check)
{
    emit bclicked(13);
}
void mywidget::pressbuttonmul(bool check)
{
    emit bclicked(14);
}
void mywidget::pressbuttondiv(bool check)
{
    emit bclicked(15);
}


