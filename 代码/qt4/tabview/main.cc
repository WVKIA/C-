
#include <QtGui>
#include <string.h>
#include "window.h"

int main(int argc,char *argv[])
{
    int rt;
    QApplication app(argc,argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    mywindow *win = new mywindow();
    win->show();
    rt = app.exec();
    return rt;
}
