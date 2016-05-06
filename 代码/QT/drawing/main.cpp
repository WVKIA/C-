#include <QApplication>
#include <QWidget>

#include "myWidget.h"
int main(int argc,char *argv[])
{
    int rt = 0;
   
    QApplication app(argc,argv);
    myWidget window;

    window.setWindowTitle(QString("qt window"));
    window.show();
    rt = app.exec();
    return rt;

    
}
