#include <QtGui>

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    QPushButton *button = new QPushButton("hello qt");
    button->resize(400,200);
    button->setWindowTitle("hello");
    QObject::connect(button,SIGNAL(clicked()),&app,SLOT(quit()));
    button->show();
    rt = app.exec();
    delete button;
    return rt;
}
