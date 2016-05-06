
#include "myDialog.h"
myDialog::myDialog(QWidget *p,Qt::WindowFlags f):QDialog(p,f)
{
    spbox.setRange(10,200);
    slder.setRange(10,200);
    spbox.setValue(100);
    slder.setValue(100);
    slder.setOrientation(Qt::Horizontal);
    lay.addWidget(&spbox);
    lay.addWidget(&slder);
    setLayout(&lay);
    QObject::connect(&spbox,SIGNAL(valueChanged(int)),&slder,SLOT(setValue(int)));
    QObject::connect(&slder,SIGNAL(valueChanged(int)),&spbox,SLOT(setValue(int)));
}