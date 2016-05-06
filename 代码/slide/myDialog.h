#ifndef __MYDIALOG_H__
#define __MYDIALOG_H_
#include <QtGui>
class myDialog:public QWidget
{
    Q_OBJECT
    public:
        myDialog(QWidget *p = 0, Qt::WindowFlags f = 0);
    protected:
        QSpinBox s;
        QSlider l;
        QHBoxLayout lay;
};
#endif
