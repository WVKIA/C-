
#include <QtGui>
#include "myDialog.h"

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    myDialog dlg;
    //QObject::connect(&window.b1,SIGNAL(clicked()),&window,SLOT(close()));
    dlg.setWindowTitle(QString("mydialog"));
    dlg.show();
    rt = app.exec();
    return rt;
}
