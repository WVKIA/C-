
#include "mainwin.h"
#include "centwin.h"
mainwin::mainwin(QWidget *parent,Qt::WindowFlags flags):QMainWindow(parent,flags)
{
    pcentwin = new centwin();
    setCentralWidget(pcentwin);
    resize(300,300);
}
