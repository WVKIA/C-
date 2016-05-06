#ifndef __MYWINDOW_H__
#define __MYWINDOW_H__

#include <QtGui>
#include <iostream>
class MyWindow :public QMainWindow
{
    Q_OBJECT
    protected:
        QTextEdit *text;
        QMenuBar  *menu;
        std::string fname;
    public:
        MyWindow(void);
        ~MyWindow();
    public slots:
        int myopen(void);
        int mysave(void);
        int myclose(void);
};

#endif
