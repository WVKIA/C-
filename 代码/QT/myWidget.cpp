#include "myWidget.h"
myWidget::myWidget(QWidget *p ,Qt::WindowFlags f ):QWidget(p,f)
{
    b1.setText(QString ("yes"));
    
    b2.setText(QString ("no"));
    
    s1.setRange(0,100);
    l1.setRange(0,100);
	mlay.addWidget(&t1);
	mlay.addWidget(&t2);
    slay.addWidget(&b1);
    slay.addWidget(&b2);

    tlay.addWidget(&s1);
    tlay.addWidget(&l1);
    
    tlay.addWidget(&c1); 
    tlay.addWidget(&c2);
    tlay.addWidget(&r1);
    tlay.addWidget(&r2);
    mlay.addLayout(&tlay);
	mlay.addLayout(&slay);

    setLayout(&mlay);
	QObject::connect(&b1,SIGNAL(clicked()),this,SLOT(yes()));
	QObject::connect(&b2,SIGNAL(clicked()),this,SLOT(no()));

    QObject::connect(&s1,SIGNAL(valueChanged(int)),&l1,SLOT(setValue(int)));
    QObject::connect(&l1,SIGNAL(valueChanged(int)),&s1,SLOT(setValue(int)));
    //QObject::connect(&b1,SIGNAL(clicked()),this,SLOT(close()));
	//QObject::disconnect(&b1,SIGNAL(clicked()),this,SLOT(close()));
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
