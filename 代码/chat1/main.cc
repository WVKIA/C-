#include <QtGui>
#include "MyMainWindow.h"
#include "MyLoginDlg.h"
int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    MyMainWindow mWindow;
    //mWindow->show();
    rt = app.exec();
    return rt;
}
