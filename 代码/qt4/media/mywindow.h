#ifndef __MYWINDOW_H__
#define __MYWINDOW_H__

#include <QtGui>
#include <iostream>
#include <phonon>
class MyWindow :public QMainWindow
{
    Q_OBJECT
    protected:
        QWidget  *video;
        QMenuBar  *menu;
        QString   fname;
        Phonon::MediaObject *mediaObject;
    public:
        MyWindow(QString s ="");
        int play(void);
        ~MyWindow();
    public slots:
        int myopen(void);
        int myclose(void);
};

#endif
