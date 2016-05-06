#include "myDialog.h"
#include <QApplication>
#include <QWidget>
int main(int argc,char *argv[])
{
    int rt;
    QApplication app(argc,argv);
    myDialog window;
    window.setWindowTitle(QString("dialog"));
    window.show();
    rt = app.exec();
    return rt;
}
