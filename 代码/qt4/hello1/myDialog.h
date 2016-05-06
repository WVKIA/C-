
#ifndef __MYDIALOG_H__
#define __MYDIALOG_H__
#include <QtGui>
class myDialog:public QDialog
{
    Q_OBJECT
    public:
        myDialog(QWidget *p=0,Qt::WindowFlags f=0);
        int getValue(void);
        bool setValue(int r);
    signals:
        void valueChanged(int);
    public slots:
        void valueChang(int);
        void valueUpdate(void);
    protected:
        QSpinBox spbox;
        QSlider  slder;
        QVBoxLayout mlay;
        QHBoxLayout toplay;
        QHBoxLayout bottomlay;
        QPushButton b1;
        QPushButton b2;
        int r;
};

#endif
