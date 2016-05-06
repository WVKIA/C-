#include <QtGui>
#include <phonon>
#include "mywindow.h"

int main(int argc,char *argv[])
{
    int rt = 0;
    QString s(argv[1]);
    QApplication app(argc,argv);
    MyWindow *win = new MyWindow(s);
    rt = app.exec();
    delete win;
    return rt;
}
