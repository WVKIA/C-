
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include "myWidget.h"

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    myWidget window;
    //QObject::connect(&window.b1,SIGNAL(clicked()),&window,SLOT(close()));
    window.setWindowTitle(QString("draw"));
    window.show();
    rt = app.exec();
    return rt;
}
