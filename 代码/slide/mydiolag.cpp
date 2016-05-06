#include "myDialog.h"
myDialog::myDialog(QWidget *p,Qt::WindowFlags f):QWidget(p,f)
{
    s.setRange(100,200);
    l.setRange(100,200);
    l.setOrientation(Qt::Horizontal);
    lay.addWidget(&s);
    lay.addWidget(&l);
    setLayout(&lay);
    QObject::connect(&s,SIGNAL(valueChanged(int)),&l,SLOT(setValue(int)));
   
    QObject::connect(&l,SIGNAL(valueChanged(int)),&s,SLOT(setValue(int)));

}
