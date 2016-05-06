
#ifndef __MY_MAINWID_H__
#define __MY_MAINWID_H__

#include <QMainWindow>
#include "centwin.h"
class mainwin :public QMainWindow
{
    protected:
        QWidget *pcentwin;
    public:
        mainwin(QWidget *parent=0, Qt::WindowFlags flags=Qt::Window);
};


#endif
