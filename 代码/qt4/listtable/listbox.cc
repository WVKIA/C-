#include <QtGui>

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    QWidget *mwindow = new QWidget();
    QTableWidget *table = new QTableWidget(10,2,mwindow);
    //listv->addColumn("name");
    //new QListViewItem(listv,"1001","xiaoming");
    QGridLayout *layout = new QGridLayout();
    mwindow->setLayout(layout);
    layout->addWidget(table);
    //layout->setSizeConstraint(QLayout::SetFixedSize);
    mwindow->setWindowTitle("main window");
    mwindow->show();
    rt = app.exec();
    return rt;
}
