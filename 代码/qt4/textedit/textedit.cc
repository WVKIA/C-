#include <QtGui>
#include "mywindow.h"

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    MyWindow *win = new MyWindow();
    win->show();
    rt = app.exec();
    delete win;
    return rt;
}
