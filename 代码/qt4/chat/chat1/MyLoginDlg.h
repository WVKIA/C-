#ifndef  __MYLOGINDLG_H__
#define  __MYLOGINDLG_H__

#include <QtGui>

class MyLoginDlg :public QDialog
{
    Q_OBJECT
private:
    QLineEdit *ip;
    QSpinBox *port;
    QLineEdit *name;
    QPushButton *yes;
    QPushButton *no;
signals:
    int ok(QString,QString,QString);
public slots:
    int sure();
public:
    MyLoginDlg(QWidget *parent = 0,Qt::WindowFlags flags = 0);
};

#endif