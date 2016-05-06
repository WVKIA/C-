#include <QtGui>

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    QLabel *label = new QLabel("hello qt");
    label->resize(400,200);
    label->setWindowTitle("hello");
    label->show();
    rt = app.exec();
    delete label;
    return rt;
}
