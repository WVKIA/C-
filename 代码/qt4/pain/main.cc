#include <QtGui>
#include "mainwin.h"
int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    mainwin *pmain = new mainwin();
    pmain->show();
    rt = app.exec();
    return rt;
}
