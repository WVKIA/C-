
#include "mywidget.h"

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    mywidget *win = new mywidget;
    win->setWindowTitle("calc");

    win->show();
    rt = app.exec();
    delete win;
    return rt;
}
