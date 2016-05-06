#include <QtGui>

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    QWidget *mwindow = new QWidget();
    QSpinBox *spinbox = new QSpinBox();
    QSlider *slider = new QSlider(Qt::Horizontal);
    spinbox->setRange(0,100);
    slider->setRange(0,100);
    QObject::connect(spinbox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    QObject::connect(slider,SIGNAL(valueChanged(int)),spinbox,SLOT(setValue(int)));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(spinbox);
    layout->addWidget(slider);
    mwindow->setLayout(layout);
    mwindow->setWindowTitle("main window");
    mwindow->show();
    rt = app.exec();
    delete spinbox;
    delete slider;
    delete layout;
    delete mwindow;
    return rt;
}
