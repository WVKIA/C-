
#ifndef __MYDIALOG_H__
#define __MYDIALOG_H__
#include <QtGui>
class myDialog:public QDialog
{
    public:
        myDialog(QWidget *p=0,Qt::WindowFlags f=0);
    protected:
        QSpinBox spbox;
        QSlider  slder;
        QHBoxLayout lay;
};

#endif
