#include "myDialog.h"
myDialog::myDialog(QWidget *p,Qt::WindowFlags f):QDialog(p,f)
{
    s.setRange(100,200);
    l.setRange(100,200);
	s.setValue(100);
	l.setValue(100);
	
    l.setOrientation(Qt::Horizontal);
    
	toplay.addWidget(&s);
    toplay.addWidget(&l);
	
	b1.setText(QString("yes"));
	b2.setText(QString("no"));

	bottomlay.addWidget(&b1);
	bottomlay.addWidget(&b2);
	
	mlay.addLayout(&toplay);
	mlay.addLayout(&bottomlay);
    setLayout(&mlay);
    
	QObject::connect(&s,SIGNAL(valueChanged(int)),&l,SLOT(setValue(int)));
    QObject::connect(&l,SIGNAL(valueChanged(int)),&s,SLOT(setValue(int)));
	
	QObject::connect(&s,SIGNAL(valueChanged(int)),this,SLOT(valueChange(int)));
	QObject::connect(&l,SIGNAL(valueChanged(int)),this,SLOT(valueChange(int)));
	
	//QObject::connect(&b1,SIGNAL(clicked()),this,SLOT(accept()));
	QObject::connect(&b2,SIGNAL(clicked()),this,SLOT(reject()));
	
	QObject::connect(&b1,SIGNAL(clicked()),this,SLOT(valueUpdate()));
}
void myDialog::valueUpdate(void)
{
	r = s.value();
	accept();
}
int myDialog::getValue(void)
{
	return r;
}
bool myDialog::setValue(int r)
{
	s.setValue(r);
	l.setValue(r);
	this->r = r;
	return true;
}

void myDialog::valueChange(int v)
{
	emit valueChanged(v);
}
