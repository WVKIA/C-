
#ifndef __MYDIALOG_H__
#define __MYDIALOG_H__

#include <QtGui>

class mydialog:public QDialog
{
    Q_OBJECT
    public:
        mydialog(QWidget *parent = 0,Qt::WindowFlags f = 0);
        bool getarg(QString &s,int &r);
    signals:
        void digsig(bool,QString,int);
    public slots:
        void yes(void);
        void no(void);
    private:
        QLineEdit *pline;
        QSpinBox  *pr;
        QPushButton *ok;
        QPushButton *cancel;
        bool sure;
};
#endif
